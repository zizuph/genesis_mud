/* heavy troll-club  */
inherit "/std/weapon";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"

create_weapon() {
  set_name(({"troll-club","weapon","club"}));
  set_short("heavy stone troll-club");
  set_pshort("troll-clubs");
  set_long("A large, heavy two-handed troll's club, made out of stone.\n");
  set_adj("troll");
  set_adj("heavy");
  set_adj("stone");
  set_adj("large");
  set_adj("two-handed");
  set_default_weapon(20,19,W_CLUB,W_BLUDGEON,W_BOTH,0);
  add_prop(OBJ_I_WEIGHT,8000);
  add_prop(OBJ_I_VOLUME,8300);
  add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(20,19)+random(200)-100);
 }


query_recover() { return MASTER+":"+query_wep_recover(); }

init_recover(arg) { init_wep_recover(arg); }

