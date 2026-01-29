/* The Nazgul's Dragon Platemail */
inherit "/std/armour";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"

create_armour() {
  set_name(({"platemail","plate mail","mail"}));
  add_name("plate");
  set_adj("black");
  set_short("black platemail");
  set_pshort("black platemails");
  set_long("The black platemail is made from the skin of a Sea-drake!\n");
  set_default_armour(60,A_BODY,0,0);
  add_prop(OBJ_I_WEIGHT,5500);
  add_prop(OBJ_I_VOLUME,1200);
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(60)+random(200)-100);
  add_prop(MAGIC_AM_MAGIC,({75,"enchantment"}));
  add_prop(MAGIC_AM_ID_INFO,({"This plate armour is magically crafted from the skin of a Sea-drake!\n", 10}));
}

query_recover() { return MASTER+":"+query_arm_recover(); }

init_recover(arg) { init_arm_recover(arg); }
