// white clothes for the snob_elf in tomato-drop quest.
// made by Kazz, March 1995

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour ()
{
  set_name ("clothes");
  set_pname ("sets of clothes");
  set_short ("white clothes");
  set_pshort ("sets of white clothes");
  add_adj("white");
  set_long ("Set of white, spotless clothes.\n");
  set_ac (7);
  set_at (A_BODY);
  add_prop(OBJ_I_WEIGHT, 3000);
  add_prop(OBJ_I_VOLUME, 2000);
}
