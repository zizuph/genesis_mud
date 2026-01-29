inherit "/d/Kalad/open/door";
#include "/d/Kalad/defs.h"

create_door()
{
  ::create_door();
  
  set_door_id("exampledoor");
  set_pass_command(({"n","north"}));
  set_door_name(({"rusty gate","gate"}));
  set_other_room(OPEN(examples/door/room_b));
  set_lock_command("lock");
  set_unlock_command("unlock");
  set_lock_name("lock");
  set_open(0); /*closed*/
  set_locked(1); /*locked*/
  set_pick(20);

  set_bashable(1); /*door is bashable*/
  set_thick(600);  /*make sure its the same as other side of door*/
  set_broken_str("The rusty gate breaks with a loud snap!\n");
}
