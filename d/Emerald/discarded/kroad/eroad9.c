/*
 * eroad9.c
 * Kahlen Road
 * by Alaron September 1, 1996
 * Noiseroom by Jaypeg - 13th Feb 97
 */

#include "defs.h"

inherit "/d/Emerald/kroad/vamp/lib/out_vamp_tellroom";


void
create_ov_road()
{
    set_short("Coastal road");
    set_long("   A cool, ocean breeze brushes against your face as you "+
	     "survey the dirt road. It is covered on the southern edge "+
	     "by overgrown greenery and vegetation. The greenery eventually "+
	     "gives way to the edge of an enormous forest. The northern "+
	     "edge of the road is bordered by puddles, patches of mud, and "+
	     "the abrupt drop-off of the cliff faces. The road continues to "+
	     "the west and east from here. A massive stone bridge can be "+
	     "seen to the northeast.\n\n");

    OUTSIDE;
    LIGHT(1);
    
    add_item( ({"bridge", "massive bridge", "massive stone bridge"}),
	     "The massive stone bridge is a marvel of engineering. From "+
	     "this vantage point it appears to be one piece of smoothly "+
	     "carved stone designed to give the impression of fluid "+
	     "motion. Looking at the bridge for too long has a dizzying "+
	     "effect.\n");

    add_item( ({"cliffs", "north", "cliff face"}),
	     "The cliffs to the north drop off abruptly and run almost "+
	     "vertically down to the channel below. The only visible "+
	     "crossing of the channel is a massive stone bridge to the "+
	     "northeast.\n");

    add_item( ({"puddles", "mud", "patches of mud"}),
	     "The puddles and patches of mud are seemingly caused by the "+
	     "ocean spray against the cliffs causing moisture to collect "+
	     "alongside the northern border of the road where there are "+
	     "not enough plants to absorb the water.\n");

    add_item( ({"bushes", "low bushes", "foliage", "green foliage",
		"vegetation", "greenery", "overgrown greenery"}),
	     "The greenery bordering the road on the southern edge "+
	     "is overgrown and seems to be reaching toward the other "+
	     "side of the road where the moisture has collected. Among "+
	     "the various forms of plant life and flowers you notice "+
	     "several kinds that look familiar.\n");

    add_item( ({"flowers", "plant life"}),
	     "Among the flowers and plant life you can see several varieties "+
	     "which look familiar to you.\n");

    add_exit(PATH + "eroad7", "east", 0, 1);
    add_exit(PATH + "eroad10", "west", 0, 1);
}
