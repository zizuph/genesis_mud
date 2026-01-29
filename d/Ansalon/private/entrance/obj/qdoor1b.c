#include "/d/Ansalon/goodlund/kendermore/local.h"

inherit STDDOOR;

create_door()
{
    ::create_door();
    set_door_id("qdoor1b");
    set_pass_command("west");
    set_door_name(({"metal door", "black metal door", "black door", "door"}));
    set_other_room("/d/Ansalon/private/entrance/room/q2");
    set_door_desc("It is a strong black door. Made of heavy metal, " + 
        "it's impossible to break through.\n");
    set_lock_command("lock");
    set_lock_mess(({"locks the black metal door.\n", "You hear the lock " + 
        "click.\n"}));
    set_fail_lock("The door is already unlocked.\n");
    set_unlock_command("unlock");
    set_unlock_mess(({"unlocks the black metal door.\n", "You hear the " +
        "lock click.\n"}));
    set_fail_unlock("The door is already unlocked.\n");
    set_pick(80);
    set_open(0);
    set_locked(1);
    set_key(FOO_BAR);                                                          
}
