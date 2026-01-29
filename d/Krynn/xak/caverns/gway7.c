/* Xak Tsorath Aghar section by Karath */

#include "../xlocal.h"
#include "/sys/ss_types.h"
#include <macros.h>

inherit  XAKINROOM

int do_block();

void
create_room()
{
    set_short("An old dirty street");
    
    set_long("You are in an old dirty street of Xak Tsaroth deep "+
	"underground in a huge cavern. The street goes east and "+
	"west with a sidestreet to the south. The buildings to the "+
	"southeast have strange sounds coming from it and there "+
	"is a waterfall to the north past some impassable rubble.\n");
    
    add_exit(DDIR + "gway6", "south", 0);
    add_exit(DDIR + "nowhere", "west", do_block);
    add_exit(DDIR + "gway8", "east", 0);

    add_item( ({ "street", "old street", "old dirty street",
		   "dirty street" }), "The streets are old and "+
	"filthy, but do show signs of recent travel.\n");
    add_item( ({"buildings", "building"}), "The buildings to the "+
	"south and west look rather damaged and have no entrance from "+
	"here. The buildings to the southeast look sturdy "+
	"and you think you can even hear voices coming from them!\n");
    add_item( ({ "torches", "torch", "flickering torches",
		   "flickering torch" }), "The torches are "+
	"flickering softly, but firmly attached to the "+
	"walls of the buildings.\n");
    add_item( ({"rubble", "impassable rubble"}), "The rubble seems "+
	"to be a collapsed building.\n");
    add_cmd_item( ({"rubble", "impassable rubble"}), ({"climb", }),
	"The rubble is definately impassable.\n");
    
    INSIDE;
}

int
do_block()
{
    write("The street to the west is blocked by a cave-in.\n");
    return 1;
}
