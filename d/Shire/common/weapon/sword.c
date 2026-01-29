/*
 *  Sword for the Hin Warrior guard
 */
 
inherit "/std/weapon";

#include <macros.h>
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

create_weapon()
{
    set_name("sword");
    set_pname("swords");
    set_short("shiny sword");
    set_pshort("shiny swords");
    set_adj("long");
    set_long("The sword has been polished lately and looks dangerous.\n");

    set_default_weapon( /* See /sys/wa_types.h for maxima */
       11,                     /* 'to hit' value    */
       10,                     /* penetration value */
       W_SWORD,                /* weapon type       */
       W_IMPALE | W_SLASH,     /* damage type       */
       W_NONE,                 /* nr of hands       */
       0);           /* object that defines wield and unwield functions */

   add_prop(OBJ_I_WEIGHT,5000); /* Weighs 5 kg  */
   add_prop(OBJ_I_VOLUME,2941); /* Volume 3 Ltr */
 /* Formula taken from /doc/man/general/weapon:
  * cc = 50 + ((wchit * wcpen * min(wchit,wcpen)) / 4)
 */
   add_prop(OBJ_I_VALUE,30 + random(40) + ((10*11*10)/4));
}


string query_recover()
{
    return MASTER + ":" + query_wep_recover();
}


void init_recover(string arg)
{
    init_wep_recover(arg);
}
