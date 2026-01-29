#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "defs.h"

void
create_room()
{
    set_short("Berth 1 - Earthsea Gont Port");
    set_long("\n"+
      "This is the north pier.\n"+
      "Ships from far away shores have found a calm place to ride out" +
      " many a storm lying here by this very pier. You see a warehouse" +
      " to the north and a jetty further east.\nThere is a sign which" +
      " reads: Berth 1 - Earthsea Gont Port.\n");

    add_item(({"warehouse" }),"");
    add_item(({"pier" }),"");
    add_item(({"jetty" }),"");

    add_exit(S_LOCAL_ROOM_DIR + "ware4","north");
    add_exit(S_DOMAIN_PIERS_DIR + "sparkle/pelargir","west");
    add_exit(S_LOCAL_ROOM_DIR + "jetty1","east");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}

