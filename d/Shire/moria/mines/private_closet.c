/*  -- Toby, 01-Oct-2007: Fixed typo in door thing...
 */

#include "defs.h"

object door;
int door_open;

CONSTRUCT_ROOM
{
   door_open = 0;
   set_short("The private closet");
   set_long(
      "You have arrived in a private closet. In the north, there is an "+
      "opening, while in the south there is a heavy oak door.");
   add_item("opening", "It leads to a cross in the north.");
   NORTH("cross");
   
   door = clone_object(MORIA_OBJ + "closet_door");
   door -> init_north();
   door -> move(TO);
   add_cmd_item(({"on the door","on door","the door","door"}),"knock","@@my_knock@@");
}

string
my_knock()
{
   say(QCTNAME(TP)+" knocks on the door.\n");
   return "You knock on the door.";
}

int
open_door()
{
   if (door_open)
      return 0;
   tell_room(TO, "The door suddenly widens and opens!\n");
   SOUTH("alch_home");
   door_open = 1;
   return 1;
}
