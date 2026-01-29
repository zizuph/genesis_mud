/* Original    s_road1.c			Styles.   3 Mar 1993
 *
 * Update : Shadowlynx
 * Date   : 15-Nov-2000
 * File   : /d/Genesis/start/human/wild2/s_road1.c
 * Purpose: Follows the stream near Sparkle to the Travellers Guild.
 * Modify : Modified from the original file created by Styles 3-Mar-1993.
 *
 * Update : Styles
 * Date   : 28-Apr-2009
 * File   : /d/Genesis/start/human/wild3/s_road1.c
 * Purpose: To add items in preparation of the construction of a new
 *          expanded version of Sparkle and the surrounding area.
 *
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
             "You move along a bright and well kept road. The ditch beside the road\n"+
             "is filled with flowers and a pleasant smell is in the air. A little\n"+
             "to the northeast across a stream you can see the village of Sparkle.\n"+

			 // Construction description.
			 "To the southeast on the other side of stream you see construction people\n"+
			 "clearing the forest, building something.\n"+
             "");

    add_exit(THIS_DIR + "../wild2/crossroad","north");
    add_exit(THIS_DIR + "s_road2","south");

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

	// Construction add items.
		     "Some construction people seem to be building something south of the\n"+
		     "village.\n"+
             "");


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
