/*
 * This is the tenth room on first road in Port Macdunn.
 *
 * Khail - May 16/97
 */
#pragma strict_types

#include "room.h"
#include "/d/Khalakhor/sys/defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit ROADBASE;

public string
query_dir_to_jail()
{
    return "east";
}

public string
warehouse_mesg()
{
    object room;

    if (!(objectp(room = TP->query_prop(LIVE_O_LAST_ROOM))))
        return "To the east lies what appears to be a warehouse " +
            "district.";

    if (file_name(room) == (ROOM + "road_1_9"))
        return "You seem to be approaching a warehouse district " +
            "to the east.";
    if (file_name(room) == (ROOM + "road_1_11"))
        return "The warehouse district is now behind you to the " +
            "east.";
    return "To the east lies what appears to be a warehouse " +
        "district.";
}

public void
create_road()
{
    set_short("harbourfront road");
    set_long("   You are on a road leading east and west along " +
        "the southern edge of Port Macdunn, on the north " +
        "shore of the harbour, Cala Fasgadh. The town itself " +
        "lies beyond the grassy patch between buildings to the " +
        "north. The town is " +
        "nothing particularly amazing in size, but the large " +
        "stone buildings are well made, and the dirt roads well " +
        "maintained. To the south, you can see the numerous " +
        "piers of Port Macdunn jutting out into the waters of " +
        "Cala Fasgadh. " + VBFC_ME("warehouse_mesg") + "\n");

    add_exit(ROOM + "road_12_8", "north");
    add_exit(ROOM + "road_13_9", "east");
    add_exit(ROOM + "road_11_9", "west");
}
