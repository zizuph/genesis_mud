inherit "/std/armour";
#include "/d/Emerald/defs.h"

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour ()
{
  set_name("boots");
	set_short("pair of leather boots");
	set_adj("leather");
	set_long("A well-crafted pair of leather boots.\n");
	set_ac(5);
	set_am(({ 0, 0, 0}));
   set_at (A_FEET);
}
