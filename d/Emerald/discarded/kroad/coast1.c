/*
 * COAST1.c
 * Coastal Road Leading to the Ruins of Kamesh
 * - Alaron November 1996
 */

inherit "/std/room";

void
create_room()
{
    set_short("Overgrown, pebbled path");
    set_long("   The wide, flat path is overgrown and littered with "+
	     "small pebbles, stones and rough, dark green weeds. The "+
	     "winding patch of well-trampled grass and weeds continues "+
	     "to the north where it begins to take on the appearance "+
	     "of an actual road. Shadowing the path the cliffs take, "+
	     "the road continues west where a bridge can be seen in the "+
	     "distance. The overgrown path continues south, wandering "+
	     "through patches of weeds and bushes near the edge of the "+
	     "cliffs. The sound of waves crashing against the rocky "+
	     "shore far below the cliff edge fills the air.\n\n");

    add_item( ({"path", "flat path", "wide flat path"}),
	     "The wide, flat path is not much more than an area of "+
	     "well-trod weeds, dirt and vegetation, surrounded by "+
	     "wild plants and overgrowing weeds.\n");

    add_item( ({"pebbles", "stones", "weeds", "green weeds",
		"dark green weeds", "grass", "well-trampled grass",
		"bushes"}),
	     "There are weeds growing up all over the path. They "+
	     "have grown to the point where the path seems more "+
	     "like a barely discernable area of well-trod dirt and "+
	     "grass. Perhaps many years ago this path was a well-used "+
	     "road, but now it is hardly recognizable as anything "+
	     "more than dirt.\n");

    add_item( ({"cliffs", "cliff edge", "cliff edges"}),
	     "The cliffs to the north and east of here mark where "+
	     "the land drops abruptly to the depths below by the "+
	     "ocean. The sounds of the waves crashing against the "+
	     "rocky shore far below drift through the damp, salty "+
	     "air.\n");

    add_exit("coast2", "south");
    add_exit("eroad8", "north");
}
