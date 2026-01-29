/* gauntlet  */
inherit "/std/armour";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"

create_armour() {
  set_name(({"gauntlet","armour"}));
  set_short("steel chainmail gauntlet");
  set_pshort("gauntlets");
  set_long("A lefthanded rohirrim gauntlet, made of tempered steel rings.\n");
  set_adj(({"steel","chainmail","chain","lefthanded","rohirrim"}));
  set_ac(22);
  set_at(A_L_ARM);
  set_am(({-1,1,0}));
  add_prop(OBJ_I_WEIGHT,1000);
  add_prop(OBJ_I_VOLUME,150);
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(22)+random(200)-100);
 }

