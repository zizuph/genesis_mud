/*   This is a the general shop in Gelan, Calia.
     Much of it is based on a shop of Milan's in Rhovanion.

    coder(s):  Maniac

    history:
              2010/09/02 Typos                             Lavellan
              2010/08/24 Last update
              28/4/98 bug fixes                            Maniac
              5/6/97 Won't serve town enemies              Maniac
              7/94                     Created             Maniac

*/

#pragma save_binary

#include "defs.h"
#include <stdproperties.h>
#include <cmdparse.h>
#include <composite.h>
#include <macros.h>
#include "room.h"
#include GUARD_INCLUDE

inherit GELAN_BASE_ROOM;
inherit "/lib/shop";

#define STORE_ROOM (GELAN_ROOMS + "shopback")
#define CAP(x) capitalize(x)
#define INSULT "Garn, go 'n get yerself a life!"
#define PLEA "'elp me for Gord sakes!"


object keeper;


reset_room()
{
  if (!keeper) fix_keeper();
}


/*
 * Function name:   create_gelan_room
 * Description:     Initialize this room
 * Returns:
 */
public void
create_gelan_room()
{
    config_default_trade();
    set_short("The shop of Gelan");
    set_long(
      "The shop has a pompous appearance; no effort was spared to make it "
     +"a heaven for wealthy consumers. The walls are made of Elfish "
     +"sandstone, the large windows made of cherrywood with crystalline "
     +"panes. The roof is an elegant white structure made of seashells. "
     +"Just inside of the arched, white entrance is a fine, red, silk carpet "
     +"woven with a million knots per meter. The sandstone walls are lined "
     +"with hundreds of shelves covered with nearly every item imaginable. "
     +"There is a little sign to read with instructions.\n");

    add_item(({"wall", "walls"}), "The walls are made of smooth, high " +
               "quality sandstone and covered with long display shelves.\n");

    add_item(({"shelf", "shelves"}), "On the long shelves are displayed " +
              "Coiney's acquisitions over the years. Some are for sale, " +
              "but many he has taken a particular liking to and decided " +
              "to use for ornamental purposes, making his store look all " +
              "the richer.\n");

    add_item(({"carpet", "red carpet", "silk carpet", "fine carpet"}),
               "Obviously with a carpet like this Coiney has either " +
               "decided that he himself is royalty, or that his " +
               "customers are.\n");

    add_item(({"roof"}), "It's made of seashells, an unusual material to " +
              "build with, but it is a strikingly elegant and " +
              "original construction.\n");

    add_item(({"window", "windows"}), "They have cherrywood frames and " +
               "crystalline panes. Crystalline materials are of course " +
               "popular in all of Calia.\n");

    add_item(({"entrance"}), "It is a semicircular white archway.\n");


    add_exit(GELAN_ROOMS + "square_westend_n", "east", 0);
    add_exit(STORE_ROOM, "up", "@@wiz_check");

    add_prop(ROOM_I_INSIDE, 1);  /* This is a real room */

    set_store_room(STORE_ROOM);
    call_other(STORE_ROOM, "load_me");

    seteuid(getuid());
    set_alarm(1.0, 0.0, "reset_room");
}



fix_keeper()
{
  keeper = clone_object(GELAN_MONSTERS + "coiney");
  keeper->move_living("into the shop", this_object());
}


void
init()
{
    ::init();   /* You MUST do this in a room-init */
    init_shop();
}



#define MONEY_TYPE ({ "cc", "sc", "gc", "pc" })



int
check_keeper(string arg)
{
  object enemy;
  string who;

  if (keeper && present(keeper,this_object()))
  {
    if (TP->query_prop(ATTACKED_GELAN)) {
        keeper->command("say to " + TP->query_real_name() +
                        " I ain't gonna serve an enemy of the town!");
        return 0;
    }
    who = TP->query_nonmet_name();
    if(enemy = keeper->query_attack())
    {
      if(enemy == TP)
      {
        keeper->command("say You wants to "+arg+" something 'n beat me "+
                        "up too, " + who + "?! " + INSULT);
      }
      else
      {
        keeper->command("say You wants to "+arg+" something while I'm "+
                        "gettin' beaten up, " + who + "?! " + PLEA);
      }
      return 0;
    }
    else
      return 1;
  }
  else
  {
    TP->catch_msg("Coiney Miser isn't here, so you can't do that!\n");
    return 0;
  }
}


int
check_light()
{
  if(CAN_SEE_IN_ROOM(keeper)) return 1;
  keeper->command("say Sorry deary, I can't see nothin'...");
  keeper->command("cough");
  return 0;
}

