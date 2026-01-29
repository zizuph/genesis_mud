inherit "/std/room";

#include "examples.h"

void
create_room()
{
    set_short("on a bridge");
    // NOT: "On a bridge."

    set_long("The road crosses a large river here on a wooden bridge.\n");
    // keep the long description nice and short.

    //  and put the details into the item descriptions
    add_item(({"road", "street", }),
        "South of the river, the south is running in a straight line "
      + "across a wide empty plain, while to the north it disappear "
      + "into a dense forest.\n");
    add_item(({"forest", "wood", }),
        "A dense forest is rising on the northern bank of the river. "
      + "It seems to be made up mainly from fir trees.\n");
    add_item(({"trees", "firs", "fir trees", }),
        "A dense wall of fir trees is all that can be seen of the forest "
      + "growing on the northern bank of the river.\n");
    add_item(({"plain", "plains", }),
        "A wide empty plain is stretching south of the river as far "
      + "as one can see. The road is running across the plain in a "
      + "straight line. Besides the road there is only one feature "
      + "standing out, a small group of bushes several hundred yards "
      + "south of the river.\n");
    add_item(({"bushes", "group", "group of bushes", }),
        "It is hard to make out any details from this far off. It "
      + "looks like a small group of bushes, conspicious only because "
      + "it is the only one visible on the plain.\n");
    add_item(({"river", "stream", "water", }),
        "The river is about fifty yards wide here. The water is flowing "
      + "slowly from east to west.\n");
    add_item(({"bridge", "wooden bridge", }),
        "The bridge spans the river in two wide arches which both rest "
      + "with one end on a stone pier in the middle of the river. "
      + "Except for the pier, the bridge has been built from wood. "
      + "At the southern end of the bridge there is a small wooden "
      + "booth.\n");
    add_item(({"pier", "stone pier", "arch", "arches", }),
        "Both arches of the bridge rest with one end on a bank and "
      + "with the other on a stone pier in the middle of the river.\n");
    add_item(({"booth", "toll booth", }),
        "At the southern end of the bridge, there is a small booth. "
      + "It might be used by the guards in bad weather.\n");

    add_exit(STAND_DIR + "forest_rd1", "north", 0, 1);
    add_exit(STAND_DIR + "s_bridge",   "south", 0, 1);
}

