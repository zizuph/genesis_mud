/* coat  */
inherit "/std/armour";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"

create_armour() {
  set_name(({"coat","leather","armour"}));
  set_short("cowhide leather coat");
  set_pshort("coats");
  set_long("A stiff dunlending coat, made of hardened cowhide leather.\n");
  set_adj(({"cowhide","leather","stiff","dunlending"}));
  set_ac(15);
  set_at(A_BODY);
  set_am(({0,1,-1}));
  add_prop(OBJ_I_WEIGHT,5000);
  add_prop(OBJ_I_VOLUME,3000);
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(15)+random(100)-100);
 }

