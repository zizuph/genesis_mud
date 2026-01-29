// door in pass4l1.c
// grace aug 1994

inherit "/std/door";
#include "../local.h"

create_door()
{
    set_door_id("_level1_door1_");
    set_pass_command(({"s","south","go through","out","exit","enter"}));   
    set_fail_pass("Walking through doors is a skill you haven't " +
        "mastered yet. Try opening them first.\n");    
    set_door_name(({"heavy wooden doors","wood doors", "wooden doors",
       "doors","door"}));
    set_door_desc("A pair of heavy wooden doors girded with iron. "+
       "Each has an iron handle attached to it, and a lock.\n");
   set_other_room(ROOM + "stair5.c"); 
    set_open(1);
    set_locked(0);   
 //   set_open_desc();
//  set_closed_desc();
    set_open_command(({"open","turn door handle","turn","push"}));
    set_open_mess(({"pushes the doors open.", "The heavy wooden doors " +
       "slowly open wide."}));
    set_fail_open(({"The heavy wooden doors are already open!\n", 
       "You must unlock the doors before they can be opened!"}));
    set_close_command(({"close","pull", "pull handle", "pull door handle"}));
    set_close_mess(({"pulls the doors closed.", "The heavy wooden doors " +
       "slowly slide closed."}));
    set_fail_close("The heavy wooden doors are already closed.");
    AI(({"handle","handles"}), "They are made of iron and it looks " +
       "like one of them can be turned.\n");   
    set_lock_name(({"lock","keyhole"}));
    set_lock_desc("It is a large lock made of iron. The key that fits " +
       "its keyhole must be quite large.\n");
    set_lock_command(({"lock","turn key"}));
    set_lock_mess(({"turns a key in the lock of the heavy wooden doors.",
       "You hear a click from the lock of the heavy wooden doors."}));
    set_fail_lock(({"The heavy wooden doors are already locked.",
       "You feel silly trying to lock an open door!"}));
    set_unlock_command(({"unlock","turn key"}));
    set_unlock_mess(({"turns a key in the keyhole, unlocking the door.",
       "You hear a click from the lock on the door, perhaps it is " +
       "unlocked now."}));
    set_fail_unlock("You feel silly trying to lock a door that is " +
       "already locked!"); 
    set_key(LOCK_M);
    set_pick(49);
}              


