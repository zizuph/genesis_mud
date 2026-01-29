/* mattock  */
inherit "/std/weapon";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"

create_weapon() {
  set_name(({"mattock","axe","weapon"}));
  set_short("blue steel mattock");
  set_pshort("mattocks");
  set_long("A large dwarven mining axe, made of inlayed teak and blue steel.\n");
  set_adj("mining");
  set_adj("blue");
  set_adj("steel");
  set_adj("large");
  set_adj("dwarven");
  set_default_weapon(17,27,W_AXE,W_IMPALE|W_BLUDGEON,W_BOTH,0);
  add_prop(OBJ_I_WEIGHT,3700);
  add_prop(OBJ_I_VOLUME,700);
  add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(17,27)+random(1000)-100);
}

query_recover() { return MASTER+":"+query_wep_recover(); }
init_recover(arg) { init_wep_recover(arg); }
