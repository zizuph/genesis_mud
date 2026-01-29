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
	"There are several flickering torches on the walls."+
	"and an alleyway leads east. To the south, "+
	"the street continues.\n");
    
    add_exit(DDIR + "gway2", "south", 0);
    add_exit(DDIR + "gway4", "north", 0);
    add_exit(DDIR + "gally1", "east", 0);

    add_item( ({ "street", "old street", "old dirty street",
		   "dirty street" }), "The streets are old and "+
	"filthy, but do show signs of recent travel.\n");
    add_item( ({"buildings", "building"}), "The buildings to the "+
	"west look rather damaged and have no entrance from here.\n");
    add_item( ({ "torches", "torch", "flickering torches",
		   "flickering torch" }), "The torches are "+
	"flickering softly, but firmly attached to the "+
	"walls of the buildings.\n");
    add_item( ({"alley", "alleyway"}), "The alleyway to the "+
	"east is absolutely filthy and shows signs of recent "+
	"travel.\n");
    
    INSIDE;
}
