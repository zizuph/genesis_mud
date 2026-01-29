/*
 *  Spear for the Hin Warrior guard
 */
 
inherit "/std/weapon";

#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>

create_weapon()
{
    set_name("spear");
    set_pname("spears");
    set_short("long spear");
    set_pshort("long spears");
    set_adj("long");
    set_long("The spear is a dangerous weapon when wielded by an expert.\n");

    set_default_weapon( /* See /sys/wa_types.h for maxima */
       7,            /* 'to hit' value    */
       11,           /* penetration value */
       W_POLEARM,      /* weapon type       */
       W_IMPALE,     /* damage type       */
       W_BOTH,       /* nr of hands       */
       0);           /* object that defines wield and unwield functions */

   add_prop(OBJ_I_WEIGHT,3500); /* Weighs 3.5 kg  */
   add_prop(OBJ_I_VOLUME,2058); /* Volume = weight/1.7 (iron) */
 /* Formula taken from /doc/man/general/weapon:
  * cc = 50 + ((wchit * wcpen * min(wchit,wcpen)) / 4)
 */
   add_prop(OBJ_I_VALUE,50 + ((7*11*7)/4));
}


string query_recover()
{
    return MASTER + ":" + query_wep_recover();
}


void init_recover(string arg)
{
    init_wep_recover(arg);
}
