inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

create_weapon()
{
    set_name("club");
    set_adj("heavy");
    add_adj("wooden");
    set_short("heavy wooden club");
    set_long("This huge ogre club can only be described as " +
      "a small tree that has been pulled out of the ground! " +
      "While somewhat unwieldy, it looks like it could do some major " +
      "damage if it connected.\n");
    set_default_weapon(15 + random(15), 30 + random(10), W_CLUB, W_BLUDGEON, W_BOTH);
    add_prop(OBJ_I_VOLUME, 10000);
    add_prop(OBJ_I_WEIGHT, 40000);
}
