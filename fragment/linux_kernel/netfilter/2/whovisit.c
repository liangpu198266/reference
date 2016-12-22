#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/skbuff.h>
#include <linux/ip.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/netdevice.h>

MODULE_LICENSE("GPL");
#define NIPQUAD(addr) \
     ((unsigned char *)&addr)[0],  ((unsigned char *)&addr)[1],  ((unsigned char *)&addr)[2],  ((unsigned char *)&addr)[3]
/* This is the structure we shall use to register our function */
static struct nf_hook_ops nfho;

/* This is the hook function itself */
unsigned int hook_func(unsigned int hooknum,
                           struct sk_buff *skb,
                           const struct net_device *in,
                           const struct net_device *out,
                           int (*okfn)(struct sk_buff *))
{
        struct sk_buff *sb = skb;
        struct iphdr *iph;

        iph = ip_hdr(sb);
        pr_warning("Packet from source addr  %d.%d.%d.%d\n",NIPQUAD(iph->saddr));
        pr_warning("Packet from dist addr %d.%d.%d.%d\n",NIPQUAD(iph->daddr));
        pr_warning("Packet from protocol %d\n",iph->protocol);
        pr_warning("=========================================\n");

        return NF_ACCEPT;
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

        pr_info("whoVisit install into kernel!/n");
        return 0;
}
            /* Cleanup routine */
void cleanup_module()
{
        nf_unregister_hook(&nfho);
        pr_info("whoVisit removed from kernel!/n");
}
