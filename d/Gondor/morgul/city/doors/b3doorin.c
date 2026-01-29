inherit "/std/door";
#include "/d/Gondor/defs.h"

create_door()
{
  ::create_door();
  set_door_id("morgul_b3");
  set_pass_command(({"e","east"}));
  set_door_name(({"wooden door","unpainted door","west door","door"}));
  set_door_desc(BSN(
    "The door leading onto Dark Street to the east is made of crude " +
    "unpainted wooden boards nailed together. There is no lock nor " +
    "handle, so you can just pull to open it and push to close it."));
  set_other_room(MORGUL_DIR + "city/darkstr5");
  set_lock_name("lock");
  set_lock_desc("The unpainted door has neither lock nor handle.\n");
  set_open_command(({"open","pull"}));
  set_open_mess(({"pulls the door open.\n",
                  "Someone pulls at the west the door from inside, opening it.\n"}));
  set_close_command(({"close","push"}));
  set_close_mess(({"pushes the door shut.\n",
                  "Someone pushes the west door from inside, closing it.\n"}));
  set_locked(0);
  set_open(0);
}

