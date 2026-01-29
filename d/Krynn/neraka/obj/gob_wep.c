inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

void
create_weapon()
{
    set_name("sword");
    set_adj("goblin");
    set_short("goblin sword");
    set_long("It's the standard sword a goblin gets when joining the" +
	     " dragon army.\n");
    set_default_weapon(20, 17, W_SWORD, W_SLASH | W_IMPALE, W_ANYH);
    add_prop(OBJ_I_VOLUME, 400);
}
