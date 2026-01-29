/* boarhelm.c  */
inherit "/std/armour";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"

create_armour() {
  set_name(({"boarhelm","helmet","armour","boarskin"}));
  set_short("bristly boarskin helmet");
  set_pshort("boarhelm");
  set_long("A bristly dunlending boarhelm, made of brown boarskin.\n");
  set_adj(({"brown","boarskin","boar","skin","bristly","dunlending"}));
  set_ac(11);
  set_at(A_HEAD);
  set_am(({0,1,-1}));
  add_prop(OBJ_I_WEIGHT,200);
  add_prop(OBJ_I_VOLUME,180);
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(11)+random(200)-100);
 }

