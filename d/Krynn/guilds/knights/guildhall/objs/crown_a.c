// crown_a.c door in kn1
// grace Dec 1994

inherit "/std/door";
#include "../../guild.h" 

#define CROWN_C_KEY   19941203

create_door()
{
   set_door_id("_Crown_conclave_door_");
   set_pass_command(({"west", "w", "crown", "Crown", "enter crown", "enter Crown"}));
   set_fail_pass("Walking through doors is a skill you haven't " +
      "mastered yet. Try opening it first.\n");
    set_door_name(({"bronze door", "bronze door", "crown order",
        "crown conclave", "door", "bronze door", "crown"}));
   set_door_desc("This large door has the image of a Crown carved into "+
      "it, the symbol of the Crown Order of the Knights of Solamnia. The "+
      "handle glows with an inner light and opens the door inward. Rather "+
      "heavy, it looks like it would take the combined weights of several "+
      "men thrown against it to force the door open.\n");
   set_other_room(VROOM + "kn3");
   set_open(0);
   set_locked(1);
    set_open_desc("An open bronze door leads west into the office of the High "+
	"Warrior.\n");
   set_closed_desc("");
   set_open_command(({"open","turn","push"}));
   set_open_mess(({"pushes the bronze door open.\n", 
      "The door to the Crown Conclave slowly opens wide.\n"}));
   set_fail_open(({"The bronze door is already open!\n",
      "You must unlock the bronze door before it can be opened!\n"}));     
   set_close_command(({"close","pull", "pull closed", "shut"}));
   set_close_mess(({"pulls the bronze door closed.\n", "You pull the Crown " +
      "Door closed.\n"}));
   set_fail_close("The bronze door is already closed.\n");
   set_lock_name(({"lock","keyhole"}));
   set_lock_desc("It is difficult to discern anything about the lock.\n");
   set_lock_command(({"lock","turn key"}));
   set_lock_mess(({"turns a key in the lock of the bronze door.\n",
      "You hear a click from the lock of the bronze door.\n"}));
   set_fail_lock(({"The bronze door is already locked.\n",
      "You feel silly trying to lock an open door!\n"}));
   set_unlock_command(({"unlock","turn key"}));
   set_unlock_mess(({"turns a key in the keyhole, unlocking the bronze door.\n",
      "You hear a click from the lock on the Rose Door, perhaps " +
       "it is unlocked now.\n"}));
   set_fail_unlock("You feel silly trying to lock a door that is " +
      "already locked!\n");
   set_key(CROWN_C_KEY);
   set_pick(101);
} 
