// rose_a.c door in kn1
// grace Dec 1994

inherit "/std/door";
#include "../local.h" 

create_door()
{
   set_door_id("_Rose_conclave_door_");
    set_pass_command(({"rose", "Rose", "enter rose", "enter Rose"}));
   set_fail_pass("Walking through doors is a skill you haven't " +
      "mastered yet. Try opening it first.\n");
    set_door_name(({"Rose Conclave door", "rose door", "rose order",
        "rose conclave", "door", "rose"}));

   set_door_desc("This large door has the image of a rose carved into "+
      "it, the symbol of the Rose Order of the Knights of Solamnia. The "+
      "handle glows with an inner light and opens the door inward. Rather "+
      "heavy, it looks like it would take the combined weights of several "+
      "men thrown against it to force the door open.\n");
   set_other_room(ROOM + "kn5");
   set_open(0);
   set_locked(1);
  set_open_desc("An open door leading Rose.\n");
    set_closed_desc("A Rose Conclave door.\n");

   set_open_command(({"open","turn","push"}));
   set_open_mess(({"pushes the Rose Door open.\n", 
      "The door to the Rose Conclave slowly opens wide.\n"}));
   set_fail_open(({"The Rose Door is already open!\n",
      "You must unlock the Rose Door before it can be opened!\n"}));     
   set_close_command(({"close","pull", "pull closed", "shut"}));
   set_close_mess(({"pulls the Rose Door closed.\n", "You pull the Rose " +
      "Door closed.\n"}));
   set_fail_close("The Rose Conclave Door is already closed.\n");
   set_lock_name(({"lock","keyhole"}));
   set_lock_desc("It is difficult to discern anything about the lock.\n");
   set_lock_command(({"lock","turn key"}));
   set_lock_mess(({"turns a key in the lock of the Rose Door.\n",
      "You hear a click from the lock of the Rose Door.\n"}));
   set_fail_lock(({"The Rose Door is already locked.\n",
      "You feel silly trying to lock an open door!\n"}));
   set_unlock_command(({"unlock","turn key"}));
   set_unlock_mess(({"turns a key in the keyhole, unlocking the Rose Door.\n",
      "You hear a click from the lock on the Rose Door, perhaps " +
       "it is unlocked now.\n"}));
   set_fail_unlock("You feel silly trying to lock a door that is " +
      "already locked!\n");
   set_key(ROSE_C_KEY);
   set_pick(101);
} 
