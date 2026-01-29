/* created by Aridor 02/09/94 */

#include "../local.h"

inherit ROOM_BASE

void
create_thief_room()
{
    set_short("In a cavern");
    set_long("This is a cavern. A doorframe is set into the rock leading west " +
	     "and a passage leads northeast from here.\n");
    
    add_exit(TURNC,"west","@@if_open");
    add_exit(CAVERN + "pass1","northeast");
    
    DARK;

    add_item(({"doorframe","door"}), "It is a wooden doorframe set into the rock.\n");
    add_item(({"rock"}),"This is just bare rock.\n");
    add_item("brick wall","@@brick_wall@@");
    add_item("metal","@@metal@@");
}


int
if_open()
{
    if ((TURNC)->query_exit_direction() == "east")
      return 0;
    write("You find that it is impossible to leave the room as the door " +
	  "ends in a brick wall!\n");
    return 1;
}
string
brick_wall()
{
    if ((TURNC)->query_exit_direction() == "east")
      return "You find no brick wall.\n";
    return "Looking closely, you find that these are not really bricks, but someone " +
      "apparently just painted bricks onto metal.\n";
}

string
metal()
{
    if ((TURNC)->query_exit_direction() == "east")
      return "You find no metal.\n";
    return "It is just metal, but not a door in any way. You cannot see any means to " +
      "pass.\n";
}
