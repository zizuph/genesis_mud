/*
 * Road at the base of Mount Black and the Volcano
 * - Alaron January 1997
 */

#include "default.h"

inherit ROAD;

public int
block_northwest()
{
    write("A rock slide has blocked that way.\n");
    return 1;
}

void
create_road()
{
    set_long("   Standing on a dark gray, stone-covered road, you look "+
	     "up at the towering volcano which dwarfs the road. It is wide "+
	     "and flat-topped, but only reaches about half the height of "+
	     "the towering, black mountain adjacent to the southeast. A "+
	     "thick plume of dark smoke continually drifts up from the "+
	     "flat peak of the volcano. Huge volcanic rocks and piles of "+
	     "rain-hardened volcanic ash litter the road, creating a "+
	     "stifling shade of gray all throughout the area. The side of "+
	     "the volcano is gray and lifeless save for a few patches of "+
	     "bushes and shrubbery. A small footpath leads up and onto "+
	     "the volcano to the northeast.\n\n");

    add_item( ({"rock", "rocks", "ash", "volcanic ash", "volcanic rock",
		"volcanic rocks"}),
	     "The thick piles of volcanic ash are solid now, but "+
	     "were at one point collections of volcanic ash powder. The "+
	     "rain must have caused the ash to mix together and harden "+
	     "when drying, creating ugly little clumps of dark grayness. "+
	     "Laying strewn about the road in between regular rocks and "+
	     "the piles of ash are large, black volcanic rocks that must "+
	     "have rolled down from the side of the volcano.\n");

    add_item( ({"footpath", "path", "small footpath"}),
	     "The small footpath departs from the main road and heads "+
	     "up the side of the volcano at an easy pace. The path "+
	     "disappears around the corner of the volcano further "+
	     "to the northeast.\n");

    add_exit(MBLACK_DIR + "road08", "northwest", block_northwest, 0, 1);
    add_exit("", "northeast", "@@block@@");
    add_exit(MBLACK_DIR + "road06", "southeast");
}

int
block()
{
    write("You consider starting up the side of the volcano onto the "+
          "path, but you notice hundreds of broken trees and other "+
          "devasation along the path from a previous eruption. You decide "+
          "to wait until the wreckage has been cleared to try that "+
          "path.\n");
    return 1;
}
