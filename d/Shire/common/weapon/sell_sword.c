/*
 *  The sword that is sold at the forge by the blacksmith.
 */
 
inherit "/std/weapon";

#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>

create_weapon() {
   set_name("sword");
   set_pname("swords");
   set_short("sword");
   set_pshort("swords");
   set_adj("mediocre");
   set_long("The mediocre sword is made of iron of a not too good quality.\n");

   set_default_weapon( /* See /sys/wa_types.h for maxima */
      23,                     /* 'to hit' value    */
      18,                      /* penetration value */
      W_SWORD,                /* weapon type       */
      W_IMPALE | W_SLASH,     /* damage type       */
      W_ANYH,                 /* nr of hands       */
      0);           /* object that defines wield and unwield functions */

   /* Note that the price is automagically set by setting the wc and wp */
   add_prop(OBJ_I_WEIGHT,3400); /* Weighs 3.4 kg  */
   add_prop(OBJ_I_VOLUME,2000); /* Volume = weight/1.7 (iron) */ 
}


string query_recover()
{
    return MASTER + ":" + query_wep_recover();
}


void init_recover(string arg)
{
    init_wep_recover(arg);
}
