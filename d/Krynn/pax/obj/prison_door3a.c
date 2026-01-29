/*
   Door from corridor3 into maidens prison

   prison_door3a.c
   ---------------
 
   Coded ........: 95/01/09
   By ...........: Jeremiah

   latest update : 95/05/04
   By ...........: Jeremiah

*/

#include "/d/Krynn/pax/local.h"
inherit STDDOOR;

create_door()
{
   ::create_door();
   set_door_id("prisondoor3");
   set_pass_command(({"n", "north"}));
   set_door_name(({"iron door", "door"}));
   set_other_room(LOW_LEVEL + "m_prison");
   set_door_desc("This is a solid iron clad door. There is a large " +
                 "keyhole in the middle left side of the door, right " +
                 "under the door handle.\n");
   set_lock_command("lock");
   set_lock_mess(({"locks the iron door.\n", "You hear a loud " +
                   "'click' from the doorlock.\n"}));
   set_fail_lock(({"The door is already locked.\n", "The door is open.\n"}));
   set_unlock_command("unlock");
   set_unlock_mess(({"unlocks the iron door.\n", "You hear a loud " +
                     "'click' from the doorlock.\n"}));
   set_fail_unlock("The door is already unlocked.\n");

   set_pick(60);

   set_open(0);
   set_locked(1);

   set_key(PRISON_KEY);
}

