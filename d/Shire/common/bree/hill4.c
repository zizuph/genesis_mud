#include "defs.h"

inherit STAND_LIB + "rom";

create_rom()
{
    set_short("Crossing in the living area of Bree.\n");
    set_long(
	    "You have reached a crossing where the path separates in three directions. "+
	    "East is where the humans live, and north towards where the hobbits "+
	    "mainly live. Green grass and other plants dominate the view here "+
	    "and the air smells good. Further east a rather newly built "+
	    "house can be seen. North of here some strange looking holes can be "+
	    "spotted.\n");

    add_exit(STAND_DIR + "hill3", "west", 0);
    add_exit(STAND_DIR + "hill5", "east", 0);
    add_exit(STAND_DIR + "nhill1", "north", 0);

    add_item(({"grass"}),
	"You wonder if you havent seen this kind of grass before.");

    add_item(({"plants"}),
	    "There are many different plants here, and only skilled herbalists "+
	    "can tell what all these plants are being used for.\n");

    add_item(({"house"}),
	    "It is difficult to see the house proper from here, maybe if you "+
	    "closer to it you can see better.\n");

}
