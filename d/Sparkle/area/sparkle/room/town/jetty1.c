#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "defs.h"

void
create_room()
{
    set_short("On the jetty");

    set_long("\n"+
             "You're walking the slippery stones of the jetty.\n"+
             "It was built long ago to protect the harbour from the\n"+
             "wrath of the sea. The jetty continues further south.\n"+
             "");

    add_item(({"jetty" }),"The stones are rather slippery so walking is not that easy.\n");
    add_item(({"stones" }),"It must have been a giants task to place these stones.\n"+
    "Each and every one is large enough to weigh a ton.\n"+
    "");

    add_exit(S_DOMAIN_PIERS_DIR + "sparkle/gont", "west");
    add_exit("jetty2","south");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}

