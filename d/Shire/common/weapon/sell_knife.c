/*
 *  The knife that is sold at the forge by the blacksmith.
 */
 
inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

create_weapon() {
   set_name("knife");
   set_pname("knives");
   set_short("long knife");
   set_pshort("long knife");
   set_adj("long");
   set_long("The long knife is just too short to be called a small sword.\n");

   set_default_weapon( /* See /sys/wa_types.h for maxima */
      16,                     /* 'to hit' value    */
      8,                      /* penetration value */
      W_KNIFE,                /* weapon type       */
      W_IMPALE | W_SLASH,     /* damage type       */
      W_ANYH,                 /* nr of hands       */
      0);           /* object that defines wield and unwield functions */

   /* Note that the price is automagically set by setting the wc and wp */
   add_prop(OBJ_I_WEIGHT,1700); /* Weighs 1.7 kg  */
   add_prop(OBJ_I_VOLUME,1000); /* Volume = weight/1.7 (iron) */ 
}


string query_recover()
{
    return MASTER + ":" + query_wep_recover();
}


void init_recover(string arg)
{
    init_wep_recover(arg);
}
