#include "../../ctower.h"

inherit EARTHSTD;
 
#include <tasks.h>
 
#define LIVE_I_FOUND_TOURMALINE "_live_i_found_ctower_tourmaline"
 
void
create_earth()
{
  add_exit(CTOWER_ROOM_ELEM + "elem10", "north");
  add_exit(CTOWER_ROOM_ELEM + "elem8", "west");
  add_exit(CTOWER_ROOM_ELEM + "mud", "east");
  add_exit(CTOWER_ROOM_ELEM + "lava", "south");

  remove_item("ground");

  add_item(({"ground", "floor", "earth", "soil"}), "@@exa_desc");

  add_prop(OBJ_S_SEARCH_FUN, "search_it");
}
 
string
search_it(object player, string what)
{
  if (what != "ground" && what != "floor" && what != "earth" && 
      what != "soil")
  {
    return 0;
  }

  if (!this_player()->query_prop(LIVE_I_FOUND_TOURMALINE) &&
      player->resolve_task(TASK_SIMPLE, ({ TS_INT, SS_AWARENESS })) >= 0)
  {
    this_player()->add_prop(LIVE_I_FOUND_TOURMALINE, 1);
    return "Your search reveals a tourmaline in the ground!\n";
  }

  return 0;
}
 
string
exa_desc()
{
  if (!this_player()->query_prop(LIVE_I_FOUND_TOURMALINE))
  {
    return "The ground is made of rich soil that is "+
        "about a foot deep.  You also think you felt something.\n" ;
  }

  return "The ground is made of rich soil that is "+
      "about a foot deep.\n" ;
}
 
int
get_it(string str)
{
  object gem;
 
  notify_fail("Get what?\n");
  if (str != "tourmaline")
  {
    return 0;
  }
 
  if (!this_player()->query_prop(LIVE_I_FOUND_TOURMALINE))
  {
    return 0;
  }
 
  if (this_player()->resolve_task(TASK_ROUTINE, ({ TS_DEX, TS_DEX })) > 0)
  {
    gem = clone_object(CTOWER_OBJ + "earthgem");
    gem->move(this_player(), 1);

    write("You quickly grab the tourmaline.\n");
    return 1;
  }

  write("You try to get the tourmaline but just aren't quick enough.\n");
  write("Your hand gets smashed but you snatch it back before worse " +
      "happens!\n"); 

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
