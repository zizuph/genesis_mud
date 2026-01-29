/* ctower/obj/wand.c is cloned by ctower/maze23.c  */
inherit "/std/object";
inherit "/d/Emerald/ctower/obj/ctower_obj_base";

#include "/d/Emerald/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <tasks.h>

void get_it(object who);
 
void
reset_object()
{
    reset_ctower_object();
}

void
create_object()
{
  set_name("wand");
  add_name("phase_quest_wand");
  set_long( "This is a clear crystal wand that is about "+
      "2 cm thick and 12 cm long and cylindrical in shape.\n" );
  set_short("crystal wand");
  add_adj("crystal");
  add_adj("for");              // cheap way to allow 'search for wand'
  add_prop(OBJ_I_WEIGHT, 100);
  add_prop(OBJ_I_VOLUME, 20);
  add_prop(OBJ_I_VALUE, 108);
  add_prop(OBJ_M_NO_GET, "You reach for the wand, but your hand passes " +
      "right through it!\n");
  add_prop(OBJ_S_SEARCH_FUN, "search_it");

  create_ctower_object();
}
 
string
search_it(object player, string what)
{
  find_player("shiva")->catch_msg(what + "\n");
  if (what != "wand" && what != "crystal wand" && 
      what != "for wand" && what != "for crystal wand")
  {
    return 0;
  }

  if (player->resolve_task(TASK_DIFFICULT, ({ TS_INT, SS_AWARENESS })) > 0)
  {
    get_it(player);
    return "\n";
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

  if (arg != "wand" && arg != "crystal wand" && 
      arg != "for wand" && arg != "for crystal wand")
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
  who->catch_msg("You feel a wand and quickly pick it up!\n");
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
