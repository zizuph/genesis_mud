inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
void create_room()
{
    object door;
 
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    set_short("Prison cell");
	set_long("   You have entered one of the prison cells in the " +
	"dungeon. There is a small hard bed along one wall. " +
	"The quarters are tight and sterile.\n\n");
    add_item("ceiling","It just hangs up there.\n");
    add_item("floor","It's of no interest.\n");
    add_item(({"wall","walls"}),"Every wall here is typical for " +
              "dungeon style: it's strong and rude.\n");
    door=clone_object(TEMPLE_DIR + "doors/celldoor2_b");
    door->move(this_object());
}
