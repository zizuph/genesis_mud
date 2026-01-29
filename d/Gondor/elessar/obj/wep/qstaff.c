/* quarterstaff  */
inherit "/std/weapon";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"

create_weapon() {
  set_name(({"quarterstaff","staff","weapon"}));
  set_short("red oak quarterstaff");
  set_pshort("quarterstaves");
  set_long("A large two-handed dunlending staff, made of ironshod red oak.\n");
  set_adj("dunlending");
  set_adj("red");
  set_adj("oak");
  set_adj("large");
  set_adj("two-handed");
  set_default_weapon(34,10,W_POLEARM,W_BLUDGEON,W_BOTH,0);
  add_prop(OBJ_I_WEIGHT,4000);
  add_prop(OBJ_I_VOLUME,4800);
  add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(34,10)+random(200)-100);
 }

query_recover() { return MASTER+":"+query_wep_recover(); }
init_recover(arg) { init_wep_recover(arg); }
