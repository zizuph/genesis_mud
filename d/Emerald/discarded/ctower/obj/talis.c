/* ctower/obj/talis.c is cloned by ctower/maze22.c */
inherit "/std/object";
inherit "/d/Emerald/ctower/obj/ctower_obj_base";

#include "/d/Emerald/defs.h"
#include <tasks.h>
#include <macros.h>
#include <stdproperties.h>

void get_it(object who);
 
void
reset_object()
{
    reset_ctower_object();
}

void
create_object()
{
  set_name("talisman");
  add_name("phase_quest_talis");
  set_short("talisman of protection");
  add_adj("for");             // cheap way to allow 'search for talisman'
  set_long("This is a crystal talisman with four symbols on it.\n");
  add_prop(OBJ_I_WEIGHT, 100);
  add_prop(OBJ_I_VOLUME, 20);
  add_prop(OBJ_I_VALUE, 144);
  add_prop(OBJ_M_NO_GET, "You reach for the talisman but your hand " +
      "passes right though it!\n");
  add_prop(OBJ_S_SEARCH_FUN, "search_it");
  add_name("elem_talis_tower");
  add_item(({"symbol", "symbols"}),  "There is a "+
      "flame, a raindrop, a rock and a cloud.\n" );

  create_ctower_object();
}

string
search_it(object player, string what)
{
  if (what != "talisman" && what != "for talisman")
  {
    return 0;
  }

  if (player->resolve_task(TASK_DIFFICULT, ({ TS_INT, SS_AWARENESS })) > 0)
  {
    get_it(player);
    return "";
  }

  return 0;  
}
 
int
feel(string arg)
{
  notify_fail("Feel what?\n");
  if (!strlen(arg))
  {
    return 0;
  }

  if (arg != "talisman" && arg != "for talisman")
  {
    return 0;
  }

  if (this_player()->resolve_task(TASK_ROUTINE + 100, ({ TS_INT, 
      SS_AWARENESS })) > 0)
  {
    get_it(this_player());
  }
  else
  {
    write("You don't feel anything.\n");
  }

  return 1;
}

void get_it(object who)
{
  who->catch_msg("You feel a talisman and quickly pick it up!\n");
  say(QCTNAME(who) + " grabs at empty space and gets something!\n");

  remove_prop(OBJ_M_NO_GET);
  move(who, 1);
}

void
init()
{
  ::init();

  add_action(feel, "feel");
}
