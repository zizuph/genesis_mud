/* created by Aridor 02/21/94 */

#include "../local.h"

inherit ROOM_BASE

void
create_thief_room()
{
  set_short("In a cavern");
  set_long("This is a cavern. It actually isn't much more than a passage " +
	   "since it is so narrow you can hardly walk through.\n");
  
  add_exit(IN_CAVE,"southwest","@@blocked");
  add_exit(CAVERN + "hall1","north");

  DARK;
}

int
blocked()
{
    write("The cavern narrows even further but you just about manage to fit " +
	  "through.\n");
    return 0;
}
