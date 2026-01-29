/* created by Aridor 02/09/94 */

#include "../local.h"

inherit ROOM_BASE


void
create_thief_room()
{
    set_short("In a cavern");
    set_long("This is a cavern. It looks like a natural cave leading off " +
	     "to the north. The odd thing here is the opening leading east, " +
	     "it's just a doorframe with a door missing in it.\n");
    
    add_exit(TURNB,"east","@@if_open");
    add_exit(CAVERN + "b1","north");
    
    DARK;
    
    add_item("doorframe",
	     "This is a doorframe carved out of the stone, very skilled " +
	     "work. Strange, though, that the rest of the cavern is not " +
	     "perfected like this.\n");
}


int
if_open()
{
    if ((TURNB)->query_exit_direction() == "west")
      return 0;
    write("You find that it is impossible to leave the room as the door ends in a brick " +
	  "wall!\nYou push again, and suddenly you fall through the wall into another " +
	  "room, the wall slamming back into place behind you.\n");
    return 0;
}
