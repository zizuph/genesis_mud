/* testing armour */
inherit "/std/armour";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"

create_armour() {
  set_name("robe");
  set_pname("robes");
  set_adj("elegant");
  set_short("elegant robe");
  set_pshort("elegant robes");
  set_long("This elegant robe is made of the finest cloth. It must cost a fortune.\n");
  set_default_armour(10,A_ROBE,0,0);
  add_prop(OBJ_I_WEIGHT,3000);
  add_prop(OBJ_I_VOLUME,7000);
  add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(10)+random(400)+200);
 }

