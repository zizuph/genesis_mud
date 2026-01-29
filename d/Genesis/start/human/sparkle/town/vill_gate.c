#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "../defs.h"

void
create_room()
{
    set_short("Village gate");
    set_long("\n"+
             "You are standing outside the gates of Sparkle.\n"+
             "Leaving the town is a dusty road leading towards a bridge and\n"+
             "the wilderness beyond. Going east inside the stockade you will\n"+
             "end up where it all began, in Sparkle. The cradle of humanity.\n"+
             "");

    add_item(({"gates","road" }),"");

    add_exit(TOWN_DIR + "road2","east");
    add_exit(HUMAN_DIR + "wild2/hump","west");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}
