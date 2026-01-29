inherit "/std/door";
#include "/d/Gondor/defs.h"

create_door()
{
  ::create_door();
  set_door_id("hrdoor");
  set_pass_command(({"e","east"}));
  set_door_name(({"wooden door","door"}));
  set_door_desc("The wooden door bears a sign reading: \n"+
    "        Male Healing Room  II.\n");
  set_other_room(HOH_DIR + "healroom2");
  set_locked(0);
  set_open(0);
  set_key("h_o_h_rooms_key");
  set_pick(30);
  set_lock_command("lock");
  set_lock_name("lock");
  set_unlock_command("unlock");
}

int pass_door(string arg)
{
  if (ENV(TO)->check_guards() == 0)
    ::pass_door(arg);
  return 1;
}

