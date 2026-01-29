/*
 * eroad12.c
 * Kahlen Road
 * by Alaron September 1, 1996
 */

#include "defs.h"

inherit BASEROAD;

void
create_road()
{
    set_short("Coastal dirt road near a forest");
    set_long("   You stand in the middle of a damp, dirt road which "+
	     "runs along the edge of cliffs which drop off abruptly "+
	     "into an ocean inlet to the west. Large puddles of water "+
	     "cover the road and sections of the road near the cliffs. A "+
	     "mass of low undergrowth covers the entire east edge of the "+
	     "road, eventually giving way to the edge of an enormous "+
	     "forest further to the east. The road slopes upward along "+
	     "the cliff edge to the north and downward parallel to the "+
	     "cliffs to the west. A thick, lingering mist seems to "+
	     "be forming to the west and south of here.\n\n");

    OUTSIDE;
    LIGHT(1);

    add_item( ({"mud", "water", "puddles", "large puddles"}),
	     "Large puddles of water and patches of mud cover the "+
	     "road and the area near the cliffs. As the cliffs gradually "+
	     "descend toward the waterline to the west, more of the ocean "+
	     "spray splashing against the cliffs collects here.\n");

    add_item( ({"cliffs", "west", "north"}),
	     "The cliffside gradually slopes downward to the west and "+
	     "upward to the north as it rounds a corner of the ocean "+
	     "inlet. The majestic white and gray cliffs stand out "+
	     "in contrast with the deep, blue color of the ocean "+
	     "beneath.\n");

    add_item( ({"bushes", "low bushes", "foliage", "green foliage",
		"vegetation", "low undergrowth", "undergrowth"}),
	     "The bushes and low undergrowth bordering the road as it "+
	     "turns the corner to the west seem to be reaching out onto "+
	     "the road, in search of the salty moisture which is "+
	     "collecting on the other side toward the cliffs. Several "+
	     "varieties of the flowers and weeds look quite familiar. Further "+
	     "back to the east the greenery gradually becomes the edge "+
	     "of an enormous forest.\n");

    add_item( ({"flowers", "weeds"}),
	     "Several of the varieties of weeds and bushes in the "+
	     "surrounding greenery look vaguely familiar.\n");


    add_exit(PATH + "eroad11", "north", 0, 1);
    add_exit(PATH + "eroad13", "west", 0, 1);
}
