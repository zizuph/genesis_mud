/*
Door for the Heartroom.

*/

inherit "/d/Krynn/std/door";

create_door()
{
   ::create_door();
   set_door_id("heartroom_door");
   set_pass_command("west");
   set_door_name(({"runed double door","double door","door"}));
   set_other_room("/d/Krynn/guilds/wohs/test/room/heartroom");
   set_door_desc("This runed double door is the entrance to the " +
       "Heartroom of the crimson tower of Daltigoth. An arcane lock " +
       "protects it from anyone but those the Master of the Tower " +
       "allows entry.\n");
   set_lock_command("lock");
   set_lock_mess(({"locks the runed double door.\n","You hear the arcane " +
       "tumblers of the door's lock fall into place with a soft " +
       "'click'.\n"}));
   set_fail_lock(({"The runed double door is already locked.\n",
       "Lock an open door?\n"}));
   set_unlock_command("unlock");
   set_unlock_mess(({"unlocks the runed double door.\n", 
       "The lock to the runed double door 'clicks' as the arcane " +
       "tumblers fall in to place.\n"}));
   set_fail_unlock("The runed double door is already unlocked.\n");
   set_pick(100);
   set_open(0);
   set_locked(1);
   set_key(8874654);
}

