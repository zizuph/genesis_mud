inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

void
create_armour()
{
    set_adj("leather");
    set_short("leather armour");
    set_long("It's the standard armour a goblin gets joining the dragon " +
	     "army.\n");
    set_default_armour(12);
}
