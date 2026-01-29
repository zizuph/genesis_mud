#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "../defs.h"

void
create_room()
{
    set_short("Berth 5, west pier");
    set_long("\n"+
      "You're standing on the pier outside a quite modern warehouse.\n"+
      "The south pier lies east from here.\n"+
      "");


    add_item(({"warehouse" }),"");
    add_item(({"pier" }),"");

    add_exit(TOWN_DIR + "pier4","north");
    add_exit(TOWN_DIR + "ware2","south");
    add_exit(TOWN_DIR + "pier6","east");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_my_desc("There is a sign here marked 'Berth 5'\n");
}
