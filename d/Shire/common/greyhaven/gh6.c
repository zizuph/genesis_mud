#include "defs.h"

inherit BASE_ROOM;

CONSTRUCT_ROOM 
{
   set_short("The Great Eastroad");
   set_long("You are travelling on the Great Eastroad. A salt wind from the west tells " +
	    "the presence of the Sea, you can not be far from the Greyhavens now. " +
	    "You can also see three white towers standing upon the hill in the west, " +
	    "and the road slowly climbs upwards towards them. " +
	    "The road continues eastwards through a barren landscape, only small " +
    "trees and fields of grass bends under the western winds.\n"+
    "A path leads north.\n");

   add_item(({ "road", "eastroad" }),
	    "The road seems well built, as it is often used by dwarves, men and elves " +
	    "in their travelling. The dwarves have their homes in the Blue Mountains, " +
	    "while the elves mostly live in the harbour town of Greyhaven, Mithlond. " +
	    "You notice tracks following the road.\n");

   add_item(({ "track", "tracks" }), "The tracks are mostly made by wagons "
	    + "and mules. There are also a few that indicate horses.\n");

   add_item(({ "wind", "salt wind" }), "The wind gently breezes from the west, and " +
	    "it definitely feels like the sea is not far from here, though you can " +
	    "not see it.\n");

   add_item(({ "towers", "white towers" }), "Lonely gazing westwards they stand upon " +
	    "the hill in the west. You better go west to get a better view.\n");
   
   add_item(({ "hill" }), "The hill, or rather the down, is gently climbing upwards.\n");
   add_item(({ "landscape", "trees", "fields" }),
	    "The landscape is beautiful in its harshness, though hardly worth a visit.\n");

   add_exit(GHAVEN_DIR + "gh3", "east", 0, 2);
   add_exit(GHAVEN_DIR + "gh7", "west", 0);
  add_exit("/d/Shire/herald/path1","north",0,2);
}


