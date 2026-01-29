/* Trousers on the ground */
inherit "/std/armour";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include <macros.h>

create_armour() {
  set_name(({"trousers","leather trousers","leathertrousers"}));
  set_pname("trouserses");
  set_short("pair of leather trousers");
  set_pshort("pairs of leather trousers");
  set_long("This is a pair of leather trousers. One size fits all.\n");
  set_default_armour(6,A_LEGS,({ 0, 0, 0 }),0);
  add_prop(OBJ_I_WEIGHT,1500);
  add_prop(OBJ_I_VOLUME,700);
  add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(6)+random(10)-5);
}
