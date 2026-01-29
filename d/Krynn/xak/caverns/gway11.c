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
	"underground in a huge cavern. The street goes southeast and "+
	"southwest. There is a waterfall to the northwest which turns "+
	"into a river flowing southeast, blocking the street.\n");
    
    add_exit(DDIR + "gway10", "southwest", 0);
    add_exit(DDIR + "nowhere", "southeast", do_block);

    add_item( ({ "street", "old street", "old dirty street",
		   "dirty street" }), "The streets are old and "+
	"filthy, but do show signs of recent travel.\n");
    add_item( ({"buildings", "building"}), "The buildings to the "+
	"south look rather damaged and have no entrance from "+
	"here.\n");
    add_item( ({"rubble", "impassable rubble"}), "The rubble seems "+
	"to be a collapsed building.\n");
    add_cmd_item( ({"rubble", "impassable rubble"}), ({"climb", }),
	"The rubble is definately impassable.\n");
    
    INSIDE;
    DARK;
}

int
do_block()
{
    write("The street to the southeast is blocked by a river.\n");
    return 1;
}
