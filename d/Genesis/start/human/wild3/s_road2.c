/* 	s_road2.c			Styles.   3 Mar 1993
 */

#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "wild.h"

void
create_room()
{
    set_short("Bright road");
    set_long("\n"+
             "Bright road.\n"+
             "The road runs north to south and a small trail is forking to the east\n"+
             "where it follows a stream towards the sea. A steep hill and some mountains\n"+
             "to your west seem to make passage that way rather difficult.\n"+

             // Construction description.
			 "On both sides of the stream to the east, you can see construction work\n"+
			 "going on. Aparantly the construction people are building something on\n"+
			 "a large scale.\n"+
             "");

    add_exit(THIS_DIR + "s_road1","north");
    add_exit(THIS_DIR + "s_road3","south");
    add_exit(THIS_DIR + "stream2","east");

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
