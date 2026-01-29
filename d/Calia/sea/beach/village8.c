
 /*
        This is the fish market. 
        Here they pay special prices for the fish caught 
        (or stolen from boats) from the local waters, 
        for export all over Calia. 

        coder(s):    Jaacar & Maniac 12/9/96

        Net always available from here, Maniac, 23/9/96
        Added net info to desc, Maniac, 27/4/97
 */

#pragma save_binary

inherit "/d/Calia/std/room_tell_room";
inherit "/d/Genesis/lib/shop";

#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include "defs.h"

#define STORE_ROOM    BEACH+"village_storeroom"
#define NET_PRICE 20

object keeper;

void
reset_room()
{
    if (!objectp(keeper)) { 
         keeper = clone_object(SEA_CREATURES+"mar_iella"); 
         keeper->arm_me(); 
         keeper->move_living("into the shop", this_object()); 
    }
}

void
create_room()
{
    config_default_trade();
    set_short("The fish market");
    set_long("The local fish market is busy as usual. " +
             "It is a centre for coastal sea food trade despite its " +
             "humble location, keeping the majority of the locals " +
             "in secure employment for all of their working lives. " +
             "Good prices are paid here for any local catches and " +
             "useful nets are available here for little cost. " + 
             "The inner walls of the hut are mounted with " +
             "wood carvings and impressive trophies of sea creatures. " +
             "Tables stacked with all kinds of fish " +
             "take up most of the space, with a central area for " +
             "customers and a bartering stall to the south where the " +
             "shopkeeper sits. In one corner is a huge bucket for " +
             "fish guts and other waste.\n"); 

    add_item(({"bucket", "huge bucket"}), "You peer inside.. Yeuch!!\n"); 

    add_item(({"hut", "market", "fish market"}), "You're in the " +
              "fish market!\n"); 

    add_item("floor", "The wooden floor is kept quite clean to stop " +
         "people slipping on fish guts and hurting themselves.\n"); 

    add_item(({"stall", "bartering stall"}), 
             "It's a large wooden table where one can slap a decent day's " +
             "catch and haggle with the owner for an acceptable price.\n"); 

    add_item(({"trophies", "trophy"}), 
             "One of the trophies is a large stuffed swordfish. It's nose " +
             "might have made a good two-hander judging by its length. " +
             "The masterpiece though is a three foot wide shark's jaw " +
             "bone with dagger-like teeth. You find yourself hoping that " +
             "this one didn't have any kids.\n"); 

    add_item(({"wall", "walls"}), "The walls are mounted with " +
             "wood carvings and trophies.\n"); 

    add_item(({"table", "tables"}), 
             "The tables in here are stacked with everything from " +
             "sardines to octopi (in separate piles, naturally). " +
             "Every so often a trader will arrive with a large " +
             "brine-filled barrel and buy some. If you kill " +
             "sea creatures out there, you may well find you " +
             "can cut off their meats and sell them here.\n");  

    add_item(({"carvings", "wood carvings", "carving", "wood carving"}), 
            "The carvings are made on a dark varnished wood " +
            "and depict variations on a common theme: nasty " +
            "tentacled things rearing up out of the sea and attacking " +
            "fisherman in boats half their size. They could be tall " +
            "stories or superstitions though.\n"); 

    add_item("central area", "Use your imagination, it's a central clear " +
             "area. You can't walk on a ceiling you know.\n"); 

    add_item("sign", "There is a sign here that you can read.\n");

    add_prop(ROOM_I_LIGHT,1);
    add_prop(ROOM_I_INSIDE,1);

    set_store_room(STORE_ROOM);

    add_exit(BEACH+"village5","north",0,0);
    add_exit(BEACH+"village7","west",0,0);

    reset_room(); 
}

void
init()
{
    ::init();
    init_shop();
}


/* This shop only buys fish meats from the thalassian sea. */
int
shop_hook_allow_sell(object ob)
{
    if (ob->query_prop(FISH_I_FROM_THALASSIAN_SEA))
        return 1;
    notify_fail("We don't buy anything but fish meat from the sea " +
                "of west Calia!\n");
    return 0;
}


/* This shop gives special rates to fish meat cut from the corpses
   of sea creatures killed in the local sea */
int
query_sell_price(object ob)
{
    int value;
    
    value = ::query_sell_price(ob);
    if (ob->query_prop(FISH_I_FROM_THALASSIAN_SEA))
        return (5*value);
    return value;
}


/* This guy is a ripoff merchant when it comes to fish :) 
   Price has to be equal or higher for fish anyway as otherwise 
   players can make profits by repeated buy/sell.
   He may sell fishing equipment at a later date.  
*/
int
query_buy_price(object ob)
{
    int value;
    value= ::query_buy_price(ob);
    if (ob->query_prop(FISH_I_FROM_THALASSIAN_SEA))
        return (10*value);
    return value;
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
                        "trying to kil me, " + who + "?!");
      }
      return 0;
    }
    else
      return 1;
  }
  else
  {
    tp->catch_msg("Mar-Iella isn't here, so you can't do that!\n");
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
  object net, tp;

  if(!check_keeper("buy")) return 1;
  if(!check_light()) return 1;

  if ((args == "net") || (args == "fishing net")) { 
      tp = this_player(); 
      if (!MONEY_ADD(tp, -NET_PRICE)) { 
          notify_fail("You do not have the necessary money!\n"); 
          return 0;
      } 
      net = clone_object(SEA_OBJECTS+"fish_net"); 
      if (net->move(tp)) {  
          net->move(this_object()); 
          tp->catch_msg("You could not carry it, so it is on the floor.\n"); 
          return 1;
      } 
      tp->catch_msg("You buy a fishing net.\n"); 
      tell_room(environment(tp), QCTNAME(tp) + " buys a fishing net.\n", tp); 
      return 1;
  } 
  return ::do_buy(args);
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
do_list(string str)
{
    object tp = this_player(); 

    if(!check_keeper("list")) return 1;
    if(!check_light()) return 1;

    write("Nets are always available here for " + NET_PRICE + " cc.\n"); 
    return ::do_list(str); 
}

