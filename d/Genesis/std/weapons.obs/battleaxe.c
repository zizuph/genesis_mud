/*
 * /d/Genesis/std/weapons/battleaxe.c
 *
 * A dwarf's best friend.
 *
 * Wishlist:
 *
 */
#pragma save_binary

inherit "/d/Genesis/std/weapons/axe";

#include "wa_types.h"
#include "stdproperties.h"

/*
 * Function name: create_battleaxe
 * Description: Go ahead and make the weapon, but ensure the values are
 * reasonable when we're done.
 */
void
create_battleaxe()
{
    ::create_axe();
}

/*
 * Function name: create_weapon
 * Description: Go ahead and make the weapon, but ensure the values are
 * reasonable when we're done.
 */
nomask void
create_axe()
{
    set_material("steel");
    add_prop(OBJ_I_VOLUME, 1500);

    create_battleaxe();

    set_name("battleaxe");
    set_hit(27);
    set_pen(27);
    set_pm(({5, 0,-5}));
}