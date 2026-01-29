/*
 * th_2.c
 *
 * This is the foyer for the town hall of port macdunn.
 *
 * Khail - June 4/97
 * modified: 03/12/01  -- Tomas
             Changed south exit to point to the hall of records, joinroom
             for the racial clans of khalakhor guild
 *
 */
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include "room.h"

inherit "/d/Khalakhor/std/room";

public int *
query_local_coords()
{
    return ({9,4});
}

public int *
query_global_coords()
{
    return VILLAGE_COORDS;
}


public void
create_khalakhor_room()
{
    set_short("bright foyer");
    set_long("   You've entered the brightly lit foyer of " +
        "Port Macdunn's town hall. Richly polished wood " +
        "panels on the walls give the room a slightly " +
        "orange tinge. South of here is a large hall filled " +
        "with shelves containing books and various parchment. To the east " +
        "seems to be some sort of common room, " +
        "and to the north lies the main reception room. " +
        "A doorway opening onto the courtyard stands " +
        "to the west.\n");

    add_item(({"walls"}),
        "The walls of the building are covered in well crafted "+
        "wooden panels.\n");
    add_item(({"panels", "wooden panels"}),
        "The panels are the product of a master carpenter, "+
        "quite possibly made from oak.\n");
    add_item(({"walkway"}),
        "You can't see much of it from here, but " +
        "it leads out into the street.\n");
    add_item(({"ground", "floor"}),
        "The floor of the room has been constructed from " +
        "tightly-jointed planks.\n");
    add_item(({"planks"}),
        "Judging from the amount of wear, this room " +
        "receives both a lot of visitors, as well as " +
        "upkeep to maintain the strength of the flooring.\n");
    add_item(({"ceiling"}),
        "The ceiling is lightly arched, and covered in " +
        "the same panels which adorn the walls.\n");

    INSIDE;

    add_exit(ROOM + "th_3", "north");
    add_exit(ROOM + "th_4", "east");
    add_exit("/d/Khalakhor/guilds/racial/clans/room/joinroom", "south");
    add_exit(ROOM + "th_1", "west");
}
