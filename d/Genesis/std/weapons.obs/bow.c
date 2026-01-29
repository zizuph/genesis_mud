/*
 * ~Genesis/std/weapons/bow.c
 *
 * Base bow from which others should be derived.
 *
 * WISHLIST
 *    1) True range would be nice.
 *    2) Bow should shoot wielded arrows, replacing them from quiver.
 *    3) A bow might act as a very weak staff if a command is given
 *       else, no attack.
 *    4) Different bows should have different tohit/pen variables, even
 *       for the same arrows.  "bow" should be usable for crossbows also.
 *    5) Bows should have sizes, which match arrow sizes. (Might get away
 *       with too long, and have too short reduce tohit/pen)
 *    6) Should have to string (and unstring) bows...requiring strength.
 *    7) Strings can break, and the "pull" of the bow would be strength 
 *       related too.
 */
#pragma save_binary

inherit "/d/Genesis/std/weapons/missile_caster";

#include "wa_types.h"
#include "stdproperties.h"

/*
 * Function name: create_bow
 * Description: Go ahead and make the bow, but ensure the values are
 * reasonable when we're done.
 */
void
create_bow()
{
    ::create_missile_caster();
}

/*
 * Function name: create_missile_caster
 * Description: Set defaults for bows, call function to configure this bow.
 */
nomask void
create_missile_caster()
{
    set_material("oak");
    add_prop(OBJ_I_VOLUME, 300);

    create_bow();
    set_name("bow");
    set_hands(W_LEFT);
}