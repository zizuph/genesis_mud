#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "../defs.h"

void
create_room()
{
    set_short("A newly built warehouse");
    set_long("\n"+
        "This warehouse is modern and very well built.\n"+
        "It contains sacks of grain and flour.\n"+
        "");

       add_item(({"sacks" }),"");
       add_item(({"room" }),"It is quite modern.\n"+
        "");

    add_exit(TOWN_DIR + "pier5","north");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_S_MAP_FILE, "sparkle_city_genesis.txt");
}
