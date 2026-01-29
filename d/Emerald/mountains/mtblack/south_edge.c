inherit "/std/room";

#include "/d/Emerald/defs.h";

void create_room()
{
    set_short("Southern Edge");
     set_long(("You stand on the southern edge of the "+
        "summit of Mount Black and survey the scene. You now can see "+
        "far across the land to the south where an incredible "+
        "view awaits your eyes. To the north is the top of the mountain.\n"));
    add_item(({"summit", "mountain", "Mount Black"}),
       ("The summet of Mount Black rises high above the "+
        "rest of Emerald. On it you have a fantastic view of the scene.\n"));
    add_item(({"view","scene"}), ("The scene is a picturesque one with "+
	"rolling valleys, meandering streams, and jutting peaks.\n"));
    add_item("streams","The streams are meandering their way through the "+
	"valleys lazily and laconicaly.\n");
    add_item("valleys","The valleys are deep and pictoresque.\n");
    add_exit(MBLACK_DIR + "top", "north");
    add_exit(MBLACK_DIR + "south_shelf", "down");
}
