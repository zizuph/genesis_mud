/* claymore  */
inherit "/std/weapon";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"

create_weapon() {
  set_name(({"claymore","sword","weapon"}));
  set_short("grey iron claymore");
  set_pshort("claymores");
  set_long("A huge two-handed dunlending sword, made of soft grey iron.\n");
  set_adj("dunlending");
  set_adj("grey");
  set_adj("iron");
  set_adj("huge");
  set_adj("two-handed");
  set_default_weapon(10,28,W_SWORD,W_SLASH|W_BLUDGEON,W_BOTH,0);
  add_prop(OBJ_I_WEIGHT,22000);
  add_prop(OBJ_I_VOLUME,3000);
  add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(10,28)+random(200)-100);
}

query_recover() { return MASTER+":"+query_wep_recover(); }
init_recover(arg) { init_wep_recover(arg); }
