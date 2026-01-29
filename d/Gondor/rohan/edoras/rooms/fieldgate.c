inherit "/std/door";
#include "/d/Gondor/defs.h"

create_door()
{
  ::create_door();
  set_door_id("barracks_gate");
  set_pass_command(({"n","north"}));
  set_door_name(({"iron gate","gate"}));
  set_other_room(EDORAS_DIR + "rooms/bhallway");
  set_lock_command("lock");
  set_lock_name("lock");
  set_unlock_command("unlock");
  set_open(0);
  set_locked(0);
  set_key("_barracks_gate_key");
}
