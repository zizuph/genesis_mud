/*
 * Shop in Goblin caves
 * Milan March 1994
 * modified from:
 *  Shop in Minas Morgul
 *  Olorin, July 1993
 *  copied from:
 *  Bendar's General Store in Edoras
 *  rewritten by Olorin                   may 1993
 *  - use /lib/shop  - copied from ranger guild shop
 *  modified by Olorin                   feb 1993
 *  after ideas by Hamurabbi
 *  after the Hobbiton drug store by
 *                               Tricky, dec 1991
 */


inherit "/d/Rhovanion/common/misty/gcaves/room";
inherit "/d/Genesis/lib/shop";

#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <cmdparse.h>
#include <composite.h>
#include <ss_types.h>
#include <filter_funs.h>
#include "/d/Rhovanion/defs.h"

#define CAVE_DIR MISTY_DIR + "gcaves/"
#define STORE_ROOM CAVE_DIR + "store"

object keeper;

void create_cave()
{
  config_default_trade();  /* Set up the trading system */
  set_money_give_max(1000);
  set_money_give_out(   ({ 10000,   700,  40,    1 }));
  set_money_give_reduce(({     0,     4,   3,    9 }));
  set_money_greed_sell("@@discriminate");
  set_money_greed_buy("@@discriminate");
  set_money_greed_change("@@discriminate");
  set_store_room(STORE_ROOM);

  set_noshow_obvious(1);

  set_short("Humid shop.\nThere is one obvious exit: east");
  set_long("You are at the end of the tunnel that burrow under the Misty "
    + "Mountains. It is very humid and the walls are damp with condensed "
    + "water.  You seriously hope that you are not lost because every "
    + "tunnel looks much the same as the last...\n"
    + "But this one is slightly different. One greedy goblin made a private "
    + "shop here. If he is here he you sell or buy all kind of things he "
    + "has or you offer to him. He has made a poster explaining which you "
    + "can read. Because he doesn't want to have stolen anything he keeps "
    + "all things in small storeroom west from here.\n"
    + "There is one obvious exit: east.\n");

  add_item("poster","Maybe you are literate enough to read it.\n");
  add_cmd_item("poster","read","@@read_poster");
  add_item("storeroom","You can see only closed door.\n");
  add_item("door","They are very massive and able to keep anyone away "+
                  "from the storeroom.\n");

  add_exit(STORE_ROOM, "west", "@@wiz_check");
  add_exit(CAVE_DIR+"t60", "east");
}

string read_poster()
{
  if(!CAN_SEE_IN_ROOM(TP)) return "It is too dark to see.\n";
  return "Use these instructions or be gone:\n"+
        "    buy sword for gold and get copper back\n" +
        "    buy sword for gold coins\n" +
        "    sell sword for copper coins\n" +
        "    sell all  - will let you sell all items except for\n" +
        "                items you wield or wear.\n" +
        "    sell all! - will let you sell ALL items you have, well\n" +
        "                at least the droppable, and no coins.\n" +
        "    sell sword, sell second sword, sell sword 2, sell two swords\n" +
        "                also works. You might want to change the verb to\n" +
        "                'value' or 'buy' too. \n" +
        "                I sell only one item at a time, though! \n" +
        "    If you want a list of all swords available in the store, the\n" +
        "    correct syntax is: list swords\n" +
        "                'list weapons', 'list armours' also works\n";
}

void init()
{
    ::init();
    init_shop();
    add_action("open_door", "open");
    add_action("unlock_door", "unlock");
}

int open_door(string arg)
{
  NF("It is too dark to see.\n");
  if(!CAN_SEE_IN_ROOM(TP)) return 0;
  NF("Open what?\n");
  if(!arg || (arg != "door")) return 0;
  say(QCTNAME(TP)+" tries desperately open the door but it "+
      "remains closed.\n");
  TP->catch_msg("You try desperately open the door but it remains closed.\n");
  if(keeper && present(keeper,TO))
  {
    keeper->command("knee "+TP->query_real_name());
    keeper->command("shout Don't mess with my storeroom!!!");
  }
  return 1;
}

int unlock_door(string arg)
{
  NF("It is too dark to see.\n");
  if(!CAN_SEE_IN_ROOM(TP)) return 0;
  NF("Unlock what?\n");
  if(!arg) return 0;
  if(explode(arg+" "," ")[0] != "door") return 0;
  say(QCTNAME(TP)+" tries unlock "+arg+" but it doesn't seem to work.\n");
  TP->catch_msg("You try to unlock "+arg+" but it doesn't seem to work.\n");
  if(keeper && present(keeper,TO))
  {
    keeper->command("tackle "+TP->query_real_name());
    keeper->command("shout I will really kill you!!!");
    keeper->command("kill "+TP->query_real_name());
  }
  return 1;
}

