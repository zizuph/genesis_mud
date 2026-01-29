/*
*  Varian 11/18/12
*/

inherit "/std/armour";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include <macros.h>

create_armour() {
  set_name(({"gloves","pair of gloves","leather gloves", "brown leather gloves"}));
  set_pname("pairs of brown leather gloves");
  set_short("pair of brown leather gloves");
  set_pshort("pairs of brown leather gloves");
  set_long("This pair of brown leather gloves look like they would give " +
  "some minimal protection to your hands.\n");
  set_default_armour(4,A_HANDS,({ 0, 0, 0 }),0);
  set_ac(2);
  add_prop(OBJ_I_WEIGHT,150);
  add_prop(OBJ_I_VOLUME,120);
  add_prop(OBJ_I_VALUE, 20);
 }
