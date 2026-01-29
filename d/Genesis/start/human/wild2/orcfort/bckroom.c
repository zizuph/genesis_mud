#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "local.h"

void
create_room()
{
    set_short("Bar backroom");
    set_long("This is the backroom to the bar. Usually there is a\n"
             + "card game of some sort being played. It seems that now\n"
             + "the table and chairs seem to be smashed to pieces, no \n"
             + "doubt a result from a previous 'friendly' game of cards.\n"
             + "Other than the pile of smashed wood on the floor, the\n"
             + "room is pretty much barren.\n");

    add_item(({"smashed table", "table", "smashed wood", "wood"}),
             "Seems very smashed.\n");
    add_item(({"smashed chairs", "chairs", "chair"}),
             "You would not want to try and sit in these!\n");
    add_item(({"stones", "stone"}), "They are all cut the wrong way, "+
    "and are the incorrect size.\n");

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_S_MAP_FILE, "orc_temple.txt");

    add_exit(ORC+"inn2", "south");
}
