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
        "You are standing in the middle of Sparkle road.\n"+
        "To your west are the city gates and beyond them the dwellings\n"+
        "of the unknown. It is much safer on this side of the gates\n"+
        "but then, who are you to show fear... Out there lies the future.\n"+
        "");

    add_item(({"gates","gate","road" }),"");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);

    add_exit("road1","north");
    add_exit("vill_gate","west");
    add_exit("road3","south");
}

