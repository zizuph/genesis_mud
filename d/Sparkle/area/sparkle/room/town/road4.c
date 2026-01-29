#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "defs.h"

void
create_room()
{
    set_short("Sparkle Road");
    set_long("\n"+
             "The road is quite crowded here. People are running in all\n"+
             "directions trying to mind their daily business. North is\n"+
             "the Church of Sparkle. It is a hall of life and a holy\n"+
             "place for the human race. South is the Tower of Realms.\n"+
             "");

    add_item(({"church" }),"It is a white building and quite simple on the outside.\n"+
    "However, you can clearly see that is made by skilled hands.\n"+
    "");
    add_item(({"people" }),"Oh they're just commoners. Nothing special about them.\n"+
    "");
    add_item(({"tower","road" }),"");

    add_exit(S_DOMAIN_START_DIR + "human/start","north");
    add_exit("road3","west");
    add_exit(S_AREA_ROOM_DIR + S_AREA_TOWER + "tower","south");
    add_exit("square","east");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}

