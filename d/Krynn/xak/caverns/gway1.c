/* Xak Tsorath Aghar section by Karath */

#include "../xlocal.h"
#include "/sys/ss_types.h"
#include <macros.h>

inherit  XAKINROOM

void
create_room()
{
    set_short("An old dirty street");
    
    set_long("You are in an old dirty street of Xak Tsaroth deep "+
	"underground in a huge cavern. This section of the city "+
	"has buildings which are in pretty poor shape and appear "+
	"to have fallen victim to cave-ins from the Cataclysm. "+
	"There are several flickering torch-lights to the north "+
	"and a doorway to a collapsed room leads east. To the south "+
	"you hear the sounds of crashing water.\n");
    
    add_exit(DDIR + "fall", "south", 0);
    add_exit(DDIR + "gruin1", "east", 0);
    add_exit(DDIR + "gway2", "north", 0);

    add_item( ({ "street", "old street", "old dirty street",
		   "dirty street" }), "The streets are old and "+
	"filthy, but do show signs of recent travel.\n");
    add_item( ({"buildings", "building"}), "The building to the "+
	"left is still standing, but you see no way in. The "+
	"building to the right has a collapsed roof, but the "+
	"doorway still stands.\n");
    add_item( ({"torch-lights", "torch lights", "lights",
		"flickering torch-lights", "flickering lights",
		"flickering torch lights" }), "The torch "+
	"lights are flickering faintly to the north.\n");
    
    INSIDE;
    DARK;
}
