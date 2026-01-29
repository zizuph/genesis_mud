/*
 * eroad2.c
 * Kahlen Road
 * by Alaron August 31, 1996
 */

#include "defs.h"

inherit BASEROAD;

void
create_road()
{
    set_short("Dirt road");
    set_long("   The low bushes on the north side of the packed dirt "+
	     "road seem to be growing into the path. Further to the north "+
	     "the vegetation grows and seems to slowly rise up into the "+
	     "edge of a forest. Beyond the dirt road to the southwest, past "+
	     "several patches of mud and puddles is the top of the cliff "+
	     "face. A cool sea breeze constantly lashes against the stone "+
	     "cliff face, making a soft whistling noise. The road continues "+
	     "west and to the south.\n\n");

    OUTSIDE;
    LIGHT(1);
    
    add_item( ({"cliffs", "cliff face", "southwest"}),
	     "The cliffs to the southwest rise steeply out of the deep blue "+
	     "water beneath. An incessant, soft wind blows against the "+
	     "side of the cliff, creating a muffled whistling noise and "+
	     "spraying the path with salty moisture. Beyond the cliffs you "+
	     "can see the ocean.\n");

    add_item("ocean",
	     "It is a vast expanse of deep, blue water.\n");

    add_item( ({"bushes", "low bushes", "foliage", "green foliage",
		"vegetation"}),
	     "The low bushes surrounding the path to the north are "+
	     "wild and overgrown, covering the sides of the road in "+
	     "scraggly vines and wide bushes. Further north the vegetation "+
	     "grows and seemingly melts into the forest edge.\n");

    add_item( ({"flowers", "weeds", "vines"}),
	     "The flowers, weeds, and vines seem to creep out of the foliage "+
	     "on the north side of the path, reaching for the moisture "+
	     "collected by the cliff face. You can see various forms of "+
	     "vegetation in the greenery that look familiar.\n");

    add_item( ({"mud", "puddles", "moisture"}),
	     "Several patches of wet mud and puddles dot the landscape "+
	     "on the south side of the road where moisture blown up from "+
	     "the ocean along the cliff face has collected.\n");

    add_exit(PATH + "eroad1", "west", 0, 1);
    add_exit(OUT_DIR + "f14", "northeast", 0, 2);
    add_exit(PATH + "eroad3", "south", 0, 1);
}

