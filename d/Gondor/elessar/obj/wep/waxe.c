/* handaxe  */
inherit "/std/weapon";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"

create_weapon() {
  set_name(({"handaxe","axe","weapon"}));
  set_short("rusty iron handaxe");
  set_pshort("handaxes");
  set_long("A small dunlending chopping axe, made of weathered pine and rusty iron.\n");
  set_adj("chopping");
  set_adj("rusty");
  set_adj("iron");
  set_adj("small");
  set_adj("dunlending");
  set_default_weapon(7,10,W_AXE,W_SLASH|W_BLUDGEON,W_ANYH,0);
  add_prop(OBJ_I_WEIGHT,2000);
  add_prop(OBJ_I_VOLUME,500);
  add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(7,10)+random(200)-100);
}

query_recover() { return MASTER+":"+query_wep_recover(); }
init_recover(arg) { init_wep_recover(arg); }
