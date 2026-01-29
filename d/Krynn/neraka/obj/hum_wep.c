inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

void
create_weapon()
{
    set_name("sword");
    set_adj("nice");
    set_short("nice sword");
    set_long("It's the standard sword a human gets when joining the dragon " +
	     "army.\n");
    set_default_weapon(25, 27, W_SWORD, W_SLASH | W_IMPALE, W_ANYH);
    add_prop(OBJ_I_VOLUME, 1600);
}
