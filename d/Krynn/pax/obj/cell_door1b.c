/*
   Door from cell into corridor, ground level.

   cell_door1b.c
   -------------
 
   Coded ........: 95/01/28
   By ...........: Jeremiah

   latest update : 95/01/28
   By ...........: Jeremiah

*/

#include "/d/Krynn/pax/local.h"
inherit STDDOOR;

create_door()
{
   ::create_door();
   set_door_id("celldoor1");
   set_pass_command(({"s", "south"}));
   set_door_name(({"iron door", "door"}));
   set_other_room(GROUND_LEVEL + "corridor2");
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

