/* 	perf_cross.c			Styles.   3 Mar 1993
 */

#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "wild.h"





void
create_room()
{
    set_short("Fisher Road");
    set_long("\n"+
             "Fisher Road.\n"+
             "Part Fisher Road 1.\n"+
             "");

    add_exit(THIS_DIR + "dead_oak","west");
    add_exit(THIS_DIR + "fish_rd_2", "east");

    add_item(({"road", "trail"}),
             "");

	add_item(({"stream"}),
             "");

	add_item(({"sea", "pensea", "Pensea" }),
             "");

	add_item(({"hills", "hill", "mountains", "mountain" }),
             "");


	// Construction add items.

	add_item(({"people","construction people" }),
             "They are rather far away on the other side of the stream and seem to\n"+
		     "be laying the foundations of new houses to come.\n"+
		     "");

	add_item(({"construction", "building", "buildings", "houses" }),
             "Well, for now it just seems the be the foundations to build houses upon.\n");

	add_item(({"forest","trees" }),
             "The forrest is giving way for new land to be built upon as the trees are\n"+
		     "cut down o make way for a expanding Sparkle.\n");

	add_item(({"foundation","foundations" }),
             "It is hard to see from here but they sure seem to be building houses.\n");


    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);

}
