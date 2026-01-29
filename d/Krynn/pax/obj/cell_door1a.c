/*
   Door from corridor into cell, ground level.

   cell_door1a.c
   -------------
 
   Coded ........: 95/01/28
   By ...........: Jeremiah

   latest update : 95/05/21
   By ...........: Jeremiah

*/

#include "/d/Krynn/pax/local.h"
inherit STDDOOR;

create_door()
{
   ::create_door();
   set_door_id("celldoor1");
   set_pass_command(({"n", "north"}));
   set_door_name(({"iron door", "door"}));
   set_other_room(GROUND_LEVEL + "cell_old");
   set_door_desc("This is a sturdy iron reinforced door.\n");
   set_lock_command("lock");
   set_lock_mess(({"locks the sturdy iron door.\n", "You hear a " +
                 "loud 'click' from the doorlock.\n"}));
   set_fail_lock(({"The door is already locked.\n", "Lock an open " +
                 "door ?.\n"}));
   set_unlock_command("unlock");
   set_unlock_mess(({"unlock the sturdy iron door.\n", "You hear " +
                   "a loud 'click' from the doorlock.\n"}));
   set_fail_unlock("The door is already unlocked.\n");
   set_pick(100); 
   set_open(0);
   set_locked(1);
   set_key(CELL_KEY);
}

