/*

cell_door1a.c
-------------

Coded ........: 95/01/28
By ...........: Jeremiah

latest update : 96/12/16
By ...........: Arman

*/

#include "/d/Ansalon/kalaman/local.h"
inherit STDDOOR;

create_door()
{
    ::create_door();
    set_door_id("door1");
    set_pass_command("northeast");
    set_door_name(({"elaborate gate","gate"}));
    set_other_room(CITY + "g3");
    set_door_desc("This elaborate gate marks the " +
      "entrance and exit of a private garden, that " +
      "you can see to the east.\n");
    set_lock_command("lock");
    set_lock_mess(({"locks the elaborate gate.\n","The lock " +
	"'clicks' loudly as you lock the elaborate gate.\n"}));
    set_fail_lock(({"The elaborate gate is already locked.\n",
	"No point in locking an open gate.\n"}));
    set_unlock_command("unlock");
    set_unlock_mess(({"unlocks the elaborate gate.\n","The lock " +
	"clicks open as you turn the key.\n"}));
    set_fail_unlock("The gate is already unlocked.\n");
    set_pick(20);
    set_open(0);
    set_locked(1);
    set_key(BOGUS_KEY);
}

