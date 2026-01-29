inherit "/std/door";
#include "door.h"
#include "/d/Ansalon/goodlund/nethosak/forest/local.h"

create_door()
{

  set_door_id("gate");

  set_pass_command(({"u","up"}));

  set_door_name(({"heavy iron gate","gate"}));
  set_other_room(MROOM + "forest100");

    /* If you want to have a look on the door you need to define the following
       sets too.
    */
  set_lock_command("lock");
  set_lock_name("lock");
  set_unlock_command("unlock");
  set_open(0);
  set_pick(100);
  set_locked(1);
  set_key(MITHAS_FOREST_CELLAR);

}


