// file name: gate_n.c
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
    set_pass_command(({"s", "south", "enter gate", "pass gate"}));
   set_fail_pass("The silver gate is closed.\n");
    set_door_name(({"silver gate", "gate"}));

   set_door_desc("This silver gate gleams from the light. It is high, "
      +"and from both sides of it extend a wall. It has a small latch in "
      +"the middle, with a lock beneath it. Through the gate, you can see "
      +"the edge of the island, with dark water gently lapping at the "
      +"shore. On the other side, a large, arched bridge stretched accross "
      +"the water to another island.\n");
   AI(({"water","sea"}),"The dark water laps agains the shore on the "
      +"other side of the gate.\n");
   AI(("bridge"),"On the other side of the gate, the massive bridge arches "
      +"steeply over the sea, reaching accross to another island. It looks "
      +"very sturdy and very old, being made from blackened stone. In the "
      +"center of the bridge you think you can make out two statues.\n");
   AI(("island"),"You can not make out any of the details of the island "
      +"from this distance.\n");
   set_other_room(BAZAAR + "green/s_shore");
   set_open(0);
   set_locked(1);
   set_open_desc("An open gate is to the south.\n");
   set_closed_desc("A closed silver gate is to the south.\n");
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
