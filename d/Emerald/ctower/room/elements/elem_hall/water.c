#include "../../../ctower.h"

inherit WATERSTD;
 
#include <tasks.h>
 
#define LIVE_I_FOUND_SPINEL "_live_i_found_ctower_spinel"
 
void
create_water()
{
    add_exit("mist", "south");
    add_exit("elem12", "north");
    add_exit("elem9", "east");
    add_exit("mud", "west");
  
    remove_item("water");
  
    add_item(({"water"}), "@@exa_desc");
  
    add_prop(OBJ_S_SEARCH_FUN, "search_it");
}
 
string
search_it(object player, string what)
{
  if (what != "water")
  {
    return 0;
  }

  if (!this_player()->query_prop(LIVE_I_FOUND_SPINEL) &&
      player->resolve_task(TASK_SIMPLE, ({ TS_INT, SS_AWARENESS })) > 0)
  {
    this_player()->add_prop(LIVE_I_FOUND_SPINEL, 1);
    return "Your search reveals a spinel in the water!\n";
  }

  return 0;
}
 
string
exa_desc()
{
  if (!this_player()->query_prop(LIVE_I_FOUND_SPINEL))
  {
    return "It is normal water although you "+
        "are not sure how it stays in the room.  Just for a moment, " +
        "something seemed to appear in the currents.\n";
  }
 
  return "It is normal water although you "+
      "are not sure how it stays in the room.";
}
 
int
get_it(string str)
{
  object gem;
 
  notify_fail("Get what?\n");
  if (str != "spinel")
  {
    return 0;
  }
 
  if (!this_player()->query_prop(LIVE_I_FOUND_SPINEL))
  {
    return 0;
  }
 
  if (this_player()->resolve_task(TASK_ROUTINE, ({ TS_DEX, TS_DEX })) > 0)
  {
    gem = clone_object(CTOWER_OBJ + "watergem");
    gem->move(this_player(), 1);

    write("You quickly grab the spinel.\n");
    return 1;
  }
 
  write("You try to get the spinel but just aren't quick enough.\n");
  write("You swallow some water by accident, choking!\n");

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
