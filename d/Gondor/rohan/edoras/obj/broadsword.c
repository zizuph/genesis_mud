/* shortsword  */
inherit "/std/weapon";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

void
create_weapon()
{
  set_name(({"broadsword","sword"}));
  set_pname("broadswords");
  set_short("broadsword");
  set_pshort("broadswords");
  set_adj(({"broad", "iron"}));
  set_long("This broadsword is made of iron.\n");
  set_default_weapon(28,27,W_SWORD,W_SLASH,W_BOTH,0);
  add_prop(OBJ_I_WEIGHT,5500);
  add_prop(OBJ_I_VOLUME,900);
  add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(28,27)+random(200)-100);
}

query_recover()  { return MASTER + ":" + query_wep_recover(); }
init_recover(arg) { init_wep_recover(arg); }
