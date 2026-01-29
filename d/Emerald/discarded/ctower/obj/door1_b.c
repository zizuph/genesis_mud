/* ctower/doors/door1_b.c is cloned by ctower/room3.c */
inherit "/std/door";
 
#include "/d/Emerald/defs.h"
 
void
create_door()
{
  set_door_id("testdoore");
  set_pass_command(({"w", "west"}));
  set_door_name(({"crystal door", "door"}));
  set_other_room(CTOWER_DIR + "hall3");
  set_open(0);
  set_locked(1);
  set_lock_name("lock");
  set_lock_desc("You can't find a lock.\n");
  set_lock_command("lock");
  set_unlock_command("unlock");
  set_no_pick();
}

int lock_procedure(string str)
{
  string key_str, door;

  if (sscanf(str, "%s with %s", door, key_str) != 2)
  {
    door = str;
  }

  if (member_array(door, door_name) < 0)
  {
    notify_fail("Unlock what?\n");
    return 0;
  }

  notify_fail("You can't find a lock.\n");
  return 0;
}
