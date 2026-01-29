/* Glove in Mirkwood */
inherit "/std/armour";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include <macros.h>

create_armour() {
  set_name(({"glove","leather glove","leatherglove"}));
  set_pname("gloves");
  set_short("leather glove");
  set_pshort("leather gloves");
  set_long("This is a small, left-handed leather glove. It would " +
    "work well if you could find a right-handed glove to go with it.\n");
  set_default_armour(4,A_L_HAND,({ 0, 0, 0 }),0);
  add_prop(OBJ_I_WEIGHT,350);
  add_prop(OBJ_I_VOLUME,112);
  add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(4)+random(10)-5);
 }
