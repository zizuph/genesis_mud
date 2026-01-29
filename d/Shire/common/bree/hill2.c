#include "defs.h"

inherit "/d/Shire/common/lib/rom";

create_rom()
{
    set_short("Road on the Bree-Hill.");
    set_long(
	    "You are on the Bree-Hill south of a lovely looking house. "+
	    "North of here a house can be spotted, or rather a hole in the ground. "+
	    "You can see yet more houses and holes further eastwards.  "+
	    "There are many nice trees around here. It is easy to see "+
	    "that Hobbits are fond of trees and gardens, and care much about them. "+
	    "The Bree-Hill seems Hobbit like since most men would have cleared "+
	    "the land of trees. The road continues eastwards towards the living "+
	    "area of Bree and southwest towards the center of Bree.\n");

    add_exit(BREE_DIR + "hill1", "southwest", 0, 3);
    add_exit(BREE_DIR + "bhill2", "east", 0, 3);
    /*add_exit(BREE_DIR + "somehouse_i_dont_know_yet", "north", 1);*/

    add_item("house",
	    "You gather that in this house there must live Hobbits because "+
	    "it is all covered with dirt on the outside. It looks like a usual "+
	    "Hobbit house, a plain hole in the ground. But the houses of Hobbits "+
	    "are known to be very nice inside.\n");

    add_item(({"hill","bree-hill"}),
	    "It looks like Hobbits have dwelled here for a long time. Trees still "+
	    "stand here, and there are many lovely gardens here. Many holes can be "+
	    "seen around on the hill.\n");

    add_item(({"trees","tree"}),
	    "There are not many trees here, but those who are here looks very old "+
	    "and well taken care of. Many of the trees here are rather large of size.\n");

}
