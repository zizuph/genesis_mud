#include "/d/Krynn/common/defs.h"
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

inherit "/std/armour";

public void
create_armour()
{
  set_name("cloth");
  set_short("tattered cloth");
  set_long("This cloth appears to have once been a form of clothing, "+
	   "but now is only tattered remains. It sinks of death and decay, " +
	   "and you would like to get rid of it as soon as possible.\n");
  set_adj(({"old","tattered"}));
  set_ac(10);
  set_am(({0,0,0}));
  set_at(A_ROBE);
  add_prop(OBJ_I_VALUE, 0);
  add_prop(OBJ_I_VOLUME, 200);
  add_prop(OBJ_I_WEIGHT, 250);
}
