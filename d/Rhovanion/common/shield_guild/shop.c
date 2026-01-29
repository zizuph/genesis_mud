/*
 * Shop in Angmar's army guild
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


#pragma save_binary

inherit "/d/Rhovanion/lib/room";
inherit "/d/Genesis/lib/shop";

#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <cmdparse.h>
#include <composite.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
#include "/d/Rhovanion/defs.h"
#include "guild.h"

/*
 * This shop has 3 storerooms ;)
 */
#define STORE_ROOM_SC THIS_DIR + "store_sc"
#define STORE_ROOM_H  THIS_DIR + "store_h"
#define STORE_ROOM_R  THIS_DIR + "store_r"

#define KEEPER     THIS_DIR + "shop_keeper"

/*
 * Prototypes
 */
void reset_room();

object keeper;
int everything_ok = 1;

/*
 * Function name:   create_room
 * Description:     Initialize this room
 * Returns:
 */
void
create_room()
{
  reset_room();

  add_prop(ROOM_I_INSIDE,1); 

  config_default_trade();  /* Set up the trading system */
  set_money_give_max(1000); 
  set_money_give_out(   ({ 10000,   700,  40,    1 }));
  set_money_give_reduce(({     0,     4,   3,    9 }));
  set_money_greed_sell("@@discriminate");
  set_money_greed_buy("@@discriminate");
  set_money_greed_change("@@discriminate");
  set_store_room(STORE_ROOM_SC);

  set_noshow_obvious(1);

  set_short("Army shop.\nThere is one obvious exit: west");
  set_long("This is the place where Angmar's warriors sell everything "+
      "they have stolen from the unfortunate travelers or the villagers "+
      "they killed in "+
      "their last ride. They usually immediately spend all the money "+
      "in the pub. The storeroom is behind a massive door to the "+
      "east. There is also a poster with the instructions here.\n");

  add_item("poster","Maybe you are literate enough to read it.\n");
  add_cmd_item("poster","read","@@read_poster"); 
  add_item("storeroom","You can see only closed door.\n");
  add_item("door","They are very massive and able to keep anyone away "+
                  "from the storeroom.\n");

  add_exit(STORE_ROOM_SC, "east", "@@wiz_check");
  add_exit(THIS_DIR+"c1", "west");
}

string
read_poster()
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

void
init()
{
    ::init();
    init_shop();
    add_action("open_door", "open");
    add_action("unlock_door", "unlock");
}

int
open_door(string arg)
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

int
unlock_door(string arg)
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

void
reset_room()
{
  if(keeper)
  {
    if(present(keeper,TO)) return;

    keeper->command("oops");
    keeper->command("say I must not leave the shop!");
    keeper->command("ponder all thieves around");
    tell_room(ENV(keeper), QCTNAME(keeper)+" runs back to "+HIS(keeper)+
                           " shop.\n");
    keeper->move_living("M", TO);
    tell_room(TO, QCTNAME(keeper)+" arrives running.\n");
    keeper->command("say Back again.");
    keeper->command("say Return all you took without paying!");
    keeper->command("emote quickly checks all inventory.");
    keeper->command("sigh relieved");
    return;
  }
  
  keeper = clone_object(KEEPER);
  keeper->arm_me();
  keeper->move_living("M",TO);
  keeper->command("say Back in business.");
  keeper->command("say Return all you took without paying!");
  keeper->command("emote quickly checks all inventory.");
  keeper->command("sigh relieved");
} 

