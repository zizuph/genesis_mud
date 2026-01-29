/* breastplate  */
inherit "/std/armour";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"

create_armour() {
  set_name(({"breastplate","plate","armour"}));
  set_short("green copper breastplate");
  set_pshort("breastplates");
  set_long("An old dunlending breastplate, made of beaten green copper.\n");
  set_adj(({"green","copper","old","dunlending"}));
  set_ac(10);
  set_at(A_TORSO);
  set_am(({-1,0,-1}));
  add_prop(OBJ_I_WEIGHT,8000);
  add_prop(OBJ_I_VOLUME,1000);
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(10)+random(100)-100);
 }

