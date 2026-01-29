inherit "/std/door";
#include "door.h"
#include "/d/Ansalon/goodlund/nethosak/city/local.h"
//#include <stdproperties.h>
//inherit MITHAS_IN;

create_door()
{

  set_door_id("gate");
  set_pass_command(({"n","north"}));
  set_door_name(({"heavy iron gate","gate"}));
  set_other_room("/d/Ansalon/goodlund/nethosak/"+
                 "city/room/road25"); 
  set_open(0); 
  set_locked(1);
  set_no_pick();
}

