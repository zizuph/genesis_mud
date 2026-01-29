/*
Door for Theobald's residence.

*/

inherit "/d/Krynn/std/door";

create_door()
{
   ::create_door();
   set_door_id("theobald_door");
   set_pass_command("south");
   set_door_name(({"elaborate double door","double door","door"}));
   set_other_room("/d/Krynn/solace/poolbottom/room/ng_hall");
   set_door_desc("This elaborate double door leads out of the " +
       "private residence of Master Theobald, and in to the great hall " +
       "of the school of High Magic.\n");
   set_lock_command("lock");
   set_lock_mess(({"locks the elaborate double door.\n","You hear the " +
            "tumblers of the door's lock fall into place with a soft 'click'.\n"}));
   set_fail_lock(({"The elaborate double door is already locked.\n","Lock an open " +
            "door?\n"}));
   set_unlock_command("unlock");
    set_unlock_mess(({"unlocks the elaborate double door.\n", "The lock to the  " +
            "elaborate double door 'clicks' as the tumblers fall in to place.\n"}));
   set_fail_unlock("The elaborate double door is already unlocked.\n");
   set_pick(39);
   set_open(0);
   set_locked(1);
   set_key(8874653);
}

