inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

void
create_weapon()
{
    set_name("club");
    set_adj("hobgoblin");
    set_short("hobgoblin club");
    set_long("It's the bulky wooden club, the typical weapon of a " +
	     "hobgoblin.\n");
    set_default_weapon(13, 23, W_CLUB, W_BLUDGEON, W_ANYH);
    add_prop(OBJ_I_VOLUME, 4000);
}
