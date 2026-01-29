/* Jacket on the ground */
inherit "/std/armour";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include <macros.h>
#include "/sys/formulas.h"

create_armour() {
  set_name(({"jacket","leather jacket","leatherjacket"}));
  set_pname("jackets");
  set_adj("leather");
  set_short("leather jacket");
  set_pshort("leather jackets");
  set_long("This is a leather jacket. One size, fits all.\n");
  set_default_armour(10,A_BODY,({ 0, 0, 0 }),0);
  add_prop(OBJ_I_WEIGHT,1500);
  add_prop(OBJ_I_VOLUME,700);
  add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(10)+random(10)-5);
 }
