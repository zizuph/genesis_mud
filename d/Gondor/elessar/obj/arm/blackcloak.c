/* The Nazgul's Black Robes */
inherit "/std/armour";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"

create_armour() {
  set_name("cloak");
  set_adj("black");
  set_adj("hooded");
  set_short("black hooded cloak");
  set_long("This is a large black cloak, with a wide hood.\n");
  set_ac(2);
  set_at(A_ROBE);
  set_am(({0,0,0}));
  add_prop(OBJ_I_WEIGHT,400);
  add_prop(OBJ_I_VOLUME,300);
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(2)+random(10)-5);
}

