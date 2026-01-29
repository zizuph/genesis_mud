// file name: crypt_gate_s.c
// creator(s): Ilyian, Oct 1995
// last update:
// purpose: Gate to the entrance of the crypts
// note:
// bug(s):
// to-do:
// Altered by Tilorop, 25/2/06.

inherit "/std/door";
#include "../dead.h"

create_door()
{
   set_door_id("_crypt_gate");
   set_pass_command(({"n", "north", "enter gate", "pass gate",
                      "sneak north", "sneak n"}));
   set_fail_pass("The solid ornated gate is closed.\n");
   set_door_name(({"solid ornated gate", "gate"}));

   set_door_desc("This large gate of unknown alloy glows with " +
   "powerful magical energies. In its centre you see a carving " +
   "of a splayed skeletal hand with a lidless eye in its palm, " +
   "surrounded by a serpent biting its own tail.\n");

   set_other_room(PATH + "shore25");
   set_open(0);
   set_locked(1);
   set_open_desc("An open ornated gate leads north to the outside.\n");
   set_closed_desc("There is a solid ornated gate to the north.\n");
   set_open_command(({"open","turn","push"}));
   set_open_mess(({"swings the solid ornated gate open noiselessly.\n",
      "The solid ornated gate opens with a frightening noiselessness.\n"}));
   set_fail_open(({"The gate is already open.\n",
      "The solid ornated gate is locked.\n"}));
   set_close_command(({"close","push", "push closed", "shut"}));
   set_close_mess(({"pushes the solid ornated gate shut.\n", 
       "The solid ornated gate "+
       "closes noiselessly.\n"}));
   set_fail_close("The solid ornated gate is already closed.\n");
   set_lock_name(({"lock","keyhole"}));
   set_lock_desc("It is a large, strangely shaped lock.\n");
   set_lock_command(({"lock","turn key"}));
   set_lock_mess(({"turns strangely shaped key in the lock of "
     +"the solid ornated gate.\n",
      "You hear a click from the lock on the solid ornated gate.\n"}));
   set_fail_lock(({"The gate is already locked.\n",
      "You must shut the gate before you lock it.\n"}));
   set_unlock_command(({"unlock","turn key"}));
   set_unlock_mess(({"turns a strangly shaped key in the keyhole.\n",
      "You hear a loud click from the lock on the solid ornated gate.\n"}));
   set_fail_unlock("It is already locked.\n");
   set_key("_avenir_cryptmain_gate_key");
    set_pick(100);
}
