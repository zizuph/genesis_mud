inherit "/d/Rhovanion/lib/room";
inherit "/lib/trade";
 
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include "/d/Rhovanion/defs.h"
 
#define STD_FEE 30
#define BANKER  "your_banker"  /* redefine this */
 
/*
 * Prototypes
 */
void reset_room();
void config_trade_data();
set_bank_fee();
 
object banker;  /* banker who does all transactions */
static	int	test;	/* To indicate that a test is going on. */
static	int	bank_fee;	/* The bank fee */
static	int	money_num;	/* Num of money types. */
 
void
create_room()
{
  reset_room();
 
  add_prop(ROOM_I_INSIDE,1);
 
  set_short("Camp bank");
 
/*** redefine long but I suggest leave the safe in desc ***/
 
  set_long("You are at the end of the tunnel that burrow under the Misty "
    + "Mountains. It is very humid and the walls are damp with condensed "
    + "water. You seriously hope that you are not lost because every "
    + "tunnel looks much the same as the last...\n"
    + "But this one is slightly different. There is a massive safe in "
    + "the wall. One greedy goblin made private "
    + "bank here. If he is here he may change some of your money. If you "
    + "want to know more you can ask him for more instructions.\n");
 
  add_item("safe","This massive safe in the wall looks unbreakable.\n");
 
  config_default_trade();
 
  set_bank_fee(STD_FEE); /* To set the exchange fee (% of changed amount) */
  config_trade_data();
 
}
 
void
reset_room()
{
  if(banker)
  {
    if(present(banker,TO)) return;
 
    banker->command("oops");
    banker->command("say I must not leave the bank!");
    banker->command("ponder all thieves around");
    tell_room(ENV(banker), QCTNAME(banker)+" runs back to "+HIS(banker)+
                           " bank.\n");
    banker->move_living("M", TO);
    tell_room(TO, QCTNAME(banker)+" arrives running.\n");
    banker->command("say Back again.");
    banker->command("emote quickly checks the safe.");
    banker->command("sigh relieved");
    return;
  }
 
  banker = clone_object(BANKER);
  banker->arm_me();
  banker->move_living("M",TO);
  banker->command("say Back in business.");
  banker->command("emote quickly checks the safe.");
  banker->command("sigh relieved");
}
 
init()
{
    ::init();
    add_action("push_something", "push");
    add_action("pull_something", "pull");
    add_action("change", "change");
    add_action("change", "exchange");
    add_action("minimize", "minimize");
    add_action("test", "test");
    add_action("open_safe", "open");
    add_action("unlock_safe", "unlock");
}
 
int
open_safe(string arg)
{
  NF("It is too dark to see.\n");
  if(!CAN_SEE_IN_ROOM(TP)) return 0;
  NF("Open what?\n");
  if(!arg || (arg != "safe")) return 0;
  say(QCTNAME(TP)+" tries desperately open the safe but it "+
      "remains closed.\n");
  TP->catch_msg("You try desperately open the safe but it remains closed.\n");
  if(banker && present(banker,TO))
  {
    banker->command("knee "+TP->query_real_name());
    banker->command("shout Don't mess with my safe!!!");
  }
  return 1;
}
 
int
unlock_safe(string arg)
{
  NF("It is too dark to see.\n");
  if(!CAN_SEE_IN_ROOM(TP)) return 0;
  NF("Unlock what?\n");
  if(!arg) return 0;
  if(explode(arg+" "," ")[0] != "safe") return 0;
  say(QCTNAME(TP)+" tries unlock "+arg+" but it doesn't seem to work.\n");
  TP->catch_msg("You try to unlock "+arg+" but it doesn't seem to work.\n");
  if(banker && present(banker,TO))
  {
    banker->command("shout I will really kill you!!!");
    banker->command("kill "+TP->query_real_name());
    banker->command("tackle "+TP->query_real_name());
  }
  return 1;
}
 
void set_bank_fee(int fee) { bank_fee = fee; }
int query_bank_fee() { return bank_fee; }
 
int
valid_type(string str)
{
    int i, j, *tmp_arr;
    string *m_names;
 
    m_names = explode(str, " ");
    tmp_arr = allocate(money_num);
 
    for (i = 0; i < sizeof(m_names); i++)
        for (j = 0; j < money_num; j++)
            if (m_names[i] == query_money_types()[j])
                tmp_arr[j] = 1;
 
    for (i = 0; i < money_num; i++)
	if (tmp_arr[i] == 1)
	    return i;
 
    return -1;		/* This should not happen */
}
 
void
config_trade_data()
{
  set_money_greed_buy("@@discriminate");
  set_money_greed_change("@@discriminate");
 
                   /* Copper Silver Gold  Platinum  */
  set_money_give_out(({40000, 4000, 2000, 200}));
  set_money_give_max(40000);
  set_money_give_reduce(({0, 0, 0, 0}));
 
  money_num = sizeof(query_money_types());
}
 
