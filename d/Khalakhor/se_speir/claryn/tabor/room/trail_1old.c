/*
 * trail_1.c
 *
 * This is part of the trail north of Tabor Sogh.
 *
 * Khail - Jan 9/98
 */
#pragma strict_types

#include "/d/Khalakhor/sys/defs.h"
#include <stdproperties.h>
#include "room.h"
#define PLAINS "/d/Khalakhor/se_speir/plains/room/"

inherit TRAILBASE;

public string
check_view()
{
    object room = find_object(ROOM + "trail2");
    if (room && TP->query_prop(LIVE_O_LAST_ROOM) == room)
        return "Topping a grassy hill, you one last look at " +
            "the sleepy little village of Tabor Sogh passing " +
            "into the distance behind you. ";
    return "Topping a grassy hill, you see the sleepy " +
        "little village of Tabor Sogh sitting at the edge of the " +
        "sea below you to the south. ";
}

public void
create_khalakhor_room()
{
    create_trail();
    set_long("   @@check_view@@You are on a lightly trampled " +
        "grassy trail which leads down the southern side of the " +
        "hill, ending ultimately in the north end of the fishing " +
        "village below.\n");

    add_exit(PLAINS + "plains_39_26", "north");
    add_exit(ROOM + "trail_2", "south");
}
