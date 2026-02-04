/*
    Modified: 30 Apr 2003, by Bleys
        - fixed a number of egregious typos
*/

inherit "/std/door";

#include <stdproperties.h>
#include "/d/Terel/common/terel_defs.h"
#include "tomb.h"

create_door()
{
     ::create_door();
     set_door_id("tomb_door");
     set_pass_command(({"n", "north", "enter", "in"}));
     set_door_desc(BSN(
           "A ponderous and foreboding slab of stone hanging " +
           "on rusty iron hinges\n"));
     set_closed_desc("The door will have to be opened more in order " +
                     "to permit ingress.\n");
     set_open_desc("The opening looks big enough to permit ingress.\n");
     set_door_name(({"stone door","door","slab","stone slab"}));
     set_other_room(TOMBDIR + "tomb01");

     set_fail_pass("The door is not open wide enough.\n");
     set_fail_open(({"The door is already open wide enough for you to " +
                     "enter.\n",
           "The chains and padlock prevent you from opening the " +
           "door any wider.\n"}));
     set_fail_close("The door doesn't close any further.\n");
     set_fail_lock(({"The padlock has already been locked securely.\n",
           "You should close the door first so the chains will " +
           "be tight.\n"}));

     set_fail_unlock("The padlock is already unlocked.\n");
     set_open_mess(({"gives chains slack and pushes the the heavy " +
           "stone\n" +
           "door open just wide enough for someone to " +
           "pass it.\n",
           "The heavy stone door opens just wide enough for someone " +
           " to slip by it.\n"}));
     set_close_mess(({"pulls the chains taut and the opening is much " +
            "smaller now.\n",
            "The heavy stone door closes a little.\n"}));

     set_lock_mess(({"locks the padlock and chains securely.\n",
           "the sound of chains moving against stone can be " +
           "faintly heard.\n"}));
     set_unlock_mess(({"unlocks the padlock and the chains loosen.\n",
           "the sound of chains moving against stone can be " +
           "faintly heard.\n"}));

     set_lock_name(({"lock", "padlock"}));
     set_lock_desc(BSN(
       "It's a padlock.  It looks like it is designed to be used with " +
       "a stone key.\n"));

     set_unlock_command("unlock");
     set_lock_command("lock");

     set_open(0);
     set_locked(1);
    set_key(3141592);
     set_pick(75); /* very hard to pick */
}
