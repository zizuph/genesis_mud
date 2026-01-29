#include "/d/Krynn/common/defs.h"
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

inherit "/std/armour";

public void
create_armour()
{
  set_name("shield");
  set_short("black steel shield");
  set_long("An old charred steel shield, remarkable similar to those "+
	   "used by Solamnian Knights.\n");
  set_adj(({"black","steel"}));
  set_ac(20);
  set_am(({0,0,0}));
  set_at(A_SHIELD);
  add_prop(OBJ_I_VALUE, 400);
  add_prop(OBJ_I_VOLUME, 1300);
  add_prop(OBJ_I_WEIGHT,2000);
}
