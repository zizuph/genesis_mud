/* Rohirrim spear  */
inherit "/std/weapon";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"

create_weapon() {
  set_name(({"spear","polearm","weapon"}));
  set_short("tall ashen spear");
  set_pshort("tall spears");
  set_long("A tall spear made of ash wood, its broad head made of steel.\n"+
    "The spear was made in Rohan.\n");
  set_adj("rohirrim");
  set_adj("bright");
  set_adj("steel");
  set_adj("tall");
  set_adj("ashen");
  set_default_weapon(13,24,W_POLEARM,W_IMPALE,W_ANYH,0);
  add_prop(OBJ_I_WEIGHT,8500);
  add_prop(OBJ_I_VOLUME,4500);
  add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(13,24)+random(200)-100);
}

query_recover() { return MASTER+":"+query_wep_recover(); }
init_recover(arg) { init_wep_recover(arg); }
