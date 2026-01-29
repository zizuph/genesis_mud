inherit "/std/armour";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"

create_armour() {
  set_name(({"helmet","iron helmet"}));
  set_short("iron helmet");
  set_pshort("iron helmets");
  set_long("This iron helmet was wrought by orcs, and on the front you see\n"+
  "the mark of Sauron's armies: A red eye on black background.\n");
  set_default_armour(8,A_HEAD,({ -2, 1, 0}),0);
  add_prop(OBJ_I_WEIGHT, 3000);
  add_prop(OBJ_I_VOLUME, 380);
  add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(8)+random(10)-20);
}
