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
	"has buildings which are in pretty decent shape and appear "+
	"to have been spared the cave-ins from the Cataclysm. "+
	"There are several flickering torches on the walls. "+
	"The alleyway continues south and east.\n");
    
    add_exit(DDIR + "gway2", "south", 0);
    add_exit(DDIR + "gally4", "east", 0);

    add_item( ({ "street", "old street", "old dirty street",
		   "dirty street" }), "The streets are old and "+
	"filthy, but do show signs of recent travel.\n");
    add_item( ({"buildings", "building"}), "The buildings "+
	"here look undamaged and have no entrance from here.\n");
    add_item( ({ "torches", "torch", "flickering torches",
		   "flickering torch" }), "The torches are "+
	"flickering softly, but firmly attached to the "+
	"walls of the buildings.\n");
    add_item( ({"alley", "alleyway"}), "The alleyway "+
	"is absolutely filthy and shows signs of recent "+
	"travel.\n");
    
    INSIDE;
}
