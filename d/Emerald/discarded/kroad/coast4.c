/*
 * COAST4.c
 * This is the coastal road / path leading to the monk ruins.
 * Alaron November 1996
 */

inherit "/std/room";

void
create_room()
{
    set_short("Fog-covered overgrown path");
    set_long("   Peering through the damp, gray darkness here you notice a " +
        "stark contrast between this area and the brilliant sunlight " +
        "above. The path is not much more than an area of the grass " +
        "which has been trampled and flattened by years of use for " +
        "wagon and horse traffic. It does however, look like it has " +
        "not seen much traffic lately. The ground is damp with "+
	"the moisture of the cloud of fog which looms perpetually " +
        "over the area. Off in the distance to the southeast, " +
        "you can see the looming, dark outlines of a building. " +
        " The path continues to the southeast and to the north.\n\n");

    add_item( ({"darkness", "damp darkness", "gray darkness", 
        "damp gray darkness", "fog", "mist"}),
	"The eerie, cold darkness hangs over the path like a perpetual "+
	"shadow, never relenting in its efforts to keep the path dark "+
	"and soaked with moisture. Peering through the darkness you notice "+
	"tall, looming outline of a building in the distance to the "+
	"southeast.\n");
	   
    add_item( ({"shapes", "outline", "dark outline", "building",
		"outline of a building", "dark outline of a building",
		"dark building"}),
        "The dark shapes looming just beyond the range of visibility through "+
	"the fog seem like they could be a building of some "+
	"kind. From here they are nothing more than dark outlines, though.\n");

  add_item( ({"green bushes", "grass", "weeds", "ground"}),
	    "The ground is moist and covered with trampled, flattened "+
	    "bushes and grass. You have to struggle to see the ground "+
	    "through the thick mist.\n");

  add_exit("coast3", "north");
  add_exit("coast5", "southeast");
}


















