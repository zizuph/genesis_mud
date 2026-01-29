
/* 
     This room is a hardware store, called the Shark's Tooth Shack.   
     It goes in the west coast fishing village of Calia. 

     Coded by Maniac & Jaacar
 */

#pragma save_binary

inherit "/std/room";
inherit "/lib/shop"; 

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

#define STORE_ROOM    BEACH+"hardware_store"


object keeper;

void
reset_room()
{
    if (!objectp(keeper)) { 
        keeper = clone_object(SEA_CREATURES+"syr_lin"); 
        keeper->move_living("into the hardware store", this_object()); 
    } 
}


void
create_room()
{
    config_default_trade();
    set_short("The Shark's Tooth Shack");
    set_long("This place is the Shark's Tooth Shack, the village " +
        "hardware store. It is indeed a shack if ever you saw one, " +
        "old and rickety and with the minimum of decor. But heaven " +
        "knows what connection this place has with a shark's tooth, " +
        "as the only sharp and dangerous thing in here " +
        "is the proprietor when she is in " +
        "a bad mood. Long dusty shelves are stacked with items for " +
        "travellers and adventurers. The south exit leads to " +
        "the village main street.\n");    

    add_item(({"here", "hut", "shack", "store"}), 
              "You're standing in it.\n"); 

    add_item(({"shelf", "shelves"}), 
      "They are long and dusty, and contain a number of items. " + 
      "Try typing `list' to see what is currently available.\n"); 

    add_item("decor", "There isn't any, really. Just bare walls with " +
            "long shelves.\n"); 
  
    add_item("walls", "They are bare and have long shelves running " + 
                      "along them.\n"); 

    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_INSIDE, 1);

    set_store_room(STORE_ROOM);

    add_exit(BEACH+"village6","south", 0, 0);
  
    reset_room(); 
}


void
init()
{
    ::init();
    init_shop();
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
      tp->catch_msg("Syr-Lin isn't here, so you can't do that!\n");
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
    if (ob->id("_calia_hardware_shop_")) 
        return 1;

    notify_fail("I'll only buy hardware of Calia.\n");
    return 0;
}

