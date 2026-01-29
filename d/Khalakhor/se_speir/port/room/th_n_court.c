/*
 * th_n_court.c
 *
 * This is the north courtyard for the town hall in Port
 * Macdunn.
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
    set_short("grassy courtyard");
    set_long("   You are standing in the northern part of " +
        "the courtyard of Port Macdunn's town hall. " +
        "It's rather plain, and looks more like a lawn " +
        "than the courtyard of any sort of nobility. " +
        "There's absolutely nothing of any immediate " +
        "interest here. The outer wall bounds the " +
        "courtyard to the north and west, the wall " +
        "of the town hall itself rises to the east, " +
        "and a walkway bisects the courtyard to the " +
        "south.\n");

    add_item(({"wall"}),
        "A high stone wall marks the edge of the courtyard " +
        "to the north and west.\n");
    add_item(({"town hall"}),
        "The town hall rises to the east, but it's " +
        "only a single story. The only thing that sets " +
        "it apart from other buildings in Port Macdunn " +
        "is the more expensive wood construction.\n");
    add_item(({"walkway"}),
        "You can't see much of it from here, but " +
        "it leads into the town hall.\n");
    add_item(({"ground", "grass"}),
        "The ground here is simple grass.\n");

    add_exit(ROOM + "th_1", "south");
}
