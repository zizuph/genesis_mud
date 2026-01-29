// file name: gate_s.c
// creator(s): Ilyian, April 1995 (code borrowed from Grace)
// last update:
// purpose: Gate between green/s_shore and green/green17
// note:
// bug(s):
// to-do:

inherit "/std/door";
#include "../../bazaar.h"

create_door()
{
   set_door_id("_silver_gate_green_");
    set_pass_command(({"n", "north", "enter gate", "pass gate"}));
   set_fail_pass("The silver gate is closed.\n");
    set_door_name(({"silver gate", "gate"}));

   set_door_desc("This silver gate gleams from the light. It is high, "
      +"and from both sides of it extend a wall. It has a small latch in "
      +"the middle, with a lock beneath it. Through the gate, you can "
      +"see the beginning of a path through a strange garden, and "
      +"next to the gate, on the other side, sits a stone bench.\n");
   AI(({"path","garden"}),"The garden on the other side of the gate "
      +"seems to extent for quite a ways. It is full of strange plants "
      +"and sweet smelling herbs.\n");
   AI(("bench"),"A stone bench lies next to the wall on the other side "
      +"of the gate. From this angle, you cannot see if there is anyone "
      +"sitting on it.\n");
   set_other_room(BAZAAR + "green/green17");
   set_open(0);
   set_locked(1);
   set_open_desc("An open gate leading north.\n");
   set_closed_desc("A closed silver gate leading north.\n");
   set_open_command(({"open","turn","push"}));
   set_open_mess(({"swings the silver gate noiselessly open.\n",
      "The silver gate glides open on noiseless hinges.\n"}));
   set_fail_open(({"The gate is already open.\n",
      "The silver gate is locked.\n"}));
   set_close_command(({"close","pull", "pull closed", "shut"}));
   set_close_mess(({"pulls the silver gate closed. It swings shut on "
       +"silent hinges.\n", "The silver gate "+
       "swings shut on silent hinges.\n"}));
   set_fail_close("The silver gate is already closed.\n");
   set_lock_name(({"lock","keyhole"}));
   set_lock_desc("It is a small, strangely shaped lock.\n");
   set_lock_command(({"lock","turn key"}));
   set_lock_mess(({"turns a key in the lock of the silver gate.\n",
      "You hear a click from the lock on the silver gate.\n"}));
   set_fail_lock(({"The gate is already locked.\n",
      "You must shut the gate before you lock it.\n"}));
   set_unlock_command(({"unlock","turn key"}));
   set_unlock_mess(({"turns a key in the keyhole and unlocks the "+
      "silver gate.\n",
      "You hear a click from the lock on the silver gate.\n"}));
   set_fail_unlock("It is already locked.\n");
   set_key("_silver_gate_key_");
   set_pick(75);

}
