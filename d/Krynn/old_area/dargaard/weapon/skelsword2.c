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
  set_name("sword");
  set_short("two handed sword");
  set_long("This is quite an impressive sword. The blade is a full meter "+
	   "and has not lost it's sharpness over the years. Like " +
	   "everything else here, it has lost it's shimmer, and seems to " +
	   "have been scorched by a fire.\n");
  set_adj("two handed");
  set_default_weapon(35, 40, W_SWORD, W_SLASH | W_IMPALE, W_BOTH);
  add_prop(OBJ_I_VALUE, 1350);
  add_prop(OBJ_I_WEIGHT, 10000);
  add_prop(OBJ_I_VOLUME, 5500);
}