int
check_keeper(string arg)
{
  object enemy;
  string who;

  if (keeper && present(keeper,TO))
  {
    who = TP->query_nonmet_name();
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
        keeper->command("wink at "+TP->query_name());
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

int
check_light()
{
  if(CAN_SEE_IN_ROOM(keeper)) return 1;
  keeper->command("say I am sorry, but I can't work when I can't see...");
  keeper->command("sigh");
  return 0;
}

int
do_buy(string args)
{
  NF("");
  if(!check_keeper("buy")) return 0;
  if(!check_light()) return 0;

  if (!args || args =="")
  {
    NF("Buy what?\n");
    return 0;
  }
  TP->catch_msg("You ask "+QTNAME(keeper)+" to sell you "+args+".\n");
  say(QCTNAME(TP)+" asks "+QTNAME(keeper)+" to sell "+
      TP->query_objective()+" "+args+".\n");

  set_store_room(STORE_ROOM_SC);
  if(!(::do_buy(args)) && everything_ok)
  {
    set_store_room(STORE_ROOM_H);
    if(!(::do_buy(args)) && everything_ok)
    {
      set_store_room(STORE_ROOM_R);
      return ::do_buy(args);
    }
  }
  return everything_ok;
}

int
do_value(string args)
{
  NF("");
  if(!check_keeper("value")) return 0;
  if(!check_light()) return 0;

  if (!args || args == "")
  {
    NF("Value what?\n");
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

  set_store_room(STORE_ROOM_SC);
  if(!(::do_value(args)) && everything_ok)
  {
    set_store_room(STORE_ROOM_H);
    if(!(::do_value(args)) && everything_ok)
    {
      set_store_room(STORE_ROOM_R);
      return ::do_value(args);
    }
  }
  return everything_ok;
}

int
do_sell(string args)
{
  NF("");
  if(!check_keeper("sell")) return 0;
  if(!check_light()) return 0;

  if (!args || args == "")
  {
    NF("Sell what?\n");
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
  set_store_room(STORE_ROOM_R);
  return ::do_sell(args);
}

int
do_list(string str)
{
    object *item_arr_sc, *item_arr_h, *item_arr_r;
    int i, price, *arr;
    string text;

    if(!check_keeper("list")) return 1;
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

    call_other(STORE_ROOM_SC, "load_me");
    item_arr_sc = all_inventory(find_object(STORE_ROOM_SC));
    call_other(STORE_ROOM_H, "load_me");
    item_arr_h = all_inventory(find_object(STORE_ROOM_H));
    call_other(STORE_ROOM_R, "load_me");
    item_arr_r = all_inventory(find_object(STORE_ROOM_R));

    if (!(sizeof(item_arr_sc) || sizeof(item_arr_h) || sizeof(item_arr_r)))
    {
	shop_hook_list_empty_store(str);
	return 0;
    }

    if (str == "weapons")
    {
      item_arr_sc = filter(item_arr_sc, "weapon_filter", this_object());
      item_arr_r = filter(item_arr_r, "weapon_filter", this_object());
      item_arr_h = filter(item_arr_h, "weapon_filter", this_object());
    }
    else if (str == "armours")
    {
      item_arr_sc = filter(item_arr_sc, "armour_filter", this_object());
      item_arr_r = filter(item_arr_r, "armour_filter", this_object());
      item_arr_h = filter(item_arr_h, "armour_filter", this_object());
    }
    else if (str)
    {
      item_arr_sc = FIND_STR_IN_ARR(str, item_arr_sc);
      item_arr_r = FIND_STR_IN_ARR(str, item_arr_r);
      item_arr_h = FIND_STR_IN_ARR(str, item_arr_h);
    }

    if (!(sizeof(item_arr_sc) || sizeof(item_arr_h) || sizeof(item_arr_r)))
	return shop_hook_list_no_match(str);
 
    keeper->command("hmm"); 
    if(sizeof(item_arr_sc))
      keeper->command("say I have "+
                       COMPOSITE_DEAD(item_arr_sc)+"...");
    if(sizeof(item_arr_r))
    {
      if(sizeof(item_arr_sc))
        keeper->command("say ...then "+
                       COMPOSITE_DEAD(item_arr_r)+"...");
      else
        keeper->command("say I have "+
                       COMPOSITE_DEAD(item_arr_r)+"...");
    }
    if(sizeof(item_arr_h))
    {
      if(sizeof(item_arr_sc) || sizeof(item_arr_r))
        keeper->command("say ...and from hardware "+
                       COMPOSITE_DEAD(item_arr_h)+"...");
      else
        keeper->command("say I have "+
                       COMPOSITE_DEAD(item_arr_h)+"...");
    }
    keeper->command("say ...and that is all.");
    keeper->command("smile");

    return 1;
}

/** sell ********************************************************/
int
shop_hook_allow_sell(object ob)
{
  if((ob->query_wt() == W_CLUB) || (ob->query_at() == A_SHIELD))
  {
    if(!query_prop("_warning_was_given_"))
    {
      add_prop("_warning_was_given_", 1);
      keeper->command("say I have orders not to buy any clubs or shields!");
      set_alarm(1.0,0.0, &remove_prop("_warning_was_given_"));
    }
    return 0;
  }
  return 1;
}

void
shop_hook_sell_get_money(string str)
{
  TP->catch_msg(QCTNAME(keeper)+" gives you "+str+".\n");
  say(QCTNAME(keeper)+" gives "+str+" to "+QTNAME(TP)+".\n");
}

void
shop_hook_sell_worn_or_wielded(object ob)
{
    NF("@@message_sell_worn_or_wielded:"+file_name(TO)+"|"+
	TP->query_nonmet_name()+"@@");
}
string 
message_sell_worn_or_wielded(string who)
{
  keeper->command("say "+who+", you have not specified to sell "+
                  "worn or wielded objects.");
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
  keeper->command("say The "+what+" is worthless to me, "+TP->query_nonmet_name()+".");
  return "";
}

int
shop_hook_sell_no_match(string *str)
{
  NF("");
  keeper->command("say "+TP->query_nonmet_name()+", you don't have any "+str+".");
  return 0;
}

void 
shop_hook_sell_object_stuck(object ob, int err)
{
  NF("");
  keeper->command("say It seems you are stuck with "+ob->short()+",  "+
                  TP->query_nonmet_name()+".");
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
  keeper->command("say I don't buy "+what+", "+TP->query_nonmet_name()+".");
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
  keeper->command("say You don't have anything to sell "+TP->query_nonmet_name()+".");
  return 0;
}

/** buy *********************************************************/
void 
shop_hook_buy_cant_pay(object ob, int *arr)
{
  everything_ok = 0;
  NF("@@message_buy_cant_pay:"+file_name(TO)+"|"+ob->short()+"@@");
}
string 
message_buy_cant_pay(string what)
{
  keeper->command("say You must have money first "+TP->query_nonmet_name()+
                  " and only then you can buy "+what+".");
  everything_ok = 1;
  return "";
}

void
shop_hook_buy_no_buy(object ob, string str)
{
  everything_ok = 0;
  NF("@@message_buy_no_buy:"+file_name(TO)+"|"+ob->short()+"@@");
}
string 
message_buy_no_buy(string what)
{
  everything_ok = 1;
  keeper->command("say I am sorry "+TP->query_nonmet_name()+". The "+
                  what+" isn't for sale.\n");
  return "";
}

void
shop_hook_buy_no_match(string str)
{
  if(query_store_room() == STORE_ROOM_R)
    NF("@@message_buy_no_match:"+file_name(TO)+"|"+str+"@@");
}
string 
message_buy_no_match(string what)
{
    keeper->command("say Sorry "+TP->query_nonmet_name()+", I have no "+what+
                    " to sell.");
  return "";
}

void
shop_hook_buy_cant_carry(object ob, int err)
{
  NF("");
  tell_room(TO,QCTNAME(keeper)+" drops the "+ob->short()+" on the floor.\n");
  keeper->command("say You can't carry it "+TP->query_nonmet_name()+".\n");
  keeper->command("comfort "+TP->query_name());
}

void
shop_hook_buy_magic_money(object ob)
{
  everything_ok = 0;
  NF("@@message_buy_magic_money@@");
}
string 
message_buy_magic_money()
{
  keeper->command("say You are carrying magic money "+QCNAME(TP)+
                  ", no deal!");
  everything_ok = 1;
  return "";
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
  everything_ok = 0;
  NF("@@message_value_not_interesting:"+file_name(TO)+"|"+ob->short()+"@@");
}
string 
message_value_not_interesting(string what)
{
  keeper->command("say The "+what+" doesn't interest me, "+
                  TP->query_nonmet_name()+".");
  everything_ok = 1;
  return "";
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
  keeper->command("say I can sell you "+ob->short()+" for "+text+", "+
                  TP->query_nonmet_name()+".");
}

void
shop_hook_value_asking(string str)
{ return; }

int
shop_hook_value_no_match(string str)
{
  NF("");
  if(query_store_room() == STORE_ROOM_R)
  {
    keeper->command("say How can I value '"+str+"' when neither you nor me "+
                  "have it?");
    keeper->command("peer at "+TP->query_name());
  }
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
  keeper->command("say We have no "+str+" in stock, "+TP->query_nonmet_name()+".\n");
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
  tell_room(TO, QCTNAME(TP)+" tries to go to storeroom but bumps into closed door.\n");
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

   if(TP->query_race_name() == "elf")
     return ((bargain * 120) / 100); 
   if(member_array(TP->query_race_name(), ({"goblin","human","dwarf"})) != -1)
     return ((bargain * 85) / 100);
   return bargain;
}
