#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "../defs.h"

void
create_room()
{
    set_short("Berth 1, north pier");
    set_long("\n"+
      "This is the north pier.\n"+
      "Ships from far away shores have found a calm place to ride out\n"+
      "many a storm lying here by this very pier. You see a warehouse\n"+
      "to the north and a jetty further east.\n"+
      "");

    add_item(({"warehouse" }),"");
    add_item(({"pier" }),"");
    add_item(({"jetty" }),"");

    add_exit(TOWN_DIR + "ware4","north");
    add_exit(TOWN_DIR + "pier2","west");
    add_exit(TOWN_DIR + "jetty1","east");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_my_desc("There is a sign here that reads 'Berth 1 - Earthsea Gont Port'.\n");
}
