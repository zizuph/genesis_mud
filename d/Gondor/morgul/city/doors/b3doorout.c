inherit "/std/door";
#include "/d/Gondor/defs.h"

create_door()
{
  ::create_door();
  set_door_id("morgul_b3");
  set_pass_command(({"w","west"}));
  set_door_name(({"wooden door","unpainted door","west door","door"}));
  set_door_desc(BSN(
    "The door leading into the house to the west is made of crude " +
    "unpainted wooden boards nailed together. There is no lock nor " +
    "handle, so you can just push to open it and pull to close it."));
  set_other_room(MORGUL_DIR + "city/barrack3");
  set_lock_name("lock");
  set_lock_desc("The unpainted door has neither lock nor handle.\n");
  set_open_command(({"open","push"}));
  set_open_mess(({"pushes the door open.\n",
                  "Someone pushes at the door from the outside, opening it.\n"}));
  set_close_command(({"close","pull"}));
  set_close_mess(({"pulls the door shut.\n",
                  "Someone pulls at the door from the outside, closing it.\n"}));
  set_locked(0);
  set_open(0);
}

