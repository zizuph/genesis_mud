// file name:  door_tenb.c
// creator(s): Lilith Feb 2002
// last update: Lucius, Jan 2005: Updated door messages.
// purpose:    door to private room in the bath
// note:       opens onto BATH "se_arc"
//             cloned to  BATH "priv_10"
// bug(s):
// to-do:

inherit "/std/door";

#include "/d/Avenir/common/city/city.h"

void
create_door()
{
    set_door_id("_avenir_bath_ten_");
    set_pass_command(({"nw", "northwest", "pass"}));
    set_fail_pass("The door is closed.\n");
    set_door_name(({"door", "door ten", "tenth door"}));
    set_door_desc("This door northwest leads into the public bath.\n");
    set_other_room(BATH +"se_arc.c");
    set_open(0);
    set_locked(1);
    set_open_desc("The door is open, revealing the public bath "+
       "to the northwest.\n");
    set_closed_desc("");
    set_open_command(({"open","push"}));
    set_open_mess(({"opens the door.\n",
      "The door to room ten opens.\n"}));
   set_fail_open(({"The door is already open.\n",
      "The door is locked.\n"}));
   set_close_command(({"close","shut"}));
   set_close_mess(({"closes the door.\n",
       "The door to room ten closes.\n"}));
   set_fail_close("The door is already closed.\n");
   set_lock_name(({"lock","keyhole"}));
   set_lock_desc("It appears to be the type of lock with a "+
       "knob on this side so you do not need a key to unlock it.\n");
   set_lock_command(({"lock","turn key"}));
   set_lock_mess(({"locks the door to room ten.\n",
       "You hear a click.\n"}));
   set_fail_lock(({"The door is already locked.\n",
      "It is open. You can't lock it while it is open.\n"}));
   set_unlock_command(({"unlock","turn key"}));
   set_unlock_mess(({"unlocks the door to room ten.\n",
      "You hear a click.\n"}));
   set_fail_unlock("It is already locked.\n");
   set_no_show_composite(1); 
}
