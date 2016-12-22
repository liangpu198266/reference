#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/skbuff.h>
#include <linux/ip.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/netdevice.h>

MODULE_LICENSE("GPL");

/* This is the structure we shall use to register our function */
static struct nf_hook_ops nfho;
static char *drop_if = "lo";
    /* This is the hook function itself */
unsigned int hook_func(unsigned int hooknum,
                           struct sk_buff *skb, 
                           const struct net_device *in,
                           const struct net_device *out,
                           int (*okfn)(struct sk_buff *))
{
        pr_info("Packet FROM.../n");
        printk("Dropped out packet on %s...n", out->name);
        printk("Dropped in packet on %s...n", in->name);
        if (strcmp(in->name, drop_if) == 0) {
            printk("Dropped packet on %s...n", drop_if);
            return NF_DROP;
        } else {
            return NF_ACCEPT;
        }
}

    /* Initialisation routine */
int init_module()
{
        /* Fill in our hook structure */
        nfho.hook     = hook_func;         /* Handler function */
        nfho.hooknum  = NF_INET_PRE_ROUTING; /* First hook for IPv4 */
        nfho.pf       = PF_INET;
        nfho.priority = NF_IP_PRI_FIRST;   /* Make our function first */

        nf_register_hook(&nfho);

        pr_info("dropLo install into kernel!/n");
        return 0;
}
            /* Cleanup routine */
void cleanup_module()
{
        nf_unregister_hook(&nfho);
        pr_info("dropLo removed from kernel!/n");
}
