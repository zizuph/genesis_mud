// Dusty clothes worn by archaelogist in Avenir dark tunnels.
// made by Boriska@Genesis, Nov 1994

inherit "/d/Avenir/inherit/cloth_arm";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour ()
{
  set_name ("clothes");
  set_pname ("sets of clothes");
  set_short ("dusty clothes");
  set_pshort ("sets of dusty clothes");
  add_adj("dusty");
  set_long ("Set of working clothes, used quite a lot.\n");
  set_ac (7);
  set_at (A_BODY);
  add_prop(OBJ_I_WEIGHT, 3000);
  add_prop(OBJ_I_VOLUME, 2000);
}
