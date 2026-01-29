inherit "/std/weapon";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"

create_weapon() {
  set_name(({"longsword","sword","long sword"}));
  set_short("steel longsword");
  set_pshort("steel longswords");
  set_long("This longsword is made of solid steel, and looks strong.\n");
  set_default_weapon(18,24,W_SWORD,W_SLASH | W_IMPALE,W_NONE,0);
  add_prop(OBJ_I_WEIGHT, 5000);
  add_prop(OBJ_I_VOLUME, 600);
  add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(18,24) + random(150) - 75);
}

query_recover() { return MASTER+":"+query_wep_recover(); }
init_recover(arg) { init_wep_recover(arg); }
