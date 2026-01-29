/* created by Aridor 02/09/94 */

#include "../local.h"

inherit ROOM_BASE

#define THIS_ROOMS_VALUE   4

object *handle = ({ });

void
create_thief_room()
{
    set_short("In a cavern");
    set_long("Here, the cavern comes to an end. The only way out is how you " +
	     "came in, to the west. Moss and algae " +
	     "are everywhere, but the hallway itself must have been " +
	     "carved by experts, straight walls, floor and ceiling " +
	     "prove this. Just noone seems to have cleaned here in ages.\n");
    
    add_exit(CAVERN + "a1","west");
    
    DARK;
    add_prop(OBJ_I_CONTAIN_WATER, 50000);
    
    add_item("moss",
	     "The moss varies in color from yellow through red to brown, " +
	     "and covers most of the walls. It even hangs down from the " +
	     "ceiling. The moss is very damp and water is dripping from " +
	     "the overhanging parts.\n");
    add_search(({"moss","ceiling"}),10,"search_moss_ceiling",1);
    add_item("algae",
	     "The algae are green and brown and grow on the floor of the " +
	     "cavern.\n");
    add_item("floor",
	     "The floor is very even here, but it's completely covered with " +
	     "algae and water.\n");
    add_item("ceiling",
	     "There is damp moss hanging from the ceiling, water dripping down.\n");
    add_item(({"wall","walls"}),
	     "The walls are very straight, along the hallway to the west and at " +
	     "the end of the hallway to the east, but they're covered with moss.\n");
    add_item("water",
	     "The water on the floor is only a few inches deep, but algae " +
	     "are growing in it. The water is dripping down from moss hanging " +
	     "down from overhead.\n");
    add_item("hallway",
	     "You are standing in it.\n");
    add_item("handle","@@exa_handle");
    add_cmd_item("handle","pull","@@solved_this");
    add_cmd_item(({"moss from ceiling"}),
		 ({"tear","rip","yank","pull"}),"@@tear_moss_ceiling");
    add_cmd_item(({"moss from wall","moss from walls"}),
		 ({"tear","rip","yank","pull"}),"@@tear_moss_wall");
    add_cmd_item(({"moss"}),
		 ({"tear","rip","yank","pull","take","get","pick"}),"@@tear_moss");
}


string
exa_handle()
{
    if (member_array(TP,handle) == -1)
      return "You find no handle.\n";
    else
      return "It's a small metal handle set into the ceiling.\n";
}

string
solved_this()
{
    NF("What?\n");
    if (member_array(TP,handle) == -1)
      return 0;
    if (!sizeof(TP->query_team_others()))
      TP->add_prop(THIEF_I_CAN_ENTER, 
		   TP->query_prop(THIEF_I_CAN_ENTER) | THIS_ROOMS_VALUE);
    return "You pull the handle and you hear a faint click from above.\n";
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
    write("You tear some of the moss down and you find a small handle underneath.\n");
    handle += ({ TP });
    return "";
}

string
search_moss_ceiling(object searcher, string what)
{
    handle += ({ searcher });
    return "You tear some of the moss down and you find a small " +
      "handle underneath.\n";
}
