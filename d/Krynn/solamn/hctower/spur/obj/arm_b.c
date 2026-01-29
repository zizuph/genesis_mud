// arm_b.c door in armoire.c
// grace aug 1994

inherit "/std/door";
#include "../local.h"

create_door()
{
   set_door_id("_armoire_");
   set_pass_command(({"enter", "back", "exit"}));         
   set_fail_pass("Walking through doors is a skill you haven't " +
      "mastered yet. Try opening it first.\n");
   set_door_name(({"armoire","wardrobe"}));
   set_door_desc("This large armoire gleams in the light. It has "+
      "two doors with handles, and a lock.\n");
   set_other_room(ROOM + "hp1.c");
   set_open(0);
   set_locked(1);
  set_open_desc("Open armoire doors.\n");
  set_closed_desc("Closed armoire doors.\n");  
   set_open_command(({"open","open armoire","turn","pull"}));
   set_open_mess(({"pulls the armoire open.", "The doors of the " +
            "armoire slowly open wide."}));
   set_fail_open(({"The armoire is already open!",
          "You must unlock the armoire before it can be opened!\n"}));     
   set_close_command(({"close","push", "push closed"}));
   set_close_mess(({"pushes the doors closed.", "The armoire doors " +
            "slowly slide closed."}));
   set_fail_close("The armoire is already closed!\n");
   set_lock_name(({"lock","keyhole"}));
   set_lock_desc("It is a small dusty lock made of iron.\n");
   set_lock_command(({"lock","turn key"}));
   set_lock_mess(({"turns a key in the lock of the armoire.",
            "You hear a click from the lock of the armoire."}));
   set_fail_lock(({"The armoire is already locked.\n",
            "You feel silly trying to lock an open door!\n"}));
   set_unlock_command(({"unlock","turn key"}));
   set_unlock_mess(({"turns a key in the keyhole, unlocking the armoire.",
            "You hear a click from the lock on the armoire, perhaps " +
            "it is unlocked now."}));
  set_fail_unlock("You feel silly trying to unlock a door that is " +
      "already unlocked!\n");
   set_key(LOCK_1);
   set_pick(40);
} 
