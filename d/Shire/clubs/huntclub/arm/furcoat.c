inherit "/std/armour";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
create_armour() {
  set_name("coat");
  set_pname("coats");
  set_adj(({"heavy","fur"}));
  set_short("heavy fur coat");
  set_pshort("heavy fur robes");
  set_long("This " +short()+ " is made from various animal furs stitched together. " +
    "It looks very warm.\n");
  set_default_armour(5,A_ROBE,0,0);
  add_prop(OBJ_I_WEIGHT,3000);
  add_prop(OBJ_I_VOLUME,7000);
  add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(10)+random(20)+10);
 }