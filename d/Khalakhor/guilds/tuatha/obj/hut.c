/* File         : /d/Khalakhor/guilds/tuatha/obj/hut.c
 * Creator      : Teth@Genesis
 * Copyright:   : Daniel Mosquin
 * Date         : March 18, 1999
 * Purpose      : The hut object which can be interacted with. They are
 *                placed in rooms.
 * Related Files: /d/Khalakhor/std/object
 * Comments     : TODO: add support for burning
 *                      is it possible to make it such that they do not
 *                      regenerate with a reboot, but instead via time?
 *                      perhaps that is too much detail.
 * Modifications:
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Khalakhor/std/object";

#include <stdproperties.h>

#include "../guild.h"

/*
 * Function name : create_khalakhor_object
 * Purpose       : The constructor function.
 */
public void
create_khalakhor_object()
{
    set_name("hut");
    set_adj("thatch");
    set_short("thatch hut");
    set_long("This is a thatch hut.\n");

    add_prop(OBJ_M_NO_GET, "It is not possible to get a thatch hut.\n");

}

