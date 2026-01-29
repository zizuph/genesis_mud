inherit "/std/door";
#include "/d/Gondor/defs.h"

create_door()
{
  ::create_door();
  set_door_id("hrdoor");
  set_pass_command(({"e","east"}));
  set_door_name(({"wooden door","door"}));
  set_door_desc("The door is made of solid oak. It is the only exit from this chamber.\n");
  set_other_room(HOH_DIR + "w_corr");
  set_lock_command("lock");
  set_lock_name("lock");
  set_unlock_command("unlock");
  set_open(0);
}
