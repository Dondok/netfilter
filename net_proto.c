#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netfilter.h>
#include <linux/netdevice.h>
#include <linux/netfilter_ipv4.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <linux/udp.h>
#include <linux/skbuff.h>

int test_pack_rcv( struct sk_buff *skb, struct net_device *dev,
                   struct packet_type *pt, struct net_device *odev ) {
                       struct iphdr *iph;
                       struct udphdr *udph;
                       struct tcphdr *tcph;
udph = udp_hdr(skb);
tcph = tcp_hdr(skb);
   iph = ip_hdr(skb);
   printk( KERN_INFO "packet received with length: %u\n, SO %u DEST %u", skb->len,  udph->source, udph->dest);
   return skb->len;
};

/* struct packet_type {
   __be16 type;            // This is really htons(ether_type).
   struct net_device *dev; // NULL is wildcarded here
   (*func) ( struct sk_buff *, struct net_device *,
             struct packet_type *, struct net_device * );
   struct sk_buff *(*gso_segment)( struct sk_buff *skb, int features );
   int (*gso_send_check)( struct sk_buff *skb );
   struct sk_buff **(*gro_receive)( struct sk_buff **head, struct sk_buff *skb );
   int (*gro_complete)( struct sk_buff *skb );
   void *af_packet_priv;
   struct list_head list;
}; */
#define TEST_PROTO_ID 0x1234
static struct packet_type test_proto = {
   .type = __constant_htons( ETH_P_ALL ),  // may be: __constant_htons( TEST_PROTO_ID ),
   NULL,
   .func = test_pack_rcv,
   (void*)1,
   NULL
};

static int __init my_init( void ) {
   dev_add_pack( &test_proto );
   printk( KERN_INFO "module loaded\n" );
   return 0;
}

static void __exit my_exit( void ) {
   dev_remove_pack( &test_proto );
   printk( KERN_INFO "module unloaded\n" );
}

module_init( my_init );
module_exit( my_exit );

MODULE_AUTHOR( "Oleg Tsiliuric" );
MODULE_LICENSE( "GPL v2" );
