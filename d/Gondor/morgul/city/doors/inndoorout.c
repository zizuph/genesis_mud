inherit "/std/door";
#include "/d/Gondor/defs.h"

create_door()
{
  ::create_door();
  set_door_id("morgul_inn");
  set_pass_command(({"e","east"}));
  set_door_name(({"inn door", "inndoor", "wooden door","door"}));
  set_door_desc(BSN(
    "It is a large wooden door painted black. On it you can read " +
    "the letters: ") +
    "\n        Red Eye Inn\n" +
    "    Ramarth, proprietor \n\n");
  set_other_room(MORGUL_DIR + "city/rooms/inn");
  set_lock_command("lock");
  set_lock_name("lock");
  set_unlock_command("unlock");
  set_open(0);
  set_locked(0);
  set_key("_minas_morgul_inn_key");
}
