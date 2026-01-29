inherit "/std/door";

#include "door.h"
#include "def.h"
#include "/d/Rhovanion/defs.h"

create_door()
{
  /* id for this door. */
  set_door_id("c1_door");


  /* How to get through the door. */
  set_pass_command(({"n","north"}));

  /* The name of the door */
  set_door_name(({"iron door","door"}));

  /* This is the other side of the door */
  set_other_room(THIS_DIR + "C1");

  /* If you want to have a lock on the door you need to define the following
   * sets too. 
   */
  set_lock_command("lock");
  set_lock_name("lock");
  set_unlock_command("unlock");

  /* The door is locked when reset. */
  set_open(0);
  set_locked(1);
  set_no_pick();
}
