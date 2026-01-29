/*
 * eroad11.c
 * Kahlen Road
 * by Alaron August 31, 1996
 */

#include "defs.h"

inherit BASEROAD;

void
create_road()
{
    set_short("Coastal dirt road near a forest");
    set_long("   A very cool, ocean breeze blows up against the cliffs "+
	     "to the west, sending a salty spray across the coastal "+
	     "dirt road. The cliffs are gradually descending toward "+
	     "the waterline to the south. The road is bordered on the east "+
	     "by low greenery which eventually gives way to an enormous, "+
	     "sprawling forest. Patches of mud and puddles of water dot "+
	     "the landscape on the western edge of the road near the "+
	     "cliffs.\n\n");

    OUTSIDE;
    LIGHT(1);

    add_item( ({"cliffs", "west"}),
	     "The cliffs to the west soar vertically out of the dark "+
	     "blue water of the ocean inlet below. As they continue to "+
	     "border the road to the south they gradually begin to "+
	     "slope downward toward the water's edge. Puddles of water "+
	     "and patches of mud dot the landscape near the cliffs.\n");

    add_item( ({"mud", "water", "patches of mud", "puddles of water"}),
	     "Puddles of water and patches of mud scatter the edge of the "+
	     "road near the cliffs to the west. They most likely formed "+
	     "from moisture collecting from the ocean spray which "+
	     "continually blasts up against the cliff face.\n");

    add_item( ({"bushes", "low bushes", "foliage", "green foliage",
		"vegetation", "greenery", "low greenery"}),
	     "Among the various forms of low greenery surrounding the "+
	     "road you notice several kinds of flowers and weeds which "+
	     "look familiar. Further back, the greenery seems to rise "+
	     "up out of the ground and form the edge of an enormous "+
	     "forest.\n");

    add_item( ({"flowers", "weeds"}),
	     "There are several kinds of familiar flowers and weeds "+
	     "scattered among the various low greenery bordering "+
	     "the road.\n");


    add_exit(PATH + "eroad10", "north", 0, 1);
    add_exit(PATH + "eroad12", "south", 0, 1);
}
