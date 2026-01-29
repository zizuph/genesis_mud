/*
 *  Axe for gorges (the potion salesman) body guard, Grimrock.
 */
 
inherit "/std/weapon";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

create_weapon()
{
    set_name("axe");
    set_short("shimmering axe");
    set_adj("shimmering");
    set_long("The axe is shimmering and seems quite sharp.\n");

    set_default_weapon( /* See /sys/wa_types.h for maxima */
       35,                     /* 'to hit' value    */
       35,                     /* penetration value */
       W_AXE,                /* weapon type       */
       W_BLUDGEON || W_SLASH,     /* damage type       */
       W_BOTH);                 /* nr of hands       */


   add_prop(OBJ_I_WEIGHT,39200); /* Weighs 39 kg  All chrome */
   add_prop(OBJ_I_VOLUME,5521); /* Volume 5.5 Ltr */
 /* Formula taken from /doc/man/general/weapon:
  * cc = 50 + ((wchit * wcpen * min(wchit,wcpen)) / 4)
 */
   add_prop(OBJ_I_VALUE,3200);
}

