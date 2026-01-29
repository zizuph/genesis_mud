// file name: cahor_gate_n.c
// creator(s): Ilyian, Oct 1995
// last update:
// purpose: Gate that blocks the entrance to the 
//          Sanctuary of Cahor
// note:
// bug(s):
// to-do:

inherit "/std/door";
#include "../dead.h"

create_door()
{
   set_door_id("_cahor_gate");
   set_pass_command(({"s", "south", "enter gate", "pass gate"}));
   set_fail_pass("The menacing gate is closed.\n");
   set_door_name(({"menacing gate", "gate"}));

   set_door_desc("This enormous gate has long thick "
     +"bars of iron that twist together in chaotic patterns, "
     +"making you dizzy even looking at it. Through the gate "
     +"you can just make out a dim hallway that extends to "
     +"the south into a fearsome darkness.\nThere is a strange "
     +"symbol over the gate.\n");

   AI(({"symbol","eye","eyes"}),"Inscribed in the arch of the "
     +"gate is an outline of two eyes that are merged "
     +"halfway.\n");
   AI(({"bars","bar","iron","pattern","patterns","chaos"}),"The "
     +"bars of the gate bend and form together in "
     +"bizarre and chaotic patterns that make you dizzy "
     +"even looking at them.\n");
   AI(({"arch","archway"}),"Inscribed in the top of the arch "
     +"of the gate is a strange symbol.\n");
   AI(({"hall","hallway"}),"The hallway on the other side "
     +"of the gate is veiled in gloom. It is narrow, and "
     +"extends to the south.\n");
   set_other_room(DEAD + "cahor/hall1");
   set_open(0);
   set_locked(1);
   set_open_desc("An open menacing gate stands in the south wall.\n");
   set_closed_desc("There is a large menacing gate to the south.\n");
   set_open_command(({"open","turn","push"}));
   set_open_mess(({"swings the menacing gate open.\n",
      "The menacing gate slowly opens.\n"}));
   set_fail_open(({"The gate is already open.\n",
      "The menacing gate is locked.\n"}));
   set_close_command(({"close","pull", "pull closed", "shut"}));
   set_close_mess(({"pulls the menacing gate closed. It slowly "
      +"swings shut with a resounding crash.\n", "The menacing gate "+
       "swings shut with a resounding crash.\n"}));
   set_fail_close("The menacing gate is already closed.\n");
   set_lock_name(({"lock","keyhole"}));
   set_lock_desc("It is a large, strangely shaped lock.\n");
   set_lock_command(({"lock","turn key"}));
   set_lock_mess(({"turns a heavy iron key in the lock of "
     +"the menacing gate.\n",
      "You hear a click from the lock on the mencaing gate.\n"}));
   set_fail_lock(({"The gate is already locked.\n",
      "You must shut the gate before you lock it.\n"}));
   set_unlock_command(({"unlock","turn key"}));
   set_unlock_mess(({"turns a heavy iron key in the keyhole.\n",
      "You hear a click from the lock on the menacing gate.\n"}));
   set_fail_unlock("It is already locked.\n");
   set_key("_cahor_gate_key");
   set_pick(80);
}
