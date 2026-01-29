/* ctower/doors/door2_b.c is cloned by ctower/room5.c */
inherit "/std/door";
 
#include <filter_funs.h>
#include "../ctower.h"
 
void
create_door()
{
  set_door_id("testdoorw");
  set_pass_command(({"e", "east"}));
  set_door_name(({"crystal door", "door"}));
  set_other_room(CTOWER_ROOM + "hall3");
  set_open(0);
  set_locked(1);
  set_lock_command("lock");
  set_lock_name("lock");
  set_unlock_command("unlock");
  set_key("phase_quest_key");
  set_pick(101);
}
 
int
pass_door(string arg)
{
  if (!other_door)
  {
    load_other_door();
  }

  if (open_status)
  {
    this_player()->move_living(query_verb(), other_room);

    if (!sizeof(FILTER_PLAYERS(all_inventory(environment()))))
    {
      write("As you pass the door, it closes behind you!\n");
      do_close_door("");
      other_door->do_close_door("");
      do_lock_door("");
      other_door->do_lock_door("");
    }
  }
  else
  {
    write(check_call(fail_pass));
  }
 
  return 1;
}