int
discriminate() {
   int bargain;
 
   bargain = TP->query_skill(SS_TRADING);
   if(bargain > 30) bargain = 30;
   bargain = 105 - bargain/3;
 
   return bargain + STD_FEE;
}
 
 
int
check_banker(string arg)
{
  object enemy;
  string who;
 
  if (banker && present(banker,TO) && !banker->query_no_show())
  {
    who = TP->query_nonmet_name();
    if(enemy = banker->query_attack())
    {
      if(enemy == TP)
      {
        banker->command("say Now you want to "+arg+" something? I will kill "+
                        "you and take all your coins!");
        banker->command("ponder stupid "+who);
      }
      else
      {
        banker->command("say Please "+who+"! You must wait untill I kill "+
                        "this coward "+enemy->query_nonmet_name()+"! "+
                        "Maybe you can help me too?");
        banker->command("wink "+TP->query_name());
      }
      return 0;
    }
    else
      return 1;
  }
  else
  {
    TP->catch_msg("There is no banker here, so you can't do that!\n");
    return 0;
  }
}
 
int
check_light()
{
  if(CAN_SEE_IN_ROOM(banker)) return 1;
  banker->command("say I am sorry "+TP->query_nonmet_name()+" but I can't work "+
                  "when I can't see.");
  banker->command("say You know... It is hard to count money in the dark.");
  banker->command("say And I dont want to make mistake...");
  banker->command("say ...in your favor!");
  banker->command("grin");
  return 0;
}
 
void
bank_hook_pay(string text)
{
  if(test)
    banker->command("say You would pay "+text+"...");
  else
  {
    TP->catch_msg("You give "+text+" to "+QTNAME(banker)+".\n");
    say(QCTNAME(TP)+" give "+text+" to "+QTNAME(banker)+".\n");
  }
}
 
void
bank_hook_change(string text)
{
  if(test)
    banker->command("say and get "+text+" back.");
  else
  {
    TP->catch_msg(QCTNAME(banker)+" opens safe, puts coins inside, gets "+
                text+", locks safe and gives coins to you.\n");
    say(QCTNAME(banker)+" opens safe, puts coins inside, gets "+text+
       ", locks safe and gives coins to "+QTNAME(TP)+".\n");
  }
}
 
void
bank_hook_already_minimized()
{
  banker->command("say Your coins are already minimized.");
  banker->command("pat "+TP->query_name());
}
 
void
bank_hook_no_idea()
{
  banker->command("shake");
  banker->command("say All your coins would be spent on my fee "+
                  TP->query_nonmet_name()+".");
}
 
void
bank_hook_minimized(string pay_text, string got_text)
{
  TP->catch_msg("You give "+pay_text+" to "+QTNAME(banker)+".\n");
  say(QCTNAME(TP)+" give "+pay_text+" to "+QTNAME(banker)+".\n");
  TP->catch_msg(QCTNAME(banker)+" opens safe, puts coins inside, gets "+
                got_text+", locks safe and gives coins to you.\n");
  say(QCTNAME(banker)+" opens safe, puts coins inside, gets "+got_text+
       ", locks safe and gives coins to "+QTNAME(TP)+".\n");
}
 
int
change(string str)
{
    string str1, str2, dummy, change;
    int price, i, j, *arr, *hold_arr, *change_arr, number, greed;
 
  if(!check_banker("change")) return 1;
  if(!check_light()) return 1;
 
  if(!test)
  {
    TP->catch_msg("You humbly ask "+QTNAME(banker)+" to "+query_verb()+" "+
                  str+".\n");
    say(QCTNAME(TP)+" humbly asks "+QTNAME(banker)+" to "+query_verb()+" "+
        str+".\n");
  }
 
    greed = query_money_greed_buy();
 
    if (!str)
    {
        NF(VBFC_ME("message_no_str"));
	return 0;
    }
    if (!parse_command(str, ({}), "%s 'to' / 'for' %s", str1, str2))
    {
        NF(VBFC_ME("message_wrong_def"));
	return 0;
    }
 
    NF(VBFC_ME("message_no_coins"));
 
    /* First find out how many coins player maximum can change to
     * Arguments: price = 0, changer = TP, str1 = what changer
     * wants to change, 1 = this is a test, 0 = a nil object (we),
     * str2 = how changer wants the change
     *
     * These settings returns an array of what the changer wants to
     * change and how much that would be in the change the changer has
     * chosen. Then we can calculate the exact amount to change.
     */
    if (sizeof(arr = pay(0, TP, str1, 1, 0, str2)) == 1)
	return 0;
 
    hold_arr = exclude_array(arr, money_num, 2 * money_num - 1);
    change_arr = exclude_array(arr, 0, money_num - 1);
 
    if ((i = valid_type(str1)) >= 0)
    {
	if (sscanf(str1, "%d %s", number, dummy) == 2)
        {
	    if (number > hold_arr[i])
	    {
                NF(VBFC_ME("message_no_coins"));
		return 0;
	    }
	    hold_arr[i] = number;
	    change_arr = calc_change(0, hold_arr, str2);
            NF(VBFC_ME("message_0"));
	}
 
	if (hold_arr[i] <= 0)
	    return 0;
 
	if ((i = valid_type(str2)) >= 0)
	{
	/* We need the price in order to take money from the player */
	    if (sscanf(str2, "%d %s", number, dummy) == 2)
            {
	        if (number > change_arr[i])
	        {
                    NF(VBFC_ME("message_cannot_afford"));
		    return 0;
	        }
	        change_arr[i] = number;
                NF(VBFC_ME("message_0"));
	        if (change_arr[i] <= 0)
		    return 0;
	    }
	    if ((change_arr[i] * query_money_values()[i] * greed / 100) >
				query_money_give_max())
		change_arr[i] = (query_money_give_max() * 100 / greed) /
				query_money_values()[i];
 
	    for (j = i - 1; j >= 0; j--)
	        change_arr[j] = 0;
 
    	    price = money_merge(change_arr);
	    if (price < 1)
	    {
                NF(VBFC_ME("message_cannot_afford"));
		return 0;
	    }
        }
        else
        {
            NF(VBFC_ME("message_not_valid"));
            return 0;
        }
    }
    else
    {
        NF(VBFC_ME("message_not_valid"));
	return 0;
    }
 
    /* Here is the actual change taking place */
    if (!(arr = pay(price, TP, str1, test, 0, str2)))
	return 0;
    give(price, TP, str2, test, 0, 0);
 
    /* Now, in the pay() the player could have been given some change back,
     * add it.
     */
    for (i = 0; i < money_num; i++)
	change_arr[i] = change_arr[i] + arr[i + money_num];
 
    /*
     * Some hooks for people who wants different messages.
     */
    bank_hook_pay(text(arr[0 .. money_num - 1]));
    if (change = text(change_arr))
      bank_hook_change(change);
    return 1;
}
 
