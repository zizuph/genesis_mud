#include "defs.h"

inherit STAND_LIB + "rom";

create_rom()
{
    set_short("Path on the Bree-Hill");
    set_long(
	    "You are going towards the outskirts of Bree-Hill. "+
	    "The grassy fields laying east of here can now be seen "+
	    "and you realize that they are enormouse. You can also see "+
	    "a sign on the house east of here but it is hard to make "+
	    "out what it tells you from here. You can see the true "+
	    "fashion behind the gardens here. Well kept and full of life. "+
	    "The road continues west towards the center of Bree and east "+
	    "towards the last houses in this area.\n");

    add_exit(STAND_DIR + "hill4", "west", 0);
    add_exit(STAND_DIR + "hill6", "east", 0);

    add_item(({"fields", "grassy fields"}),
	    "The vast grassy fields spread out far away, but southeast "+
	    "of here you can spot a road going eastwards.\n");

    add_item(({"sign"}),
	    "You need better glasses to read it from here!");

    add_item(({"garden","gardens"}),
	    "You are stunned by the beautiful look of those gardens here "+
	    "in Bree. The hobbits must have worked hard to make them so "+
	    "beautiful as they are now.\n");

    add_item(({"road","path"}),
	    "The path you are walking at is paved and crafted by the many "+
	    "humans who has lived here in Bree and still live here.\n");

}
