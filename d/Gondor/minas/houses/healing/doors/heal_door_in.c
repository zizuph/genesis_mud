inherit "/std/door";
#include "/d/Gondor/defs.h"

create_door()
{
  ::create_door();
  set_door_id("heal_door");
  set_pass_command(({"n","north"}));
  set_door_name(({"stone door","door"}));
  set_other_room(HOH_DIR + "heal_garden1");
  set_door_desc("The door is made of solid stone.\n");
  set_lock_command("lock");
  set_lock_name("lock");
  set_unlock_command("unlock");
  set_open(0);
  set_locked(0);
}
