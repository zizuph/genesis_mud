/* ctower/doors/door2_a.c is cloned by ctower/hall3.c */
inherit "/std/door";
 
#include "../ctower.h"
 
void
create_door()
{
  set_door_id("testdoorw");
  set_pass_command(({"w", "west"}));
  set_door_name(({"door", "west door"}));
  set_other_room(CTOWER_ROOM + "room5");
  set_open(0);
  set_locked(1);
  set_lock_command("lock");
  set_lock_name("lock");
  set_unlock_command("unlock");
  set_key("ctower_quest_key");
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
    write("As you pass through the doorway the daemon "+
        "melts away to reveal a gleaming white knight.\n");
 
    write("The knight says:  Congratulations, you have "+
        "correctly passed the first test by remembering that, in the "+
        "Crystal Tower, not all is as it appears.  I am afraid that "+
        "I must stay here, a force of equal good is needed to balance "+
        "out the force of evil that is the daemon in the other cell.  But "+
        "I can help you another way...go down two flights of stairs to "+
        "reach the next level, and there is a talisman in the desk you will "+
        "need to complete the quest.  Good luck!\n");
 
    write("The knight goes back to his reading.\n");
 
    this_player()->move_living(query_verb(), other_room);
  }
  else
  {
    write(check_call(fail_pass));
  }
 
  return 1;
}

int
lock_procedure(string arg)
{
  object *keys;
  int ret = ::lock_procedure(arg);

  if (ret && sizeof(keys = filter(all_inventory(this_player()),
      &operator(==)(, key) @ &->query_key())))
  { 
    write("As you " + query_verb() + " the door, the key fuses with " +
        "the lock!\n");
    keys[0]->remove_object();
  }

  return ret;
}
