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
	"underground in a huge cavern. The street makes a turn "+
	"to the west and south at the corner of some buildings "+
	"that seem to be in rather good shape while the buildings "+
	"to the southwest are almost totally destroyed. To the south, "+
	"the street continues.\n");
    
    add_exit(DDIR + "gway3", "south", 0);
    add_exit(DDIR + "gway5", "west", 0);

    add_item( ({ "street", "old street", "old dirty street",
		   "dirty street" }), "The streets are old and "+
	"filthy, but do show signs of recent travel.\n");
    add_item( ({"buildings", "building"}), "The buildings to the "+
	"southwest look rather damaged and have no entrance from "+
	"here. The buildings to the east and north look sturdy "+
	"and you think you can even hear voices coming from them!\n");
    add_item( ({ "torches", "torch", "flickering torches",
		   "flickering torch" }), "The torches are "+
	"flickering softly, but firmly attached to the "+
	"walls of the buildings.\n");
    
    INSIDE;
}
