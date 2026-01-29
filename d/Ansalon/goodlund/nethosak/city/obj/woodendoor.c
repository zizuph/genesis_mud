inherit "/std/door";
#include "door.h"
#include "/d/Ansalon/goodlund/nethosak/city/local.h"
//#include <stdproperties.h>
//inherit MITHAS_IN;

create_door()
{

  set_door_id("door");

  set_pass_command(({"n","north"}));

  set_door_name(({"heavy wooden door","door"}));
  set_other_room(MROOM + "barracks5");

    /* If you want to have a look on the door you need to define the following
       sets too.
    */
  set_lock_command("lock");
  set_lock_name("lock");
  set_unlock_command("unlock");

}

