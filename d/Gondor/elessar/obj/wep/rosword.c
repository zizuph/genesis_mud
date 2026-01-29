/* The typical sword of the Rohirrim */
inherit "/std/weapon";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"

create_weapon() {
  set_name(({"sword","weapon","longsword"}));
  set_short("rohirrim longsword");
  set_pshort("rohirrim longswords");
  set_long("The sword is long and bright, and there are green gems set in the hilt.\n"+
    "This is the typical sword of the Men of Rohan.\n");
  set_adj("rohirrim");
  set_adj("long");
  set_adj("green-hilted");
  set_adj("bright");
  set_default_weapon(18,22,W_SWORD,W_SLASH|W_IMPALE,W_ANYH,0);
  add_prop(OBJ_I_WEIGHT,8700);
  add_prop(OBJ_I_VOLUME,3900);
  add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(18,22)+250);
}

query_recover() { return MASTER+":"+query_wep_recover(); }
init_recover(arg) { init_wep_recover(arg); }
