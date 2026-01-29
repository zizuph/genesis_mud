/*
 *
 * WISHLIST:
 *     1) Using your fist while holding a sling would be OK.
 *     2) You could wield a sling and something else, but not load
 *        and fire it.
 */
#pragma save_binary

inherit "/d/Genesis/std/weapons/sword";

#include "wa_types.h"
#include "stdproperties.h"

/*
 * Function name: create_sling
 * Description: Go ahead and make the weapon, but ensure the values are
 * reasonable when we're done.
 */
void
create_sling()
{
    ::create_sword();
}

/*
 * Function name: create_weapon
 * Description: Go ahead and make the weapon, but ensure the values are
 * reasonable when we're done.
 */
nomask void
create_sword()
{
/*
 * Should be based on material/magic etc.
 */
    set_material("steel");
    add_prop(OBJ_I_VOLUME, 300);

    create_sling();

    set_name("sling");
    set_hit(27);
    set_pen(27);
    set_dt(W_IMPALE | W_SLASH | W_BLUDGEON);
    set_pm(({5, 0,-5}));
}