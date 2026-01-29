#include "../../ctower.h"

inherit FIRESTD;
 
#include <tasks.h>

 
#define LIVE_I_FOUND_RUBY "_live_i_found_ctower_ruby"
 
void
create_fire()
{
  add_exit(CTOWER_ROOM_ELEM + "lava", "north");
  add_exit(CTOWER_ROOM_ELEM + "smoke", "east");
  add_exit(CTOWER_ROOM_ELEM + "elem4", "west");
  add_exit(CTOWER_ROOM_ELEM + "elem1", "south");

  remove_item("flames");

  add_item(({"flames", "flame", "fire", "inferno"}), "@@exa_desc");

  add_prop(OBJ_S_SEARCH_FUN, "search_it");
}
 
string
search_it(object player, string what)
{
  if (what != "flames" && what != "flame" && what != "fire" && 
      what != "inferno")
  {
    return 0;
  }

  if (!this_player()->query_prop(LIVE_I_FOUND_RUBY) &&
      player->resolve_task(TASK_SIMPLE, ({ TS_INT, SS_AWARENESS })) > 0)
  {
    this_player()->add_prop(LIVE_I_FOUND_RUBY, 1);
    return "Your search reveals a ruby in the flames!\n";
  }

  return 0;
}
 
string
exa_desc()
{
  if (!this_player()->query_prop(LIVE_I_FOUND_RUBY))
  {
    return  "As you stare deeper into the flames you "+
        "think you can detect a pattern to their dance.  And with the "+
        "last vestiges of your will, you tear your eyes away before it "+
        "is too late.  You are covered in sweat and not sure how much "+
        "time has passed, but you think there may be something in "+
        "the flames.\n" ;
  }

  return  "As you stare deeper into the flames you "+
      "think you can detect a pattern to their dance.  And with the "+
      "last vestiges of your will, you tear your eyes away before it "+
      "is too late.  You are covered in sweat and not sure how much "+
      "time has passed.\n" ;
 
}
 
int
get_it(string str)
{
  object gem;
  int    success;
 
  notify_fail("Get what?\n");
  if (str != "ruby")
  {
   return 0;
  }
 
  if (!this_player()->query_prop(LIVE_I_FOUND_RUBY, 1))
  {
    return 0;
  }
 
  if (this_player()->resolve_task(TASK_ROUTINE, ({ TS_DEX, TS_DEX })) > 0)
  {
    gem = clone_object(CTOWER_OBJ + "firegem");
    gem->move(this_player(), 1);

    write("You quickly grab the ruby.\n");
    return 1;
  }

  write("You try to get the ruby but just aren't quick enough.\n");
  write("You snatch back your hand but not before being burned!\n"); 

  this_player()->reduce_hit_point(this_player()->query_max_hp() / 10);
  if (this_player()->query_hp() <= 0)
  {
    this_player()->do_die(this_object());
  }

  return 1;
}

void
init()
{
  ::init();
 
  add_action(get_it, "get");
  add_action(get_it, "take");
} 
