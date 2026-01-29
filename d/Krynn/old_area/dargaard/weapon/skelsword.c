#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <formulas.h>
#include <filter_funs.h>

inherit "/std/weapon";

public void
create_weapon()
{
  set_name("scimitar");
  set_short("black steel scimitar");
  set_long("A wicked looking curved sword. The steel is blackened as if it "+
	   "had been burned.\n");
  set_adj(({"black","steel", "curved"}));
  set_default_weapon(35, 30, W_SWORD, W_SLASH | W_IMPALE, W_ANYH);
  add_prop(OBJ_I_VALUE, 1000);
  add_prop(OBJ_I_WEIGHT, 4500);
  add_prop(OBJ_I_VOLUME, 3000);
}
