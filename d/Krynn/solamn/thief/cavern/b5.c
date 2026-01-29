/* created by Aridor 02/09/94 */

#include "../local.h"

inherit ROOM_BASE


void
create_thief_room()
{
    set_short("In a hallway");
    set_long("This is a hallway made from stone leading north. There is " +
	     "an opening leading west.\n");
    
    add_exit(TURNB,"west","@@if_open");
    add_exit(CAVERN + "b3","north");
    
    DARK;
}


int
if_open()
{
    if ((TURNB)->query_exit_direction() == "east")
      return 0;
    write("You find that it is impossible to leave the room as the door ends in a brick " +
	  "wall!\nYou push again, and suddenly you fall through the wall into another " +
	  "room, the wall slamming back into place behind you.\n");
    return 0;
}