void reset_room()
{
  if(keeper && present(keeper,TO)) return;
  if(sizeof(FILTER_LIVE(all_inventory(TO))))
  {
    set_alarm(200.0, 0.0, "reset_room");
    return;
  }
  keeper = clone_object(NPC_DIR + "goblins/keeper.c");
  keeper->arm_me();
  keeper->move_living("xxx",TO);
}

int check_keeper(string arg)
{
  object enemy;
  string who;

  if (keeper && present(keeper,TO))
  {
    who = TP->query_nonmet_name();
    if(keeper->query_introduced(TP))
       who = TP->query_name();
    if(enemy = keeper->query_attack())
    {
      if(enemy == TP)
      {
        keeper->command("say Now you want to "+arg+" something? I will kill "+
                        "you now and take all your possesions for free!");
        keeper->command("ponder stupid "+who);
      }
      else
      {
        keeper->command("say Please "+who+"! You must wait untill I kill "+
                        "this coward "+enemy->query_nonmet_name()+"! "+
                        "Maybe you can help me too?");
        keeper->command("wink "+TP->query_name());
      }
      return 0;
    }
    else
      return 1;
  }
  else
  {
    TP->catch_msg("There is no shopkeeper here, so you can't do that!\n");
    return 0;
  }
}

int check_intro(string arg)
{
  if(keeper->query_introduced(TP)) return 1;
  keeper->command("say If you want "+arg+" something then you should at "+
                  "least introduce yourself!");
  keeper->command("say Yes you bastard! I mean you "+TP->query_nonmet_name()+"!");
  return 0;
}

int check_light()
{
  if(CAN_SEE_IN_ROOM(keeper)) return 1;
  keeper->command("say I am sorry "+TP->query_name()+" but I can't work "+
                  "when I can't see and all my torches are gone...");
  keeper->command("sigh");
  return 0;
}

int do_buy(string args)
{
  if(!check_keeper("buy")) return 1;
  if(!check_intro("buy")) return 1;
  if(!check_light()) return 1;

  if (!args || args =="")
  {
    NF("Buy what?\n");
    return 0;
  }
  TP->catch_msg("You ask "+QTNAME(keeper)+" to sell you "+args+".\n");
  say(QCTNAME(TP)+" asks "+QTNAME(keeper)+" to sell "+
      TP->query_objective()+" "+args+".\n");

  call_other(STORE_ROOM, "load_me");
  if(!present("_bed_cover_for_goblin_hotel_",find_object(STORE_ROOM)))
    clone_object(OBJ_DIR+"bed_cover")->move(STORE_ROOM);

  return ::do_buy(args);
}

int do_value(string args)
{
  if(!check_keeper("value")) return 1;
  if(!check_intro("value")) return 1;
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
    keeper->command("say I can't value everything! It is too much even for me.");
    return 0;
  }
  TP->catch_msg("You ask "+QTNAME(keeper)+" about the value of the "+
      args+".\n");
  say(QCTNAME(TP)+" asks "+QTNAME(keeper)+" about the value of the "+
      args+".\n");

  return ::do_value(args);
}

