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
  set_adj("cowhide");
  set_adj("leather");
  set_adj("stiff");
  set_adj("dunlending");
  set_ac(15);
  set_at(A_BODY);
  set_am(({-1,0,-1}));
  add_prop(OBJ_I_WEIGHT,5500);
  add_prop(OBJ_I_VOLUME,3600);
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(15)+random(100)-100);
 }

