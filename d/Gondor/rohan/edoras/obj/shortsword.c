/* shortsword  */
inherit "/std/weapon";
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

void
create_weapon()
{
  set_name(({"shortsword","sword"}));
  set_pname("swords");
  add_pname("shortswords");
  set_short("silvery single-edged shortsword");
  set_pshort("silvery single-edged shortswords");
  set_adj(({"short", "silvery", "single-edged"}));
  set_long("This single-edged shortsword shines like silver.\n");
  set_default_weapon(19,14,W_SWORD,W_SLASH|W_IMPALE,W_NONE,0);
  add_prop(OBJ_I_WEIGHT,2000);
  add_prop(OBJ_I_VOLUME,700);
  add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(19,14)+random(200)-100);
}

query_recover()  { return MASTER + ":" + query_wep_recover(); }
init_recover(arg) { init_wep_recover(arg); }