string
message_no_str(){
  banker->command("say "+TP->query_nonmet_name()+", what do you want to "+
                   query_verb()+"?");
  banker->command("peer");
  return "";
}
string
message_wrong_def(){
  banker->command("say "+TP->query_nonmet_name()+", you have to better define what "+
                  "you want to change and to what it will be.");
  banker->command("pat "+TP->query_name());
  return "";
}
string
message_no_coins(){
  banker->command("say "+TP->query_nonmet_name()+", you can only change coins "+
                  "you hold.");
  banker->command("pat "+TP->query_name());
  return "";
}
string
message_0(){
  banker->command("say "+TP->query_nonmet_name()+", don't you think that you ought "+
                  "to give a number higher than 0?");
  banker->command("pat "+TP->query_name());
  return "";
}
string
message_cannot_afford(){
  banker->command("say "+TP->query_nonmet_name()+", you cannot afford that!");
  banker->command("pat "+TP->query_name());
  return "";
}
string
message_not_valid(){
  banker->command("say "+TP->query_nonmet_name()+", you have to choose a valid type "+
                  "of coins.");
  banker->command("pat "+TP->query_name());
  return "";
}
 
int
minimize(string str)
{
    int *money_arr, *money_arr2, value, i, new_sum, total_sum, greed;
    string change;
 
  if(!check_banker("minimize")) return 1;
  if(!check_light()) return 1;
 
  TP->catch_msg("You humbly ask "+QTNAME(banker)+" to minimize your coins.\n");
  say(QCTNAME(TP)+" humbly asks "+QTNAME(banker)+" to minimize "+
      TP->query_possessive()+" coins.\n");
 
    greed = query_money_greed_buy();
 
    money_arr = what_coins(TP);
 
    money_arr2 = split_values(total_sum = money_merge(money_arr));
    for (i = 0; i < money_num; i++)
    {
	money_arr2[i] -= money_arr[i];
	if (money_arr2[i] < 0)
	    money_arr2[i] = 0;
    }
    value = money_merge(money_arr2);
    if (!value)
    {
	bank_hook_already_minimized();
	return 1;
    }
    new_sum = total_sum - (greed - 100) * value / 100;
    money_arr2 = split_values(new_sum);
    for (i = 0; i < money_num; i++)
    {
	money_arr2[i] -= money_arr[i];
	if (money_arr2[i] < 0)
	    money_arr2[i] = 0;
    }
    value = money_merge(money_arr2);
    if (!value)
    {
	bank_hook_no_idea();
	return 1;
    }
 
    MONEY_ADD(TP, new_sum);
    MONEY_ADD(TP, -total_sum);
 
    money_arr2 = split_values(new_sum);
    bank_hook_minimized(text(money_arr),text(money_arr2));
 
    return 1;
}
 
int
test(string str)
{
    int i;
    string str1;
 
    notify_fail("Test what?\n");
    if (!str)
	return 0;
 
  if(!check_banker("test")) return 1;
  if(!check_light()) return 1;
 
  TP->catch_msg("You humbly ask "+QTNAME(banker)+" what will he do if "+
                "you ask him to "+str+".\n");
  say(QCTNAME(TP)+" humbly asks "+QTNAME(banker)+" what will he do if "+
      TP->query_pronoun()+" asks him to "+str+".\n");
  banker->command("hmm");
  banker->command("scratch");
 
    if (parse_command(str, ({}), "'change' / 'exchange' %s", str1))
    {
	test = 1;
	i = change(str1);
	test = 0;
	return i;
    }
}
