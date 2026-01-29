inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
void create_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    set_short("Prison cell");
	set_long("   You have entered one of the prison cells in " +
	"the dungeon. The door seems to have been blown away.\n\n");
	add_item("ceiling","It just hangs up there.\n");
    add_item("floor","It's of no interest.\n");
    add_item(({"wall","walls"}),"Every wall here is typical "+
                 "for dungeon style: it's strong and rude.\n");
    add_exit(TEMPLE_DIR + "dungeon3", "east", 0);
}
