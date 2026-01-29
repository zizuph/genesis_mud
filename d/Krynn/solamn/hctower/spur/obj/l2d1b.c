// door in landing1
// grace aug 1994

inherit "/std/door";
#include "../local.h"

create_door()
{
   set_door_id("_level2_door1_"); 
   set_pass_command(({"w","west","go through","out","exit"}));
   set_fail_pass("Walking through doors is a skill you haven't " +
      "mastered yet. Try opening them first.\n");    
   set_door_name(({"heavy wooden door","wood door", "wooden door",
            "door","door"}));
   set_door_desc("A heavy wooden door girded with iron. "+
      "It has an iron handle attached to it, and a lock.\n");
    set_other_room(ROOM + "greathall");
   set_open(0);
   set_locked(0);   
 //   set_open_desc();
   //  set_closed_desc();
   set_open_command(({"open","turn door handle","turn","push"}));
   set_open_mess(({"pushes the door open.\n", "The heavy wooden door " +
            "slowly opens wide.\n"}));
   set_fail_open(({"The heavy wooden door is already open!\n", 
            "You must unlock the door before it can be opened!\n"}));
   set_close_command(({"close","pull", "pull handle", "pull door handle"}));
   set_close_mess(({"pulls the door closed.\n", "The heavy wooden door " +
            "slowly slides closed.\n"}));
   set_fail_close("The heavy wooden door is already closed.\n");
    AI(({"handle","handles"}), "The door handle is made of iron and it looks " +
      "like it can be turned.\n");   
   set_lock_name(({"lock","keyhole"}));
   set_lock_desc("It is a large lock made of iron. The key that fits " +
      "its keyhole must be quite large.\n");
   set_lock_command(({"lock","turn key"}));
   set_lock_mess(({"turns a key in the lock of the heavy wooden door.\n",
            "You hear a click from the lock of the heavy wooden door.\n"}));
   set_fail_lock(({"The heavy wooden door is already locked.\n",
            "You feel silly trying to lock an open door!\n"}));
   set_unlock_command(({"unlock","turn key"}));
   set_unlock_mess(({"turns a key in the keyhole, unlocking the door.\n",
            "You hear a click from the lock on the door, perhaps it is " +
            "unlocked now.\n"}));
    set_fail_unlock("You feel silly trying to lock a door that is " +
      "already locked!\n"); 
   set_key(LOCK_M);
   set_pick(49);
}              


