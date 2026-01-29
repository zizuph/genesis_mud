inherit "/std/door";
#include "/d/Gondor/defs.h"

create_door()
{
  ::create_door();
  set_door_id("morgul_b11");
  set_pass_command(({"e","east"}));
  set_door_name(({"black door","east door","door"}));
  set_door_desc(BSN(
    "The door leading into the house to the east is made of crude " +
    "wooden boards nailed together that have been painted black. There is no lock nor " +
    "handle, so you can just push to open it and pull to close it."));
  set_other_room(MORGUL_DIR + "city/barrack11");
  set_lock_name("lock");
  set_lock_desc("The black door has neither lock nor handle.\n");
  set_open_command(({"open","push"}));
  set_open_mess(({"pushes the door open.\n",
                  "Someone pushes at the door from the outside, opening it.\n"}));
  set_close_command(({"close","pull"}));
  set_close_mess(({"pulls the door shut.\n",
                  "Someone pulls at the door from the outside, closing it.\n"}));
  set_locked(0);
  set_open(0);
}