int do_sell(string args)
{
  if(!check_keeper("sell")) return 1;
  if(!check_intro("sell")) return 1;
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

int do_list(string str)
{
    object *item_arr;
    int i, price, *arr;

    if(!check_keeper("list")) return 1;
    if(!check_intro("list")) return 1;
    if(!check_light()) return 1;

    if (str && (str != "all") && (str != "all!"))
    {
      TP->catch_msg("You ask "+QTNAME(keeper)+" about available "+str+".\n");
      say(QCTNAME(TP)+" asks "+QTNAME(keeper)+" about available "+str+".\n");
    }
    else
    {
      TP->catch_msg("You ask "+QTNAME(keeper)+" what is available for sell.\n");
      say(QCTNAME(TP)+" asks "+QTNAME(keeper)+" what is available for sell.\n");
    }

    call_other(STORE_ROOM, "load_me");
    if(!present("_bed_cover_for_goblin_hotel_",find_object(STORE_ROOM)))
      clone_object(OBJ_DIR+"bed_cover")->move(STORE_ROOM);

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
    keeper->command("say I have "+COMPOSITE_DEAD(item_arr)+" in the stock "+
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
    NF("@@message_sell_worn_or_wielded:"+file_name(TO)+"|"+ob->short()+"@@");
}
string
message_sell_worn_or_wielded(string what)
{
  keeper->command("say "+TP->query_name()+", you should remove the "+what+
                       " first!");
  return "";
}

void
shop_hook_sell_no_value(object ob)
{
  NF("@@message_sell_no_value:"+file_name(TO)+"|"+ob->short()+"@@");
}
string
message_sell_no_value(string what)
{
  keeper->command("say The "+what+" is worthless to me, "+TP->query_name()+".");
  return "";
}

int
shop_hook_sell_no_match(string *str)
{
  NF("");
  keeper->command("say "+TP->query_name()+", you don't have any "+str+".");
  return 0;
}

void
shop_hook_sell_object_stuck(object ob, int err)
{
  NF("");
  keeper->command("say It seems you are stuck with "+ob->short()+",  "+
                  TP->query_name()+".");
}

void
shop_hook_sell_no_sell(object ob, string str)
{
  if (stringp(str)){ NF(str); return; }
  NF("@@message_sell_no_sell:"+file_name(TO)+"|"+ob->short()+"@@");
}
string
message_sell_no_sell(string what)
{
  keeper->command("say I don't buy "+what+", "+TP->query_name()+".");
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
  keeper->command("say You don't have anything to sell "+TP->query_name()+".");
  return 0;
}

/** buy *********************************************************/
void
shop_hook_buy_cant_pay(object ob, int *arr)
{
  NF("");
  keeper->command("say You must have money first "+TP->query_name()+
                  " and only then you can buy "+ob->short()+".");
}

void
shop_hook_buy_no_buy(object ob, string str)
{
  NF("");
  keeper->command("say I am sorry "+TP->query_name()+". "+
                  CAP(LANG_THESHORT(ob))+" isn't for sale.\n");
}

void
shop_hook_buy_no_match(string str)
{
  NF("");
  keeper->command("say "+TP->query_name()+", I have no "+str+" to sell.");
}

void
shop_hook_buy_cant_carry(object ob, int err)
{
  NF("");
  tell_room(TO,QCTNAME(keeper)+" drops the "+ob->short()+" on the floor.\n");
  keeper->command("say You can't carry it "+TP->query_name()+".\n");
  keeper->command("comfort "+TP->query_name());
}

void
shop_hook_buy_magic_money(object ob)
{
  NF("");
  keeper->command("say You are carrying magic money "+QCNAME(TP)+
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
  keeper->command("say The "+ob->short()+" doesn't interest me, "+
                  TP->query_name()+".\n");
}

void
shop_hook_value_held(object ob, string text)
{
  keeper->command("say I could offer you "+text+" for that "+ob->short()+
                  ", "+TP->query_name()+".");
}

void
shop_hook_value_store(object ob, string text)
{
  keeper->command("say I can sell you "+ob->short()+" for "+text+", "+
                  TP->query_name()+".");
}

void
shop_hook_value_asking(string str)
{ return; }

int
shop_hook_value_no_match(string str)
{
  NF("");
  keeper->command("say How can I value '"+str+"' when neither you nor me "+
                  "have it?");
  keeper->command("peer at "+TP->query_name());
  return 0;
}

/** list *********************************************************/
void
shop_hook_list_empty_store(string str)
{
  NF("");
  keeper->command("say I have nothing to sell at the moment.\n");
}

int
shop_hook_list_no_match(string str)
{
  NF("");
  keeper->command("say We have no "+str+" in stock, "+TP->query_name()+".\n");
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
  seteuid(geteuid(TO));
  if (TP->query_wiz_level())
    return 0;

  TP->catch_msg("You try to go to storeroom but bump into closed door.\n");
  say(TP->query_name()+" tries to go to storeroom but bumps into closed door.\n");
  if(keeper && present(keeper,TO))
  {
    keeper->command("grin at "+TP->query_real_name());
    keeper->command("shout Only over my dead body!!!");
  }
  return 1;
}

/*
 * Function name:   discriminate
 * Description:     Don't treat all players equal by giving different prices.
 * Returns:         A percentage.   100   pay normal price.
 *                                 >100   annoy player
 *                                 <100   help player
 */
int
discriminate() {
   int bargain;

   bargain = TP->query_skill(SS_TRADING);
   if(bargain > 30) bargain = 30;
   bargain = 115 - bargain;

   if(TP->query_race_name() == "goblin")
     return ((bargain * 85) / 100);

   return ((bargain * 120) / 100);
}
