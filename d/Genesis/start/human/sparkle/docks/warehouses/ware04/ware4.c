#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "../defs.h"

void
create_room()
{
    set_short("A stone warehouse");
    set_long("\n"+
             "This is a strong stone warehouse.\n"+
             "Many storms and strong winds have polished the stone walls\n"+
             "smooth on the outside while the inner walls are still rugged.\n"+
             "Judging by the the smell, you would say this to be the\n"+
             "place where the fish is stored.\n"+
             "");


    add_item(({"walls" }),"They seem to be as expected. Solid.\n"+
    "");
    add_item(({"room" }),"");

    add_exit(TOWN_DIR + "pier1","south");
    
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}
