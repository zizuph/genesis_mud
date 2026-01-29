
/*
 *    A cave by the Calian sea
 *    coded by Amelia and Digit and Jaacar (busy room eh?)... 7/1995
 * 
 *    This room converted into a shop for any players to sell in 
 *    by Maniac, plus some other revisions, 28/8/96
 */

#pragma save_binary

inherit "/std/room";
inherit "/lib/shop"; 

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

#define STORE_ROOM (BEACH+"sea_cave_store")  

object keeper;

void
reset_room()
{
    if (!objectp(keeper))  {
        keeper = clone_object(SEA_CREATURES+"ripper");
        keeper->move_living("into the sea cave", this_object()); 
    } 
}


void
create_room()
{
    config_default_trade(); 
    set_short("A watery cave");
    set_long("This is a huge, watery cave "+
      "carved into the rock by the sea. Just a little "+
      "light filters in from the crack above. As you "+
      "focus on your surroundings, you see dark shapes. "+
      "You are up to your knees in brackish sea water, "+
      "and the floor seems slimy and slippery. There is " +
      "a peculiar odor...\n");

    add_prop(ROOM_I_IS, 1);
    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

    set_store_room(STORE_ROOM); 

    add_item((({"shapes", "dark shapes", "surroundings"})),
        "It's difficult to make out what the shapes are. "+
        "They are more like shadows, possibly just rocks.\n");

    add_item((({"water", "sea water", "brackish sea water"})),
        "The sea water here is brackish and smells bad. "+
        "There seems to be some slimy substance floating in it.\n");

    add_item((({"rocks", "walls", "ceiling"})),
        "The cave is eroded out of solid rock. "+
        "There are large rocks or shapes all around ... \n");

    add_item("crack","The crack looks large enough, and low "+
        "enough for you to crawl out through.\n");

    reset_room();
}


int
climb_out(string str)
{
    notify_fail("Crawl where?\n");

    if (str=="out" || str=="up" || str=="out crack"|| 
        str == "crack") {
        this_player()->move_living("through the crack", BEACH+"beach1", 0);
        return 1;
    }
    return 0;
}


void
init()
{
    ::init();
    init_shop(); 
    add_action(climb_out, "climb");
    add_action(climb_out, "crawl");
}

int
check_keeper(string arg)
{
  object enemy, tp;
  string who;

  tp = this_player();

  if (keeper && present(keeper,this_object()))
  {
     who = tp->query_nonmet_name();
    if (enemy = keeper->query_attack())
    {
      if(enemy == tp)
      {
        keeper->command("say You want to "+arg+" something and kill " +
                        "me too, " + who + "?!");
      }
      else
      {
        keeper->command("say You want to "+arg+" something while someone's "+
                        "trying to kill me, " + who + "?!");
      }
      return 0;
    }
    else
      return 1;
  }
  else {
      tp->catch_msg("Ripper isn't here, so you can't do that!\n");
      return 0;
  }
}

int
check_light()
{
  if (CAN_SEE_IN_ROOM(keeper)) return 1;
  keeper->command("say Sorry but I can't see anything!");
  return 0;
}


int
do_buy(string args)
{
  if(!check_keeper("buy")) return 1;
  if(!check_light()) return 1;

  return ::do_buy(args);
}


int
do_list(string str)
{
    object tp = this_player();

    if(!check_keeper("list")) return 1;
    if(!check_light()) return 1;

    return ::do_list(str);
}


int
do_value(string args)
{
  object tp = this_player();

  if(!check_keeper("value")) return 1;
  if(!check_light()) return 1;

  return ::do_value(args);
}


int
do_sell(string args)
{
  object tp = this_player();

  if(!check_keeper("sell")) return 1;
  if(!check_light()) return 1;

  return ::do_sell(args);
}

int
shop_hook_allow_sell(object ob)
{
    if (ob->query_prop(FISH_I_FROM_THALASSIAN_SEA)) { 
        notify_fail("I don't buy that fish meat, try the market.\n"); 
        return 0;
    } 
    return ::shop_hook_allow_sell(ob);
}

