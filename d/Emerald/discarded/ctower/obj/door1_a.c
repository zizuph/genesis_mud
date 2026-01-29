/* ctower/doors/door1_a.c is cloned by ctower/hall3.c */
inherit "/std/door";
 
#include "../ctower.h"
 
void
create_door()
{
  set_door_id("testdoore");
  set_pass_command(({"e", "east"}));
  set_door_name(({"door", "east door"}));
  set_other_room(CTOWER_ROOM + "room3");
  set_open(0);
  set_locked(1);
  set_lock_command("lock");
  set_lock_name("lock");
  set_unlock_command("unlock");
  set_lock_desc("An extremely secure padlock.\n");
  set_pick(80);
  set_key("ctower_quest_key");
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
    write("As you pass through the doorway the prisoner "+
        "melts away to reveal a vicious daemon.\n");
 
    write("The daemon shouts:  Fools, I have waited for "+
        "someone to take my place in this accursed cell!  Now you can "+
        "rot here until some other fool releases you!\n");
 
    write("The daemon disappears in a cloud of smoke and brimstone."+
        "The door slams shut and an evil laugh resounds off the "+
        "cell walls.\n"); 

    this_player()->move_living(query_verb(), other_room);

    write("As you pass the door, it closes behind you!\n");
    do_close_door("");
    other_door->do_close_door("");
    do_lock_door("");
    other_door->do_lock_door("");
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
