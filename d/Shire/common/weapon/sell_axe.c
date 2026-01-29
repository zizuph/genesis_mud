/*
 *  The axe that is sold at the forge by the blacksmith.
 */
 
inherit "/std/weapon";

#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>

create_weapon() {
   set_name("axe");
   set_pname("axes");
   set_short("sturdy axe");
   set_pshort("sturdy axe");
   set_adj("sturdy");
   set_long("The sturdy axe looks just like the one dwarves use to wear.\n");

   set_default_weapon( /* See /sys/wa_types.h for maxima */
      20,                     /* 'to hit' value    */
      15,                     /* penetration value */
      W_AXE,                  /* weapon type       */
      W_SLASH,                /* damage type       */
      W_ANYH,                 /* nr of hands       */
      0);           /* object that defines wield and unwield functions */

   /* Note that the price is automagically set by setting the wc and wp */
   add_prop(OBJ_I_WEIGHT,4600); /* Weighs 4.6 kg  */
   add_prop(OBJ_I_VOLUME,2700); /* Volume 2.7 Ltr */ 
}


string query_recover()
{
    return MASTER + ":" + query_wep_recover();
}


void init_recover(string arg)
{
    init_wep_recover(arg);
}
