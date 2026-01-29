inherit "/std/door";
#include "/d/Gondor/defs.h"

create_door()
{
  ::create_door();
  set_door_id("barracks_gate");
  set_pass_command(({"s","south"}));
  set_door_name(({"iron gate","gate"}));
  set_other_room(EDORAS_DIR + "field");
  set_lock_command("lock");
  set_lock_name("lock");
  set_unlock_command("unlock");
  set_open(0);
  set_locked(0);
  set_key("_barracks_gate_key");
  set_open_desc("An open iron gate leads south.\n");
  set_closed_desc("A closed iron gate leads south.\n");
}
