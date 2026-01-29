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
  set_name("spear");
  set_short("long jagged spear");
  set_long("As you look at the long jagged spear, you can't help "+
	   "shivering at the barbs on the blade. The mere sight of them " +
	   "leaves you very thankful that they are not embedded in " +
	   "your flesh.\n");
  
  set_adj(({"long","jagged"}));
  set_default_weapon(35, 35, W_POLEARM, W_SLASH | W_IMPALE, W_BOTH);

  add_prop(OBJ_I_VALUE, 1250);
  add_prop(OBJ_I_WEIGHT, 10000);
  add_prop(OBJ_I_VOLUME, 6500);
}
