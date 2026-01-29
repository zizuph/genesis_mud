// crown_a.c door in kn3
// grace Dec 1994

inherit "/std/door";
#include "../local.h" 

create_door()
{
   set_door_id("_Crown_conclave_door_");
     set_pass_command(({"out", "enter", "exit"}));
   set_fail_pass("Walking through doors is a skill you haven't " +
      "mastered yet. Try opening it first.\n");
    set_door_name(({"Crown", "crown door", "crown order",
        "crown conclave", "door", "crown"}));
   set_door_desc("This large door has the image of a Crown carved into "+
      "it, the symbol of the Crown Order of the Knights of Solamnia. The "+
      "handle glows with an inner light and opens the door inward. Rather "+
      "heavy, it looks like it would take the combined weights of several "+
      "men thrown against it to force the door open.\n");
   set_other_room(ROOM + "kn1");
   set_open(0);
   set_locked(1);
   set_open_desc("The Crown Conclave door stands open.\n");
   set_closed_desc("A Crown Conclave door.\n");
   set_open_command(({"open","turn","pull"}));
   set_open_mess(({"pulls the Crown Door open.\n", 
      "The door to the Crown Conclave slowly opens wide.\n"}));
   set_fail_open(({"The Crown Door is already open!\n",
      "You must unlock the Crown Door before it can be opened!\n"}));     
   set_close_command(({"close","push", "push closed", "shut"}));
   set_close_mess(({"pushes the Crown Door closed.\n", "You push the Crown " +
      "Door closed.\n"}));
   set_fail_close("The Crown Conclave Door is already closed.\n");
   set_lock_name(({"lock","keyhole"}));
   set_lock_desc("It is difficult to discern anything about the lock.\n");
   set_lock_command(({"lock","turn key"}));
   set_lock_mess(({"turns a key in the lock of the Crown Door.\n",
      "You hear a click from the lock of the Crown Door.\n"}));
   set_fail_lock(({"The Crown Door is already locked.\n",
      "You feel silly trying to lock an open door!\n"}));
   set_unlock_command(({"unlock","turn key"}));
   set_unlock_mess(({"turns a key in the keyhole, unlocking the Crown Door.\n",
      "You hear a click from the lock on the Rose Door, perhaps " +
       "it is unlocked now.\n"}));
   set_fail_unlock("You feel silly trying to lock a door that is " +
      "already locked!\n");
   set_key(CROWN_C_KEY);
   set_pick(101);
} 
