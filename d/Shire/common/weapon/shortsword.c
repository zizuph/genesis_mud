/*
 *  Shortsword for the Hin Warrior guard
 *
 * 1993/05/14 Last update
 * 2011/08/02 Lavellan - Added "sword" name as with other swords
 */
 
inherit "/std/weapon";

#include <macros.h>
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>

create_weapon() {
   set_name("shortsword");
   set_name("sword");
   set_pname("shortswords");
   set_short("shiny shortsword");
   set_pshort("shiny shortswords");
   set_adj("shiny");
   set_long("The shortsword has been polished lately. It can inflict much damage.\n");

   set_default_weapon( /* See /sys/wa_types.h for maxima */
      14,                     /* 'to hit' value    */
      16,                     /* penetration value */
      W_SWORD,                /* weapon type       */
      W_IMPALE | W_SLASH,     /* damage type       */
      W_RIGHT,                /* nr of hands       */
      0);           /* object that defines wield and unwield functions */

   add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(14,16));
}


string query_recover()
{
    return MASTER + ":" + query_wep_recover();
}


void init_recover(string arg)
{
    init_wep_recover(arg);
}
