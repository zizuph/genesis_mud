#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "../defs.h"

void
create_room()
{
    set_short("Sparkle Road");
    set_long("\n"+
             "You're walking down the road. To your south is the\n"+
             "adventurers guild. A place well worth a visit.\n"+
             "");

    add_item(({"guild","road" }),"");

    add_exit(TOWN_DIR + "road2","north");
    add_exit(TOWN_DIR + "adv_guild","south");
    add_exit(TOWN_DIR + "road4","east");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}
