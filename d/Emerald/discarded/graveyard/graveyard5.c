/*
 * GRAVEYARD5.c
 * Section of graveyard in the Emerald graveyard.
 * Alaron August 2, 1996
 */

#include "default.h"

inherit "/std/room";

void
create_room()
{
    set_short("Graveyard");
    set_long("   A thick sheet of dark gray fog seems to hover inches "+
	     "above the damp, dark green soil of the graveyard. A chill "+
	     "wind laps gently against the tops of the overgrown grass, "+
	     "causing the entire field to lean slightly in one direction. "+
	     "Scattered randomly among the tall grass are hundreds of "+
	     "old, decaying and broken grave markers. Some are simple "+
	     "stone slabs, others are intricately carved stone crosses. A "+
	     "sense of dread and loneliness seems to fill the mist as "+
	     "it smothers the graveyard in a sheet of dismal gray.\n\n");

    add_item( ({"fog", "thick sheet", "dark gray fog", "gray fog",
		"dismal gray"}),
	     "The entire graveyard seems to be smothered in a sheet "+
	     "of dark gray moisture, looming ominously over the scene "+
	     "and actively stifling anything that might bring light "+
	     "or cheer to the area. The more you look at the fog, the "+
	     "more you want to turn and run out of the graveyard as "+
	     "fast as you possibly can.\n");

    add_item( ({"grass", "overgrown grass", "tall grass"}),
	     "The entire field has been left untended in this damp "+
	     "environment for far too long. The grass has grown to such "+
	     "proportions that one could disappear beneath by ducking "+
	     "only slightly.\n");

    add_item( ({"markers", "grave markers", "stones", "grave stones",
		"gravestones", "headstones", "head stones", "slabs",
		"crosses", "stone slabs", "stone crosses"}),
	     "The centuries of aging in this damp, cold area have "+
	     "not been kind to the grave markers. Most are dark purple "+
	     "and black with water erosion, and equally as many have "+
	     "cracked or broken into pieces. A sad testament to the once "+
	     "strong and vibrant people whose ashes now inhabit the "+
	     "earth below.\n");
    
    add_exit( GRAVEYARD_DIR + "graveyard7", "south");
    add_exit( GRAVEYARD_DIR + "graveyard2", "west");
}