int
do_buy(string args)
{
  if(!check_keeper("buy")) return 1;
  if(!check_light()) return 1;

  if (!args || args =="")
  {
    NF("Buy what?\n");
    return 0;
  }
  TP->catch_msg("You ask "+QTNAME(keeper)+" to sell you "+args+".\n");
  say(QCTNAME(TP)+" asks "+QTNAME(keeper)+" to sell "+
      TP->query_objective()+" "+args+".\n");

  return ::do_buy(args);
}


int
do_value(string args)
{
  if(!check_keeper("value")) return 1;
  if(!check_light()) return 1;

  if (!args || args == "")
  {
    notify_fail("Value what?\n");
    return 0;
  }
  if (args == "all" || args == "all!")
  {
    NF("");
    TP->catch_msg("You ask "+QTNAME(keeper)+" about the values of everything.\n");
    say(QCTNAME(TP)+" asks "+QTNAME(keeper)+" about the values of everything.\n");
    keeper->command("say I can't value everythin', deary!");
    return 0;
  }

  TP->catch_msg("You ask "+QTNAME(keeper)+" about the value of the "+
      args+".\n");
  say(QCTNAME(TP)+" asks "+QTNAME(keeper)+" about the value of the "+
      args+".\n");

  return ::do_value(args);
}


int
do_sell(string args)
{
  if(!check_keeper("sell")) return 1;
  if(!check_light()) return 1;

  if (!args || args == "")
  {
    notify_fail("Sell what?\n");
    return 0;
  }
  if((args != "all") && (args != "all!"))
  {
    TP->catch_msg("You offer "+args+" to "+QTNAME(keeper)+".\n");
    say(QCTNAME(TP)+" offers "+args+" to "+QTNAME(keeper)+".\n");
  }
  else
  {
    TP->catch_msg("You offer all your possessions to "+QTNAME(keeper)+".\n");
    say(QCTNAME(TP)+" offers all "+TP->query_possessive()+" possessions to "+
        QTNAME(keeper)+".\n");
  }
  return ::do_sell(args);
}

int
do_list(string str)
{
    object *item_arr;
    int i, price, *arr;

    if(!check_keeper("list")) return 1;
    if(!check_light()) return 1;

    if (str && (str != "all") && (str != "all!"))
    {
      TP->catch_msg("You ask "+QTNAME(keeper)+" about available "+str+".\n");
      say(QCTNAME(TP)+" asks "+QTNAME(keeper)+" about available "+str+".\n");
    }
    else
    {
      TP->catch_msg("You ask "+QTNAME(keeper)+" what is for sale.\n");
      say(QCTNAME(TP)+" asks "+QTNAME(keeper)+" what is for sale.\n");
    }

    call_other(STORE_ROOM, "load_me");
    item_arr = all_inventory(find_object(STORE_ROOM));

    if (!sizeof(item_arr))
    {
	shop_hook_list_empty_store(str);
	return 0;
    }

    if (str == "weapons")
        item_arr = filter(item_arr, "weapon_filter", this_object());
    else if (str == "armours")
            item_arr = filter(item_arr, "armour_filter", this_object());
    else if (str)
	item_arr = FIND_STR_IN_ARR(str, item_arr);

    if (sizeof(item_arr) < 1)
	return shop_hook_list_no_match(str);

    keeper->command("hmm");
    keeper->command("say I's got "+COMPOSITE_DEAD(item_arr)+" in stock "+
                    "at the moment.");

    return 1;
}



/** sell ********************************************************/

void
shop_hook_sell_get_money(string str)
{
  TP->catch_msg(QCTNAME(keeper)+" gives you "+str+".\n");
  say(QCTNAME(keeper)+" gives "+str+" to "+QTNAME(TP)+".\n");
}



void
shop_hook_sell_worn_or_wielded(object ob)
{
    NF("@@message_sell_worn_or_wielded:" + file_name(this_object())
       +  "@@");
}




string
message_sell_worn_or_wielded()
{
  keeper->command("say "+TP->query_nonmet_name()+", you's specified to sell "+
                  "worn or wielded objects, deary.");
  return "";
}



void
shop_hook_sell_no_value(object ob)
{
  NF("@@message_sell_no_value:"+file_name(this_object())+"|"
                                                  +ob->short()+"@@");
}



string
message_sell_no_value(string what)
{
  keeper->command("say The "+what+" is worth nothin', "
                             +TP->query_nonmet_name()+".");
  return "";
}

int
shop_hook_sell_no_match(string str)
{
    NF("");
    keeper->command("say "+ TP->query_nonmet_name() + ", you don't have any "+str+".");
    return 0;
}

void
shop_hook_sell_object_stuck(object ob, int err)
{
  NF("");
  keeper->command("say You's stuck with "+LANG_THESHORT(ob)+", "+
                  TP->query_nonmet_name()+".");
}

