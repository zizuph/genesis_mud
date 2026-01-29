#pragma save_binary
#pragma strict_types

#include <stdproperties.h>

#include "../defs.h"

inherit "/std/room";

void
create_room()
{
    set_short("At sea outside Sparkle");
    set_long("\n"+
             "You are swimming far out at sea!\n"+
             "Land can be seen to the west but it is just to far to go.\n"+
             "You realize that you are about to drown.\n"+
             "");

    add_item(({"land" }),"It is beyond you strength to swim ashore now.\n"+
    "");

    add_exit(TOWN_DIR + "sea2","west");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
