/* 	crossroad.c			Styles.   3 Mar 1993
 */

#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "defs.h"

void
create_room()
{
    set_short("At the crossroad");
    set_long("\n"+
             "You are standing in the middle of a crossroad.\n"+
             "East lies the village of Sparkle, the origin of the human race.\n"+
             "West lies Orc road, leading to the orc fortress in Orc Valley.\n"+
             "North is Dark road and south is Bright road. Both are making\n"+
             "their way through wild and unbroken terrain.\n"+
             "");

    add_exit("n_road1","north");
    add_exit("orc_road1","west");
    add_exit("s_road1","south");
    add_exit("hump","east","@@eblock", 0);

    add_item(({"road" }),
             "");
    add_item(({"sparkle","Sparkle","village" }),
             "Sparkle is a small human village by the shore of Pensea.\n");

    add_prop(OBJ_S_WIZINFO, "@@wizinfo");
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);

/*
  clone_object("/d/Genesis/obj/wizquest/mage_stone")->move(this_object());
  */
}

int
eblock()
{
    if (this_player()->query_merc_dog())
        return 0;

    if (interactive(this_player()))
        return 0;
    return 1;
}

string
wizinfo()
{
    return ("If you are to make any caravan or other mass transportation\n"+
            "that will arrive to Sparkle, this is as far as it should go.\n"+
            "You may have it drive by here and pick up passengers etc. but\n"+
            "do not take it into town. The only exception are ships. They\n"+
            "will of course arrive and depart in the harbour. \n");
}

