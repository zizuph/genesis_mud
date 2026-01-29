/* created by Aridor 02/09/94 */

#include "../local.h"

inherit ROOM_BASE

void
create_thief_room()
{
    set_short("In a cavern");
    set_long("This is a natural cavern. A strange doorframe leads east and " +
	     "the natural cavern extends further west. Next to the doorframe, " +
	     "a wooden wheel is affixed to the wall.\n");
    
    add_exit(TURNC,"east","@@if_open");
    add_exit(CAVERN + "hall1","west");
    
    add_cmd_parse("[the] 'wheel' [to] [the] 'right'","turn",
		  "@@turn_room_right");
    add_cmd_parse("[the] 'wheel' [to] [the] 'left'","turn",
		  "@@turn_room_left");
    add_cmd_parse("[the] 'wheel'","turn",
		  "In which direction do you want to turn the wheel?\n");
    DARK;
    
    add_item(({"frame","door","doorframe"}),
	     "It's a wooden doorframe set into the rock.\n");
    add_item(({"wheel","wooden wheel"}),
	   "It is a round wheel made from wood with a diameter of about one foot. " +
	   "The wheel is affixed to the wall and looks like it can be turned.\n");
    add_item(({"rock","east wall","wall"}),
	     "On the east wall in this cavern you see a wheel protruding from " +
	     "the rock. The wall is just bare rock, you cannot see anything " +
	     "special about it.\n");
    add_item("brick wall","@@brick_wall@@");
    add_item("metal","@@metal@@");
}


int
if_open()
{
    if ((TURNC)->query_exit_direction() == "west")
      return 0;
    write("You find that it is impossible to leave the room as the door " +
	  "ends in a brick wall!\n");
    return 1;
}

string
brick_wall()
{
    if ((TURNC)->query_exit_direction() == "west")
      return "You find no brick wall.\n";
    return "Looking closely, you find that these are not really bricks, but someone " +
      "apparently just painted bricks onto metal.\n";
}

string
metal()
{
    if ((TURNC)->query_exit_direction() == "west")
      return "You find no metal.\n";
    return "It is just metal, but not a door in any way. You cannot see any means to " +
      "pass.\n";
}

string
turn_room_left()
{
  (TURNC)->turn_me_left();
  return "";
}

string
turn_room_right()
{
  (TURNC)->turn_me_right();
  return "";
}
