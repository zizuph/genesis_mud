/*
 * th_1.c
 *
 * This is the 'entrance' room into the town hall.
 *
 * Khail - May 16/97
 */
#pragma strict_types

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
    set_short("wide walkway");
    set_long("   You are on a wide walkway east into the town " +
        "hall, and west out onto the street. North and " +
        "south of the walkway extend the grass-covered " +
        "confines of the courtyard, bounded by a high " +
        "stone wall. The town hall isn't all that much " +
        "different from the other buildings in size, " +
        "being only a single level, but has been " +
        "constructed from wood.\n");

    add_item(({"wall"}),
        "The town hall and its courtyard are surrounded " +
        "on all sides by a high stone wall.\n");
    add_item(({"courtyard"}),
        "It's not much of a courtyard, is it? More of a " +
        "front lawn, really.\n");
    add_item(({"town hall"}),
        "The town hall rises to the east, but it's " +
        "only a single story. The only thing that sets " +
        "it apart from other buildings in Port Macdunn " +
        "is the more expensive wood construction.\n");
    add_item(({"walkway", "ground", "cobblestones"}),
        "The walkway connects the town hall to the " +
        "street to the west, and has been paved with " +
        "cobblestones.\n");

    add_exit(ROOM + "th_n_court", "north");
    add_exit(ROOM + "th_2", "east");
    add_exit(ROOM + "th_s_court", "south");
    add_exit(ROOM + "road_8_4", "west");
}
