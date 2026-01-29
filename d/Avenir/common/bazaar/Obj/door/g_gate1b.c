// file name: g_gate1b.c
// creator(s): Ilyian, April 1995 (code borrowed from Grace)
// last update:
// purpose: Gate between extr/str17 and green/green1
// note:
// bug(s):
// to-do:

inherit "/std/door";
#include "../../bazaar.h"

create_door()
{
   set_door_id("_entrance_gate_green_str_");
    set_pass_command(({"n", "north", "enter gate", "pass gate"}));
   set_fail_pass("The high gate is closed.\n");
   set_door_name(({"high gate", "gate"}));

   set_door_desc("This is a high gate of thick iron bars. Through "
     +"the bars you can see a wide street that runs through the "
     +"crowded marketplace.\n");
   AI(({"market","north","marketplace","bazaar"}),"The market you "
     +"can see through the bars is a noisy area crowded with people "
     +"and merchants hawking their wares.\n");
   set_other_room(BAZAAR + "extr/str17");
   set_open(0);
   set_locked(0);
   set_open_desc("An open iron gate is to the north.\n");
   set_closed_desc("A closed iron gate is to the north.\n");
   set_open_command(({"open","lift","push"}));
   set_open_mess(({"swings the iron gate open, its hinges complaining "
      +"with a shrieking noise.\n",
      "The iron gate opens, its hinges making a shrieking noise.\n"}));
   set_fail_open(({"The gate is already open.\n",
      "The iron gate is locked.\n"}));
   set_close_command(({"close","pull", "pull closed", "shut"}));
   set_close_mess(({"pulls the iron gate closed. The shrieking of the "
       +"hinges is deafening.\n", "The iron gate "+
       "swings shut on noisy hinges.\n"}));
   set_fail_close("The iron gate is already closed.\n");
   set_lock_name(({"lock","keyhole","latch"}));
   set_lock_desc("It is a heavy iron latch that keeps the gate shut, "
        +"with a large keyhole in the center of it.\n");
   set_lock_command(({"lock","turn key"}));
   set_lock_mess(({"turns a key in the lock of the iron gate.\n",
      "You hear a click from the latch on the iron gate.\n"}));
   set_fail_lock(({"The gate is already locked.\n",
      "You must shut the gate before you lock it.\n"}));
   set_unlock_command(({"unlock","turn key"}));
   set_unlock_mess(({"turns a key in the keyhole and unlocks the "+
      "iron gate.\n",
      "You hear a click from the lock on the iron gate.\n"}));
   set_fail_unlock("It is already locked.\n");
   set_key("_iron_gate_key_");
   set_pick(34);  //easy enough to pick...

}
