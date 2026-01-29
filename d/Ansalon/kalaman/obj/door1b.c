
#include "/d/Ansalon/kalaman/local.h"
inherit STDDOOR;

create_door()
{
    ::create_door();
    set_door_id("door1");
    set_pass_command("east");
    set_door_name(({"storeroom door","door"}));
    set_other_room("/d/Ansalon/kalaman/room/office");
    set_door_desc("This is a sturdy wooden door, with a lock that could almost be classed " +
      "as thief proof.\n");
    set_lock_command("lock");
    set_lock_mess(({"locks the storeroom door.\n","You lock the storeroom door.\n"}));
    set_fail_lock(({"The door is already locked.\n","Lock an open door?\n"}));
    set_unlock_command("unlock");
    set_unlock_mess(({"unlocks the storeroom door.\n","You unlock " +
	"the storeroom door with a noisy 'click' of the lock.\n"}));
    set_fail_unlock("The door is already unlocked.\n");
    set_pick(45);
    set_open(0);
    set_locked(1);
    set_key(BOGUS_KEY);
}

