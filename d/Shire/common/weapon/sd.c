/*
*  The knife that is sold at the forge by the blacksmith.
   */

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

create_weapon() {
   set_name(({"dagger","silver dagger"}));
   set_pname("daggers");
   set_short("small silver dagger");
   set_pshort("small silver daggers");
   set_adj(({"small","silver"}));
   set_long("This dagger was beautiful made by a master smith.\n");
   
   set_default_weapon( /* See /sys/wa_types.h for maxima */
      16,
      8,                      /* penetration value */
      W_KNIFE,                /* weapon type       */
      W_IMPALE | W_SLASH,     /* damage type       */
      W_ANYH,                 /* nr of hands       */
      0);           /* object that defines wield and unwield functions */
   
   /* Note that the price is automagically set by setting the wc and wp */
   add_prop(OBJ_I_WEIGHT,500);
   add_prop(OBJ_I_VOLUME,500);
   add_prop(OBJ_I_VALUE,3750);
}


string query_recover()
{
   return MASTER + ":" + query_wep_recover();
}


void init_recover(string arg)
{
   init_wep_recover(arg);
}
