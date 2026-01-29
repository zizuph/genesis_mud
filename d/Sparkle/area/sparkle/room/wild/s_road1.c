/*
 * Creator: Shadowlynx
 * Date   : 15-Nov-2000
 * File   : /d/Genesis/start/human/wild2/s_road1.c
 * Purpose: Follows the stream near Sparkle to the Travellers Guild.
 * Modify : Modified from the original file created by Styles 3-Mar-1993.
 * Updates:
 */

#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "defs.h"

void
create_room()
{
    set_short("Bright road");
    set_long("\n"+
             "Bright road.\n"+
             "You move along a bright and well kept road. The ditch beside the road\n"+
             "is filled with flowers and a pleasant smell is in the air. A little\n"+
             "to the northeast across a stream you can see the village of Sparkle.\n"+
             "");

    add_exit ("crossroad","north");
    add_exit ("s_road2","south");

    add_item(({"road","stream" }),
             "");
    add_item(({"ditch" }),
             "Some very pretty flowers grow here.\n"+
             "");
    add_item(({"flowers" }),
             "Oh, they are indeed wonderful. Some of nature's fabulous creations.\n"+
             "");
    add_item(({"village","Sparkle","sparkle" }),
             "Ah, the village of Sparkle. It is a most holy place for the human race.\n"+
             "It is also very beautiful where it lies, on the shore of Pensea.\n"+
             "");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}

int
pick(string what)
{
    if (what == "flower" || what == "flowers") {
        write("You realy shouldn't do that. There are not that many left.\n");
        return 1;
    }
    return 0;
}

void
init()
{
    ::init();

    add_action(pick,"pick");
}

