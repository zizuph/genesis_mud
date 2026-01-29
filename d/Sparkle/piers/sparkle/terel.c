#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "defs.h"

void
create_room()
{
    set_short("Berth 5 - Terel");
    set_long("\n"+
      "This is the south pier of the Sparkle harbour.\n" +
      "You are standing on the pier outside a quite modern warehouse." +
      " The south pier extends to the east.\nThere is a sign here" +
      " that reads: Berth 5 - Terel.\n");


    add_item(({"warehouse" }),"");
    add_item(({"pier" }),"");

    add_exit(S_LOCAL_ROOM_DIR + "circle","north");
    add_exit(S_LOCAL_ROOM_DIR + "ware2","south");
    add_exit("newports","east");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}

