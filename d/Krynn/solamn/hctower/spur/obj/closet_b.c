// arm_b.c door in armoire.c
// grace aug 1994

inherit "/std/door";
#include "../local.h"

create_door()
{
   set_door_id("_closet_");
   set_pass_command(({"enter", "back", "exit", "out"}));
   set_fail_pass("Walking through doors is a skill you haven't " +
      "mastered yet. Try opening it first.\n");
   set_door_name(({"closet door","closet"}));
   set_door_desc("This is a simple door made from pine wood. It has "+
      "two doors with handles.\n");
   set_other_room(ROOM + "kn2.c");
   set_open(0);
   set_locked(0);
   set_open_desc("Open closet doors.\n");
  set_closed_desc("Closed closet doors.\n");
   set_open_command(({"open","open door","turn","pull"}));
   set_open_mess(({"pulls the closet doors open.\n", "The doors of the " +
            "closet slowly open wide.\n"}));
   set_fail_open(({"The closet is already open!\n",
          "You must unlock the closet door before it can be opened!\n"}));
   set_close_command(({"close","push", "push closed"}));
   set_close_mess(({"pushes the doors closed.\n", "The closet doors " +
            "slowly slide closed.\n"}));
   set_fail_close("The closet door is already closed.\n");
} 
