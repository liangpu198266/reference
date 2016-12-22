#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/tcp.h>                  /* for tcphdr */
#include <net/ip.h>
#include <net/tcp.h>                    /* for csum_tcpudp_magic */
#include <net/udp.h>
#include <net/icmp.h>                   /* for icmp_send */
#include <net/route.h>                  /* for ip_route_output */
#include <net/ipv6.h>
#include <net/ip6_route.h>
#include <linux/icmpv6.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>

MODULE_LICENSE("GPL");
/* This is the structure we shall use to register our function */
int inet_i2str(unsigned int addr,char *addr_str){
  unsigned char *p;
  int i;
  p=(unsigned char *)(&addr);
  for(i=0;i<4;i++){
     addr_str[i*4+0]=*(p+i)/100+'0';
     addr_str[i*4+1]=*(p+i)/10-(*(p+i)/100)*10+'0';
     addr_str[i*4+2]=*(p+i)%10+'0';
     addr_str[i*4+3]='.';
  }
  addr_str[15]='/0';
  return 0;
}

/* This is the hook function itself */
unsigned int sahu_pre_routing(unsigned int hooknum,
                           struct sk_buff *skb,
                           const struct net_device *in,
                           const struct net_device *out,
                           int (*okfn)(struct sk_buff *))
{
  char saddr_str[16],daddr_str[16];
  struct sk_buff *sb = skb;
  struct iphdr *iph;
  if(!sb) return NF_ACCEPT;
  iph = ip_hdr(sb);
  if(!iph) return NF_ACCEPT;
  
  inet_i2str(iph->saddr,saddr_str);
  inet_i2str(iph->daddr,daddr_str);
  printk("pre_routing:/t%s->%s\n",saddr_str,daddr_str);  
  return NF_ACCEPT;
}
unsigned int sahu_post_routing(unsigned int hooknum,
                           struct sk_buff *skb,
                           const struct net_device *in,
                           const struct net_device *out,
                           int (*okfn)(struct sk_buff *))
{
  char saddr_str[16],daddr_str[16];
  struct sk_buff *sb = skb;
  struct iphdr *iph;
  if(!sb) return NF_ACCEPT;
  iph = ip_hdr(sb);
  if(!iph) return NF_ACCEPT;
  
  inet_i2str(iph->saddr,saddr_str);
  inet_i2str(iph->daddr,daddr_str);
  printk("post_routing:/t%s->%s\n",saddr_str,daddr_str);  
  return NF_ACCEPT;
}
unsigned int sahu_local_in(unsigned int hooknum,
                           struct sk_buff *skb,
                           const struct net_device *in,
                           const struct net_device *out,
                           int (*okfn)(struct sk_buff *))
{
  char saddr_str[16],daddr_str[16];
  struct sk_buff *sb = skb;
  struct iphdr *iph;
  if(!sb) return NF_ACCEPT;
  iph = ip_hdr(sb);
  if(!iph) return NF_ACCEPT;
  
  inet_i2str(iph->saddr,saddr_str);
  inet_i2str(iph->daddr,daddr_str);
  printk("local_in:/t%s->%s\n",saddr_str,daddr_str);  
  return NF_ACCEPT;
}
unsigned int sahu_local_out(unsigned int hooknum,
                           struct sk_buff *skb,
                           const struct net_device *in,
                           const struct net_device *out,
                           int (*okfn)(struct sk_buff *))
{
  char saddr_str[16],daddr_str[16];
  struct sk_buff *sb = skb;
  struct iphdr *iph;
  if(!sb) return NF_ACCEPT;
  iph = ip_hdr(sb);
  if(!iph) return NF_ACCEPT;
  
  inet_i2str(iph->saddr,saddr_str);
  inet_i2str(iph->daddr,daddr_str);
  printk("local_out:/t%s->%s/n",saddr_str,daddr_str);  
  return NF_ACCEPT;
}
unsigned int sahu_forward(unsigned int hooknum,
                           struct sk_buff *skb,
                           const struct net_device *in,
                           const struct net_device *out,
                           int (*okfn)(struct sk_buff *))
{
  char saddr_str[16],daddr_str[16];
  struct sk_buff *sb = skb;
  struct iphdr *iph;
  if(!sb) return NF_ACCEPT;
  iph = ip_hdr(sb);
  if(!iph) return NF_ACCEPT;
  
  inet_i2str(iph->saddr,saddr_str);
  inet_i2str(iph->daddr,daddr_str);
  printk("forward:/t%s->%s\n",saddr_str,daddr_str);  
  return NF_ACCEPT;
}
 
/* netfilter hooks in this kernel module*/
static struct nf_hook_ops sahu_ops[] __read_mostly = {
  {
    .hook = sahu_pre_routing,
    .owner = THIS_MODULE,
    .pf = PF_INET,
    .hooknum = NF_INET_PRE_ROUTING,
    .priority = NF_IP_PRI_FIRST,
  },
  {
    .hook = sahu_post_routing,
    .owner = THIS_MODULE,
    .pf = PF_INET,
    .hooknum = NF_INET_POST_ROUTING,
    .priority = NF_IP_PRI_FIRST,
  },
  {
    .hook = sahu_local_in,
    .owner = THIS_MODULE,
    .pf = PF_INET,
    .hooknum = NF_INET_LOCAL_IN,
    .priority = NF_IP_PRI_FIRST,
  },
  {
    .hook = sahu_local_out,
    .owner = THIS_MODULE,
    .pf = PF_INET,
    .hooknum = NF_INET_LOCAL_OUT,
    .priority = NF_IP_PRI_FIRST,
  },
  {
    .hook = sahu_forward,
    .owner = THIS_MODULE,
    .pf = PF_INET,
    .hooknum = NF_INET_FORWARD,
    .priority = NF_IP_PRI_FIRST,
  }
};
/* Initialisation routine */
int init_module()
{
  int ret;
  ret = nf_register_hooks(sahu_ops,ARRAY_SIZE(sahu_ops));
  if(ret<0){
    pr_info("can't install netMonitor into kernel!\n");
  }else{
    pr_info("netMonitor install into kernel!\n");
  }
  return 0;
}
/* Cleanup routine */
void cleanup_module()
{
  nf_unregister_hooks(sahu_ops,ARRAY_SIZE(sahu_ops));
  pr_info("netMonitor removed from kernel!\n");
}
