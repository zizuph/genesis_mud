#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "../defs.h"

void
create_room()
{
    set_short("4th floor");
    set_long("\n"+
             "The 4th floor.\n"+
             "You are in a short corridor with many doors. Next to the stairs\n"+
             "you can see a small sign. The doors appear to be numbered 1 - 8.\n"+
             "");

    add_item(({"floor","door" }),"");
    add_item(({"stairs" }),"The stairs lead up to the attic as well as down to the third floor.\n"+
    "");
    add_item(({"doors" }),"You see nothing special about them.\n"+
    "");
    add_item(({"sign" }),"@@sign");

    add_exit(TOWN_DIR + "l3", "down");
    add_exit(TOWN_DIR + "l5", "up");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}
