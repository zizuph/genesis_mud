/* chainmail  */
inherit "/std/armour";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"

create_armour() {
  set_name(({"chainmail","steel","armour"}));
  set_short("grey steel chainmail");
  set_pshort("chainmails");
  set_long("A fine rohirrim chainmail, made of tempered grey rings.\n");
  set_adj(({"grey","steel","fine","rohirrim"}));
  set_ac(24);
  set_at(A_BODY);
  set_am(({-1,1,0}));
  add_prop(OBJ_I_WEIGHT,9000);
  add_prop(OBJ_I_VOLUME,1250);
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(24)+random(200)-100);
 }

