inherit "/std/door";
#include "/d/Gondor/defs.h"

create_door()
{
  ::create_door();
  set_door_id("morgul_b11");
  set_pass_command(({"w","west"}));
  set_door_name(({"wooden door","black door","east door","door"}));
  set_door_desc(BSN(
    "The door leading onto Dark Street to the east is made of crude " +
    "wooden boards nailed together and painted black. There is no lock nor " +
    "handle, so you can just pull to open it and push to close it."));
  set_other_room(MORGUL_DIR + "city/darkstr5");
  set_lock_name("lock");
  set_lock_desc("The black door has neither lock nor handle.\n");
  set_open_command(({"open","pull"}));
  set_open_mess(({"pulls the door open.\n",
                  "Someone pulls at the east the door from inside, opening it.\n"}));
  set_close_command(({"close","push"}));
  set_close_mess(({"pushes the door shut.\n",
                  "Someone pushes the east door from inside, closing it.\n"}));
  set_locked(0);
  set_open(0);
}

