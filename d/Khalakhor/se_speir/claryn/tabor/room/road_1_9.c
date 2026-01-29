/*
 * road_1_9.c
 *
 * This is part of a road in Tabor Sogh.
 *
 * Khail - Jan 3/98
 */
#pragma strict_types

#include "room.h"

inherit ROADBASE;

public void
create_road()
{
    set_short("narrow dirt road");
    set_long("   You are on a narrow dirt road leading " +
        "north and south through a sleepy little " +
        "fishing village called Tabor Sogh. It appears " +
        "this is the only road in the village, with " +
        "low stone buildings standing on the east " +
        "side, and the rocky shoreline of the Lear " +
        "Min following it to the west. The building " +
        "to the immediate east appears to be someone's " +
        "home. Following the road south will take " +
        "you out of the southern edge of the village.\n");

    add_item(({"building"}),
        "The building to the immediate east is identical " +
        "to almost all of the buildings in the village, " +
        "low stone walls with a thatched roof. However " +
        "it has a lived-in look that a shop or pub " +
        "doesn't have.\n");

    add_exit(ROOM + "road_1_8", "north");
    add_exit(ROOM + "road_1_10", "south", "@@blocked");
    add_exit(ROOM + "home_9", "east");
}

int blocked()
{
   write("That way is blocked for now.\n");
   return 1;
}
