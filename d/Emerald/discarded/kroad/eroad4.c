/*
 * road1.c
 * Kahlen Road
 * by Alaron August 31, 1996
 */

#include "defs.h"

inherit BASEROAD;

void
create_road()
{
    set_short("Coastal road");
    set_long("   The brisk coastal breeze blows against the cliff face "+
	     "just to the south, sending a salty spray of moisture over "+
	     "the entire road. The cliffs turn a sharp and ragged corner "+
	     "to the south and continue to border the road on the west "+
	     "side. The low, overgrown vegetation and greenery off to the "+
	     "east seems to creep out onto the road, as if reaching for "+
	     "the salty moisture of the sea. Off to the east and north "+
	     "the greenery and vegetation seems to melt into the forest "+
	     "edge. Dozens of small puddles and "+
	     "patches of mud litter the surroundings between the road "+
	     "and the sharp dropoff of the cliffs. The road follows the "+
	     "coastline to the north and east.\n\n");

    OUTSIDE;
    LIGHT(1);
    
    add_item( ({"cliffs", "south", "dropoff", "west", "cliff face"}),
	     "The cliffs rise sharply out of the ocean and just up "+
	     "to a plateau which serves as the base for the road "+
	     "you are standing on. The majestic white and gray rock "+
	     "stands out in contrast with the deep, dark blue of the "+
	     "ocean below. Looking out over the cliffs provides a very "+
	     "panoramic view of the ocean.\n");

    add_item( ({"ocean", "panoramic view", "view"}),
	     "You look out over the the cliffs and are amazed at the "+
	     "brilliant blue color of the vast ocean below. Further "+
	     "to the horizon you can see a twin set of cliffs on the "+
	     "other side of the tremendous inlet which serves as the "+
	     "port for the Emerald continent.\n");

    add_item( ({"puddles", "mud", "patches of mud"}),
	     "There are dozens of patches of mud and puddles littering "+
	     "the landscape where moisture from the sea spray against the "+
	     "cliffs has collected.\n");

    add_item( ({"bushes", "low bushes", "foliage", "green foliage",
		"vegetation", "greenery" ,"overgrown greenery"}),
	     "The thick greenery runs all around the inside of the "+
	     "road opposite the cliffs. Further back, beyond sections of "+
	     "weed and plant life which look vaguely familiar, the "+
	     "low undergrowth seems to slowly melt into the edge of a "+
	     "forest.\n");


    add_item( ({"flowers", "weeds", "vines", "plant life"}),
	     "Quite a bit of the flowers, weeds, vines and other "+
	     "plant life in the greenery look vaguely familiar to "+
	     "you.\n");

    add_exit(PATH + "eroad3", "north", 0, 1);
    add_exit(PATH + "eroad5", "east", 0, 1);
}
