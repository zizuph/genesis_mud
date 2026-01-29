/* heavy trollhammer  */
inherit "/std/weapon";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"

create_weapon() {
  set_name(({"troll-hammer","weapon","hammer"}));
  set_short("heavy iron hammer");
  set_pshort("iron hammers");
  set_long("A large, heavy two-handed troll's hammer, made out of iron.\n");
  set_adj("troll");
  set_adj("heavy");
  set_adj("iron");
  set_adj("large");
  set_adj("two-handed");
  set_default_weapon(28,20,W_CLUB,W_BLUDGEON,W_BOTH,0);
  add_prop(OBJ_I_WEIGHT,7600);
  add_prop(OBJ_I_VOLUME,7400);
  add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(28,20)+random(200)-100);
 }

query_recover()
{
  return MASTER+":"+query_wep_recover();
}

init_recover(arg) { init_wep_recover(arg); }