void
shop_hook_sell_no_sell(object ob, string str)
{
  if (stringp(str)){ NF(str); return; }
  NF("@@message_sell_no_sell:"+file_name(this_object())+"|"
                              +ob->short()+"@@");
}


string
message_sell_no_sell(string what)
{
  keeper->command("say I don't wanna buy the "+what+", "+
                                   TP->query_nonmet_name()+".");
  return "";
}


/** sold ********************************************************/
int
shop_hook_sold_items(object *item)
{
  tell_room(TO,QCTNAME(keeper)+" puts "+COMPOSITE_DEAD(item)+
               " into the storeroom.\n");
  return 1;
}

int
shop_hook_sold_nothing()
{
  NF("");
  keeper->command("say You's got nothin' to sell, "+TP->query_nonmet_name()+".");
  return 0;
}

/** buy *********************************************************/
void
shop_hook_buy_cant_pay(object ob, int *arr)
{
  NF("");
  keeper->command("say You's gotta have the money first, "
                  +TP->query_nonmet_name()+
                  ", if ya want to buy "+LANG_THESHORT(ob)+".");
}

void
shop_hook_buy_no_buy(object ob, string str)
{
  NF("");
  keeper->command("say Sorry "+TP->query_nonmet_name()+". "+
                  CAP(LANG_THESHORT(ob))+" isn't for sale.\n");
}

void
shop_hook_buy_no_match(string str)
{
  NF("");
  keeper->command("say "+TP->query_nonmet_name()+", I's got no "+str+
                                                      " to sell.");
}

void
shop_hook_buy_cant_carry(object ob, int err)
{
  NF("");
  keeper->command("say You can't carry it "+TP->query_nonmet_name()+".\n");
  keeper->command("snicker");
}


void
shop_hook_buy_magic_money(object ob)
{
  NF("");
  keeper->command("say You's carryin' magic money, "+QCNAME(TP)+
                  ", no deal!");
}

void
shop_hook_buy_pay_money(string str, string change)
{
  TP->catch_msg("You give "+str+" to "+QTNAME(keeper)+".\n");
  say(QCTNAME(TP)+" gives "+str+" to "+QTNAME(keeper)+".\n");
  if (change)
  {
    TP->catch_msg("He gives you "+change+" back.\n");
    say(QCTNAME(keeper)+" gives "+change+" to "+QTNAME(TP)+".\n");
  }
}


/** bought ******************************************************/
int
shop_hook_bought_items(object *arr)
{
    TP->catch_msg(QCTNAME(keeper)+" gets "+COMPOSITE_DEAD(arr)+
               " from the storeroom and gives it to you.\n");
    say(QCTNAME(keeper)+" gets "+QCOMPDEAD+
               " from the storeroom and gives it to "+QTNAME(TP)+".\n");
    return 1;
}

/** value ********************************************************/
void
shop_hook_value_not_interesting(object ob)
{
  NF("");
  keeper->command("say "+CAP(LANG_THESHORT(ob))+" doesn't interest me, "+
                  TP->query_nonmet_name()+".\n");
}

void
shop_hook_value_held(object ob, string text)
{
  keeper->command("say I could offer you "+text+" for that "+ob->short()+
                  ", "+TP->query_nonmet_name()+".");
}

void
shop_hook_value_store(object ob, string text)
{
  keeper->command("say I can sell you "+LANG_THESHORT(ob)+" for "+text+", "+
                  TP->query_nonmet_name()+".");
}

void
shop_hook_value_asking(string str)
{ return; }

int
shop_hook_value_no_match(string str)
{
  NF("");
  keeper->command("say I can't value '"+str+"' as neither you or me's "+
                  "got it!");
  keeper->command("peer at "+TP->query_name());
  return 0;
}


/** list *********************************************************/
void
shop_hook_list_empty_store(string str)
{
  NF("");
  keeper->command("say I's got nothin' to sell at the moment.\n");
}

int
shop_hook_list_no_match(string str)
{
  NF("");
  keeper->command("say We's got no "+str+" in stock, "+
                            TP->query_nonmet_name()+".\n");
  return 0;
}



/*
 * Function name:   wiz_check
 * Description:     Check if a player is a wizard
 * Returns:         0 if the player is a wizard
 *                  1 otherwise
 */
wiz_check()
{
  seteuid(geteuid(this_object()));
  if (TP->query_wiz_level()) return 0;

  TP->catch_msg("You try to enter the storeroom but are stopped by a strange "
                +"and powerful magical force.\n");
  tell_room(TO, QCTNAME(TP)+" tries to enter the storeroom but is stopped "
                +"by a strange and powerful magical force.\n", ({TP}));

  if(keeper && present(keeper,TO))
  {
    keeper->command("grin at "+TP->query_real_name());
    keeper->command("snicker");
  }
  return 1;
}
