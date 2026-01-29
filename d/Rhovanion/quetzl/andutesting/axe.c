inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>

create_weapon()
{
    set_name("axe");
    set_adj("woodsman's");
    set_long("This is the large axe of a woodsman.  It is normally " +
        "used for chopping down trees, but would probably make " +
        "a rather brutal weapon in the right hands.\n");
    set_wt(W_AXE);
    set_pen(25);
    set_hit(25);
    set_hands(W_BOTH);
}
