#include <linux/module.h>
#include <linux/init.h>
#include <linux/netdevice.h>

static int __init my_init( void ) {
   struct net_device *dev;
   printk( KERN_INFO "Hello: module loaded at 0x%p\n", my_init );
   dev = first_net_device( &init_net );
   printk( KERN_INFO "Hello: dev_base address=0x%p\n", dev );
   while ( dev ) {
      printk( KERN_INFO
              "name = %6s irq=%4d ",
              dev->name, dev->irq /*dev->trans_start, dev->last_rx */ );
      dev = next_net_device( dev );
   }
   return -1;
}
static void __exit my_exit( void ) {
   printk( KERN_INFO "Unloading stub network module\n" );
}
module_init( my_init );
module_exit( my_exit );
