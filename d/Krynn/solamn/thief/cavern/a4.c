/* created by Aridor 02/09/94 */

#include "../local.h"

inherit ROOM_BASE

void
create_thief_room()
{
    set_short("In a cavern");
    set_long("This is a straight part of the cavern. Moss and algae " +
	     "are everywhere, but the hallway itself must have been " +
	     "carved by experts, straight walls, floor and ceiling " +
	     "prove this. Just noone seems to have cleaned here in ages.\n");
    
    add_exit(CAVERN + "a1","north");
    add_exit(CAVERN + "a6","south");
    
    DARK;
    add_prop(OBJ_I_CONTAIN_WATER, 50000);
    
    add_item("moss",
	     "The moss varies in color from yellow through red to brown, " +
	     "and covers most of the walls. It even hangs down from the " +
	     "ceiling. The moss is very damp and water is dripping from " +
	     "the overhanging parts.\n");
    add_item("algae",
	     "The algae are green and brown and grow on the floor of the " +
	     "cavern.\n");
    add_item("floor",
	     "The floor is very even here, but it's completely covered with " +
	     "algae and water.\n");
    add_item("ceiling",
	     "There is damp moss hanging from the ceiling, water dripping down.\n");
    add_item(({"wall","walls"}),
	     "The walls are very straight in both directions, north and south, " +
	     "but they're covered with moss.\n");
    add_item("water",
	     "The water on the floor is only a few inches deep, but algae " +
	     "are growing in it. The water is dripping down from moss hanging " +
	     "down from overhead.\n");
    add_item("hallway",
	     "You are standing in it.\n");
    add_cmd_item(({"moss from ceiling"}),
		 ({"tear","rip","yank","pull"}),"@@tear_moss_ceiling");
    add_cmd_item(({"moss from wall","moss from walls"}),
		 ({"tear","rip","yank","pull"}),"@@tear_moss_wall");
    add_cmd_item(({"moss"}),({"tear","rip","yank","pull"}),"@@tear_moss");
    
}


string
tear_moss()
{
    write("Where do you want to tear the moss down from?\n");
    return "";
}

string
tear_moss_wall()
{
    write("You tear some of the moss down but you can't find anything special " +
	  "underneath.\n");
    return "";
}

string
tear_moss_ceiling()
{
    write("You tear some of the moss down from the ceiling. There is nothing " +
	  "underneath, though.\n");
    return "";
}
