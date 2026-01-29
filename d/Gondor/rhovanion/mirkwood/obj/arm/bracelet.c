/*
*  Varian 11/18/12
*/

inherit "/std/armour";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include <macros.h>

create_armour() {
  set_name(({"bracelet", "bronze bracelet"}));
  set_pname("bronze bracelets");
  set_short("bronze bracelet");
  set_pshort("bronze bracelets");
  set_long("This is a thin bracelet crafted from several, " +
  "thin rods of bronze which have been twisted togeather.\n");
  set_default_armour(4,A_ANY_WRIST,({ 0, 0, 0 }),0);
  set_ac(1);
  add_prop(OBJ_I_WEIGHT,50);
  add_prop(OBJ_I_VOLUME,50);
  add_prop(OBJ_I_VALUE, 200);
 }
