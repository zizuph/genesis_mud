#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "../defs.h"

void
create_room()
{
    set_short("The harbour");

    set_long("\n"+
             "You are floating in the harbour!\n"+
             "This is not really a good place to be when the ships come in.\n"+
             "");

    add_item(({"harbour" }),"You're not in a position to spend time looking at the harbour!\n"+
    "Although it is a seagulls view from here, you're about to see\n"+
    "the bottom.\n"+
    "");
    add_item(({"water" }),"It's rather filthy.\n"+
    "");

    add_exit(TOWN_DIR + "sea1","south");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
