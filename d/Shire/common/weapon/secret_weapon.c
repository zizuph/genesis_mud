/* This weapon is used by common/guild/secret_room  */

inherit "/std/weapon";

#include <macros.h>
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>

#define SNAME ({"longsword", "shortsword", "sword", "dagger", "spear"})
#define SADJ  ({"shiny", "lethal", "heavy", "curved", "wooden"})
 
create_weapon() {
  int ran;

  ran = random(sizeof(SNAME));
  set_name(SNAME[ran]);
  set_short(SADJ[ran] + " " + SNAME[ran]);
  set_adj(SADJ[ran]);
  set_long("Consider this weapon a token of Nob Nar's gratitude.\n");

  set_default_weapon( /* See /sys/wa_types.h for maxima */
    8,                      /* 'to hit' value    */
    8,                      /* penetration value */
    W_SWORD,                /* weapon type       */
    W_SLASH,                /* damage type       */
    W_NONE,                 /* nr of hands       */
    0);           /* object that defines wield and unwield functions */

  add_prop(OBJ_I_WEIGHT, 3000);
  add_prop(OBJ_I_VOLUME, 2000);
  add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(8, 8));
}


string query_recover()
{
    return MASTER + ":" + query_wep_recover();
}


void init_recover(string arg)
{
    init_wep_recover(arg);
}
