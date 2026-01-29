/* testing armour */
inherit "/std/armour";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"

create_armour() {
  set_name("leather armour");
  set_pname("leather armours");
  set_short("leather armour");
  set_pshort("leather armours");
  set_adj("leather");
  set_long("This armour is made of fine hard leather.\n");
  set_default_armour(10,A_BODY,0,0);
  add_prop(OBJ_I_WEIGHT,3000);
  add_prop(OBJ_I_VOLUME,700);
  add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(10)+random(200)-100);
 }

