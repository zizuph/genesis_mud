/*
 * eroad6.c
 * Kahlen Road
 * by Alaron August 31, 1996
 * Noiseroom added by Jaypeg - 13th Feb 97
 */

#include "defs.h"

inherit "/d/Emerald/kroad/vamp/lib/out_vamp_tellroom";


void
create_ov_road()
{
    set_short("Coastal road at the edge of a bridge");
    set_long("   You stand on the edge of a hard-packed dirt road. The road "+
	     "travels west from this point south of a forest and just north "+
	     "of the edge of the cliffs. The forest seems to press in upon "+
	     "the road, forcing you onto the bridge which leads across the "+
	     "channel to the south. The massive stone bridge seems to drip "+
	     "out of the side of the cliffs and melt into the other cliff; its "+
	     "architecture smooth, flowing and rounded. A mass of overgrown "+
	     "greenery seems to creep onto the road along its northern "+
	     "edge.\n\n");

    OUTSIDE;
    LIGHT(1);

    add_item( ({"bridge", "massive bridge", "massive stone bridge"}),
	     "The massive stone bridge seems to drip out of the cliff face "+
	     "and melt southward across the channel and into the side "+
	     "of the cliff on the other side of the water. The design of "+
	     "the bridge is smooth and flowing, with lots of curves and "+
	     "sweeping lines, giving you the impression of a flowing, "+
	     "almost liquid stone.\n");

    add_item( ({"cliffs", "south", "edge of the cliffs", "edge of cliffs"}),
	     "The cliffs to the south drop off abruptly and leave in their "+
	     "place a smooth, massive stone bridge which spans the channel. "+
	     "The cliffs on the other side are nearly identical to those "+
	     "on this side of the water. The sound of churning water can "+
	     "be heard far below in the channel.\n");

    add_item( ({"bushes", "low bushes", "foliage", "green foliage",
		"vegetation", "greenery"}),
	     "The overgrown greenery which runs along the road's northern "+
	     "edge seems to creep out onto the road, reaching for the "+
	     "salty moisture collecting on the edge of the road near "+
	     "the cliffs. Scattered among the hundreds of reaching "+
	     "vines are various forms of flowers and plant life which "+
	     "you recognize. Further back from the road, the greenery "+
	     "seems to rise up out of the ground and melt into the "+
	     "edge of a forest.\n");

    add_item( ({"flowers", "weeds", "vines", "plant life"}),
	     "There are various forms of recognizeable plant life "+
	     "scattered among the greenery bordering the trail's "+
	     "northern edge.\n");


    add_exit(PATH + "eroad5", "west", 0, 1);
    add_exit(PATH + "bridge", "south", 0, 1);
}
