/*
 * COAST2.c
 * Coastal Road Leading to the Ruins of Kamesh
 * - Alaron November 1996
 */

inherit "/std/room";

void
create_room()
{
    set_short("Overgrown, pebbled path");
    set_long("   You are walking on a wide, flat path. It is littered "+
	     "with pebbles and small rocks which cover over the dirt "+
	     "in sections which have not been devoured by rampant, "+
	     "wild-growing green and brown weeds. The well-trampled "+
	     "grass and weeds form a barely-recognizable pattern "+
	     "in the shape of a path which meanders southeast "+
	     "and north from here. The weeds and bushes continue "+
	     "away from the path to the east and north where "+
	     "they come to an abrupt halt at the tops of the ocean "+
	     "cliffs.\n\n");

    add_item( ({"path", "wide path", "wide flat path", "flat path",
		"road", "down", "dirt", "ground"}),
	     "The wide, flat path is barely recognizeable as "+
	     "such. It is not much more than a long, winding patch "+
	     "of pebbles, trampled grass and weeds. The path is "+
	     "surrounded on both sides by thick bushes and weeds.\n");

    add_item( ({"pebbles", "rocks", "small rocks"}),
	     "The road is littered with pebbles and small rocks. Ages "+
	     "of rain and sea water getting into the soil and freezing "+
	     "during harsh winters has pushed the rocks and pebbles "+
	     "up out of the soil, creating the illusion that the path "+
	     "seems to be 'growing rocks'.\n");
    
    add_item( ({"grass", "weeds", "green weeds", "brown weeds",
		"wild weeds", "wild grass"}),
	     "The thick, low-growing grass runs wild all over the "+
	     "path and road. It has been trampled and flattened along "+
	     "the path from frequent use. You can make out several "+
	     "trenches which have been dug in the ground from years "+
	     "of wagon traffic.\n");

    add_item( ({"trench", "trenches"}),
	     "The trenches in the path have obviously been created by "+
	     "years of frequent wagon traffic trampling the grass and "+
	     "surrounding vegetation.\n");

    add_item( ({"cliffs", "ocean cliffs"}),
	     "The grass and weeds extend out beyond the edge of the path "+
	     "and continue to the north and east until they halt "+
	     "abruptly at the tops of the ocean cliffs. The cliffs "+
	     "mark the edge of the Emerald isle where far beneath "+
	     "you can hear the sounds of the waves crashing against "+
	     "the rocky shore.\n");

    add_exit("coast3", "southeast");
    add_exit("coast1", "north");
}


