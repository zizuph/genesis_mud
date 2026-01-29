#include "/d/Krynn/common/defs.h"
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

inherit "/std/armour";

public void
create_armour()
{
  set_name("platemail");
  set_short("blackened platemail");
  set_long("You weren't sure from looking at the weapons, but the armour "+
	   "is obviously of Solamnian make. Ornate designs of vines of " +
	   "roses detail the armour, though it is only barely noticeable " +
	   "through the blackened metal. You finally manage to take your " +
	   "eyes off the intricate armour, but are left wondering where " +
	   "these foul creatures came across Solamnian armour.\n");
  set_adj("blackened");
  set_ac(40);
  set_am(({0,0,0}));
  set_at(A_BODY);
  add_prop(OBJ_I_VALUE, 0);
  add_prop(OBJ_I_VOLUME, 200);
  add_prop(OBJ_I_WEIGHT, 250);
}
