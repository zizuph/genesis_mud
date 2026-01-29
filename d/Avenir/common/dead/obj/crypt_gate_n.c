// file name: crypt_gate_n.c
// creator(s): Ilyian, Oct 1995
// last update:
// purpose: Gate to the entrance of the crypts
// note:
// bug(s):
// to-do:
// Altered by Tilorop 25/2/06.

inherit "/std/door";
#include "../dead.h"

create_door()
{
   set_door_id("_crypt_gate_n");
   set_pass_command(({"s", "south", "enter gate", "pass gate",
                      "sneak south", "sneak s"}));
   set_fail_pass("The solid iron gate is closed.\n");
   set_door_name(({"solid irond gate", "gate"}));

   set_door_desc("This is a large and imposing gate made of thick iron "
       +"bars. Each half of the gate is embalzoned with the trefoil "
       +"seal of Sybarus on each half. It sparks with magical energy "
       +"humming around it.\n);	   
   
   set_other_room(CRYPT + "crypt_entr");
   set_open(0);
   set_locked(1);
   set_open_desc("An open gate leads south into darkness.\n");
   set_closed_desc("There is a solid iron gate to the south.\n");
   set_open_command(({"open","turn","push", "swing"}));
   set_open_mess(({"swings the solid iron gate open soundlessly.\n",
      "The solid iron gate opens noiselessly.\n"}));
   set_fail_open(({"The solid iron gate is already open.\n",
      "The solid iron gate is locked.\n"}));
   set_close_command(({"close","pull", "pull closed", "shut"}));
   set_close_mess(({"pulls the solid ornated gate shut.\n", 
       "The solid ornated gate "+
       "closes noiselessly.\n"}));
   set_fail_close("The solid iron gate is already closed.\n");
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
