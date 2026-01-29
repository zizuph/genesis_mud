/* 	orc_vall3.c			Styles.   3 Mar 1993
 */

#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "defs.h"
#include S_DOMAIN_SYS_LINKS

void
create_room()
{
    set_short("Orc valley");
    set_long("\n"+
        "Orc road.\n"+
        "You are in a little wider part of Orc valley. The road runs " +
        "east-west from here and the valley seems to continue far in " +
        "each direction.\n" + "");

    add_exit ("orc_vall2","east");
    add_exit(S_LINK_FAERIE_VALLEY, "west", "@@block_room@@",0,1);

    add_item(({"road","valley" }),
             "");
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);

    add_my_desc("Someone has placed a small sign here.\n");

    add_cmd_item("sign", "read",
                 "The road into the mountains has been closed, but passage " +
                 "to other places may be obtained from boats at Sparkle.\n");

    add_item("sign",
             "The road into the mountains has been closed, but passage " +
                 "to other places may be obtained from boats at Sparkle.\n");
}


int
block_room()
{
if (this_player()->query_wiz_level()) return 0;

write("An avalanche has occured and blocked the road.\n");
return 1;
}

