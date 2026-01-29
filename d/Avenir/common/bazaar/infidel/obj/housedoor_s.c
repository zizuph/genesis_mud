// file name: housedoor_s.c
// creator(s): Ilyian, Oct 1995
// last update:
// purpose: Door entering the house of the Infidel hideout
// note:
// bug(s):
// to-do:

inherit "/std/door";
#include "../infidel.h"

create_door()
{
   set_door_id("_infidel_house_door_");
    set_pass_command(({"n", "north", "enter house", "sneak north"}));
   set_fail_pass("The heavy oak door is closed.\n");
    set_door_name(({"heavy oak door", "door"}));

   set_door_desc("This is a heavy oak door that leads "
                +"north into the house.\n");
   set_other_room(INFID + "house");
   set_open(0);
   set_locked(1);
   set_open_desc("There is an open wooden door to the north.\n");
   set_closed_desc("A closed wooden door lies north.\n");
   set_open_command(({"open","turn","push"}));
   set_open_mess(({"swings the heavy oak door open.\n",
      "The oaken door opens.\n"}));
   set_fail_open(({"The heavy oak door is already open.\n",
      "The heavy oak door is locked.\n"}));
   set_close_command(({"close","pull", "pull closed", "shut"}));
   set_close_mess(({"swings the oak door shut.\n", "The oak door "+
       "closes.\n"}));
   set_fail_close("The heavy oak door is already closed.\n");
   set_lock_name(({"lock","keyhole"}));
   set_lock_desc("It is a small, normal lock.\n");
   set_lock_command(({"lock","turn key"}));
   set_lock_mess(({"turns a key in the lock of the heavy oak door.\n",
      "You hear a click from the lock on the heavy oak door.\n"}));
   set_fail_lock(({"The door is already locked.\n",
      "You must shut the door before you lock it.\n"}));
   set_unlock_command(({"unlock","turn key"}));
   set_unlock_mess(({"turns a key in the keyhole and unlocks the "+
      "heavy oak door.\n",
      "You hear a click from the lock on the heavy oak door.\n"}));
   set_fail_unlock("It is already unlocked.\n");
   set_key("_infidel_hideout_key_");
   set_pick(34);  //easy enough to pick...

}
