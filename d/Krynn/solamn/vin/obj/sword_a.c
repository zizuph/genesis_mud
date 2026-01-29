// sword_a.c door in kn1
// grace Dec 1994

inherit "/std/door";
#include "../knight/guild.h" 

#define SWORD_C_KEY   19941204

create_door()
{
   set_door_id("_Sword_conclave_door_");
    set_pass_command(({"east", "e", "sword", "Sword", "enter sword", "enter Sword"}));
   set_fail_pass("Walking through doors is a skill you haven't " +
      "mastered yet. Try opening it first.\n");
    set_door_name(({"Sword Door", "Sword Conclave Door", "sword order",
        "sword conclave", "door", "sword door", "silver door", "sword"}));
   set_door_desc("This large door has a gleaming sword impressed into "+
      "it, the symbol of the Sword Order of the Knights of Solamnia. The "+
      "handle glows with an inner light and opens the door outward. Rather "+
      "heavy, it looks like it would take the combined weights of several "+
      "men thrown against it to force the door open.\n");
   set_other_room(VROOM + "kn4");
   set_open(0);
   set_locked(1);
  set_open_desc("An open silver door leads east into the office of the High "+
	"Clerist.\n");
//  set_closed_desc("A silver door.  \n");       
   set_closed_desc("");

   set_open_command(({"open","turn","push"}));
   set_open_mess(({"pushes the silver door open.\n", 
      "The silver door slowly opens wide.\n"}));
   set_fail_open(({"The silver door is already open!\n",
      "You must unlock the silver door before it can be opened!\n"}));     
   set_close_command(({"close","pull", "pull closed", "shut"}));
   set_close_mess(({"pulls the silver door closed.\n", "You pull the silver " +
      "door closed.\n"}));
   set_fail_close("The silver door is already closed.\n");
   set_lock_name(({"lock","keyhole"}));
   set_lock_desc("It is difficult to discern anything about the lock.\n");
   set_lock_command(({"lock","turn key"}));
   set_lock_mess(({"turns a key in the lock of the silver door.\n",
      "You hear a click from the lock of the silver door.\n"}));
   set_fail_lock(({"The silver door is already locked.\n",
      "You feel silly trying to lock an open door!\n"}));
   set_unlock_command(({"unlock","turn key"}));
   set_unlock_mess(({"turns a key in the keyhole, unlocking the silver door.\n",
      "You hear a click from the lock on the silver door, perhaps " +
       "it is unlocked now.\n"}));
   set_fail_unlock("You feel silly trying to lock a door that is " +
      "already locked!\n");
   set_key(SWORD_C_KEY);
   set_pick(101);
} 
