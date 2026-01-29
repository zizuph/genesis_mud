/*
 * File:     chapel_altar
 * Created:  Cirion, 1998.06.07
 * Purpose:  Altar for the monk's chapel. It can double as a
 *           drop-rack for equipment.
 * Modification Log:
 */
#pragma strict_types

#include "defs.h"
#include <composite.h>
#include <filter_funs.h>
inherit MONK_OBJ + "table";
inherit MONKLIB;

void
create_table()
{
    set_name("altar");
    add_name("chapel_altar");

    set_adj(({"simple","wood","hardwood","wooden"}));
    set_short("simple altar");

    set_long("It is a simple altar, made from some dark "
        + "hardwood. Carved all along the altar's surface "
        + "are images of birds and dragons. The surface of "
        + "the altar is smooth and unadorned, save for "
        + "a small inscription carved delicately into the wood.\n");

    set_describe_prefix("Upon a wide, semi-circular marble dais "
        + "filling the western half of the room is a simple altar "
        + "made from dark wood");

}

/*
 * Function name: prevent_leave
 * Description:   Called when an object is trying to leave this container
 *                to see if we allow it to leave. Only monks may
 *                remove things from the altar, as it can act
 *                as a droproom of sorts.
 * Arguments:     object ob - the object trying to leave
 * Returns:       1 - The object is not allowed to leave
 *                0 - The object is allowed to leave
 */
public int
prevent_leave(object ob)
{
#define MONK_CAUGHT_NOALTAR   "_monk_caught_noaltar"

    if(!m_query_monk(this_player()))
    {
        // we have to do this because trying to get multiple things
        // from the altar will result in a message for each one: spam.
        // Set a flag to only send the message once / second.
        if(this_player()->query_prop(MONK_CAUGHT_NOALTAR) != time())
        {
            write("As you reach out for the altar, the room suddenly "
                + "seems to lurch and shift, and you find yourself "
                + "facing the opposite direction.\n");
            say(QCTNAME(this_player()) + " reaches out for the "
                + "altar, but then suddenly lurches away and "
                + "stumbles around blindly.\n");
            this_player()->add_prop(MONK_CAUGHT_NOALTAR, time());
        }

        return 1;
    }
    else
        return 0;
}

