/*
 * A base room for the Ways
 *
 * Coded by Igneous
 */

inherit "/d/Khalakhor/std/room";

#include <stdproperties.h>
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/terrains.h"

void
create_khalakhor_room()
{
    set_short("fog ladden path");
    set_long("This is a pathway in the ways.");

    add_prop(ROOM_I_INSIDE, 1);
}

