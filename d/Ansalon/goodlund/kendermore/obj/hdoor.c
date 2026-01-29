#include "/d/Ansalon/goodlund/kendermore/local.h"
inherit STDDOOR;

create_door()
{
   ::create_door();
   set_door_id("housed1");
   set_pass_command("enter");
   set_door_name(({"oak door","door"}));
   set_other_room(KROOM + "small_house");
   set_door_desc("A door made of oak leads into the house. There's a keyhole under " + 
            "the handle.\n");
   set_lock_command("lock");
   set_lock_mess(({"locks the oak door.\n","You hear the " +
            "lock click.\n"}));
   set_fail_lock(({"The door is already locked.\n","Lock an open " +
            "door?\n"}));
   set_unlock_command("unlock");
   set_unlock_mess(({"unlocks the oak door.\n", "You hear the lock click.\n"}));
   set_fail_unlock("The door is already unlocked.\n");
   set_pick(39);
   set_open(0);
   set_locked(1);
   set_key(HOUSE_KEY);
}

