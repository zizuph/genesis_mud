/*
 * eroad10.c
 * Kahlen Road
 * by Alaron September 1, 1996
 */

#include "defs.h"

inherit BASEROAD;

void
create_road()
{
    set_short("Coastal dirt road");
    set_long("   A cool, ocean breeze blows up against the cliffs to "+
	     "the north, sending a fine, salty mist into the air "+
	     "above the road. The dirt road forms a corner here, heading "+
	     "east and south. Bordering the road on the south and west "+
	     "are thick patches of low undergrowth. Further back, "+
	     "the undergrowth becomes more full and eventually becomes "+
	     "the edge of a forest. Further south, as the road progresses "+
	     "deeper into the forest, it slowly becomes consumed by a "+
	     "heavy, lingering mist.\n\n");

    OUTSIDE;
    LIGHT(1);
    
    add_item( ({"cliffs", "north", "cliff face"}),
	     "The cliffs to the north drop off abruptly only a short "+
	     "ways up from the road. Their majestic gray and white faces "+
	     "stand in stark contrast to the deep blue color of the "+
	     "ocean channel churning far below. Puddles of water and patches "+
	     "of mud dot the landscape on the north side of the road near "+
	     "the cliffs.\n");

    add_item( ({"mud", "puddles of water", "patches of mud", "water"}),
	     "The puddles of water and patches of mud dotting the "+
	     "landscape just to the north of the road are most likely "+
	     "the result of water collection over time from the ocean "+
	     "spray which washes up over the top of the cliffs due to "+
	     "the strong winds from below.\n");

    add_item( ({"bushes", "low bushes", "foliage", "green foliage",
		"vegetation", "greenery" ,"overgrown greenery"}),
	     "The greenery bordering the road seems to be stretching out "+
	     "into the road, reaching for the clusters of puddles and "+
	     "collected moisture from the ocean spray near the cliffs. "+
	     "Among the vegetation you recognize several types of flowers "+
	     "and weeds.\n");

    add_item( ({"flowers", "weeds"}),
	     "Among the greenery you notice several kinds of flowers and "+
	     "weeds which look familiar to you.\n");


    add_exit(PATH + "eroad9", "east", 0, 1);
    add_exit(PATH + "eroad11", "south", 0, 1);
}
