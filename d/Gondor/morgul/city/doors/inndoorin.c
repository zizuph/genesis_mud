inherit "/std/door";
#include "/d/Gondor/defs.h"

create_door()
{
  ::create_door();
  set_door_id("morgul_inn");
  set_pass_command(({"w","west"}));
  set_door_name(({"wooden door","door"}));
  set_door_desc(BSN("The door leads out of the inn onto a dark and narrow street. "));
  set_other_room(MORGUL_DIR + "city/darkstr3");
  set_lock_command("lock");
  set_lock_name("lock");
  set_unlock_command("unlock");
  set_open(0);
  set_locked(0);
  set_key("_minas_morgul_inn_key");
}
