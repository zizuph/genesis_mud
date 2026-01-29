inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

void
create_armour()
{
    set_name("mail");
    set_adj("splint");
    set_short("splint mail");
    set_long("It's the standard armour a human gets joining the dragon " +
	     "army.\n");
    set_default_armour(21);
}
