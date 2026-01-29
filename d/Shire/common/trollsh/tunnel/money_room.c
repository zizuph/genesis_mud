/*
 * Money changer room in the trollshaws
 * Altrus, July 2005
 * money changing code borrowed from goblin cave's changer
 */
 

#pragma strict_types

inherit "/d/Shire/std/room.c";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <money.h>
#include <ss_types.h>
#include <filter_funs.h>

inherit "/lib/trade";

#define STD_FEE 15

/*
 * Prototypes
 */
void config_trade_data();
void set_bank_fee(int fee);

object banker;  /* banker who does all transactions */
static  int test;   /* To indicate that a test is going on. */
static  int bank_fee;   /* The bank fee */
static  int money_num;  /* Num of money types. */

void
create_shire_room()
{
    add_prop(ROOM_S_MAP_FILE, "trollshaws2.txt");

    set_short("A dank side room");
    set_long("You are standing in a dank, damp room somewhere under the Trollshaws. The ceiling is low, and the light is dim. It doesn't smell half so bad in here as the rest of the place, but that isn't saying much. To the east lies the main tunnel.\n");
    
    add_item("ceiling", "The low ceiling is covered in pale lichens, which is probably where the low light is eminating.\n");
	add_item(({"lichens", "pale lichens", "lichen", "pale lichen"}),"The pale lichen appears to be greyish color, or possibly green. It appears to be the only source of light in this room.\n");
	
    add_exit("/d/Shire/common/trollsh/tunnel/tb01", "east");
	
    config_default_trade();
    set_bank_fee(STD_FEE);
    config_trade_data();
	
    reset_shire_room();
}

void
reset_shire_room()
{
    if(banker && present(banker,TO)) 
	return;
    banker = clone_object("/d/Shire/common/trollsh/npc/banker");
    banker->move(TO);
}

void init()
{
    ::init();
    add_action("change", "change");
    add_action("change", "exchange");
    add_action("minimize", "minimize");
    add_action("test", "test");
}

void set_bank_fee(int fee) { bank_fee = fee; }
int query_bank_fee() { return bank_fee; }

int valid_type(string str)
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

    return -1;      /* This should not happen */
}

void config_trade_data()
{
    set_money_greed_buy("@@discriminate");
    set_money_greed_change("@@discriminate");

    /* Copper Silver Gold  Platinum  */
    set_money_give_out(({40000, 4000, 2000, 200}));
    set_money_give_max(40000);
    set_money_give_reduce(({0, 0, 0, 0}));

    money_num = sizeof(query_money_types());
}

int discriminate()
{
    int bargain;

    bargain = TP->query_skill(SS_TRADING);
    if(bargain > 40) bargain = 40;
    bargain = 100 - bargain/3;

//  if(TP->query_race_name() == "goblin")
//  return ((bargain * 95) / 100) + STD_FEE;
    return ((bargain * 105) / 100) + STD_FEE;
}


int check_banker(string arg)
{
    object enemy;
    string who;

    if (banker && present(banker,TO) && !banker->query_no_show())
    {
	who = TP->query_nonmet_name();
	if(banker->query_introduced(TP))
	    who = TP->query_name();
	if(enemy = banker->query_attack())
	{
	    if(enemy == TP)
	    {
		banker->command("say Now ye want to "+arg+" something? Just leave me be!");
		banker->command("ponder stupid "+who);
	    }
	    else
	    {
		banker->command("say Please "+who+"! gots t'wait until I kills "+enemy->query_nonmet_name()+"! Unless ye wants t'help?");
		banker->command("wink "+TP->query_name());
	    }
	    return 0;
	}
	else
	    return 1;
    }
    else
    {
	TP->catch_msg("There ain't anyone here to help you, so you can't do that!\n");
	return 0;
    }
}

int check_intro(string arg)
{
    if(banker->query_introduced(TP)) return 1;
    banker->command("say If ye want to "+arg+" something then ye should at "+
      "least introduce yerself!");
    banker->command("grumble "+TP->query_name());
    return 0;
}

int check_light()
{
    if(CAN_SEE_IN_ROOM(banker)) return 1;
    banker->command("say I am sorry "+TP->query_name()+" but I can't work "+
      "when I can't see.");
    banker->command("say 'Tis too hard fer me t'count.");
    banker->command("say I'd hate t'be givin' ye more than I mean to!!");
    banker->command("grin greedily");
    return 0;
}

void bank_hook_pay(string text)
{
    if(test)
	banker->command("say Ye would pay "+text+"...");
    else
    {
	TP->catch_msg("You give "+text+" to "+QTNAME(banker)+".\n");
	say(QCTNAME(TP)+" gives "+text+" to "+QTNAME(banker)+".\n");
    }
}

void bank_hook_change(string text)
{
    if(test)
	banker->command("say and get "+text+" back.");
    else
    {
	TP->catch_msg(QCTNAME(banker)+" runs off into the shadows... You hear a faint jingling of metal on metal, then suddenly he is back and giving "+
	  text+" to you.\n");
	say(QCTNAME(banker)+" runs off into the shadows... You hear a faint jingling of metal on metal, then suddenly he is back and giving "+text+
	  " to "+QTNAME(TP)+".\n");
    }
}

void bank_hook_already_minimized()
{
    banker->command("say Your coins are already minimized.");
    banker->command("pat "+TP->query_name());
}

void bank_hook_no_idea()
{
    banker->command("shake");
    banker->command("say All your coins would be spent on my fee "+
      TP->query_name()+".");
}

void bank_hook_minimized(string pay_text, string got_text)
{
    TP->catch_msg("You give "+pay_text+" to "+QTNAME(banker)+".\n");
    say(QCTNAME(TP)+" give "+pay_text+" to "+QTNAME(banker)+".\n");
    TP->catch_msg(QCTNAME(banker)+" runs off into the shadows... You hear a faint jingling of metal on metal, then suddenly he is back and giving "+got_text+" to you.\n");
	say(QCTNAME(banker)+" runs off into the shadows... You hear a faint jingling of metal on metal, then suddenly he is back and giving "+got_text+" to "+QTNAME(TP)+".\n");
}

int change(string str)
{
    string str1, str2, dummy, change;
    int price, i, j, *arr, *hold_arr, *change_arr, number, greed;

    if(!check_banker("change")) return 1;
    if(!check_intro("change")) return 1;
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

string message_no_str()
{
    banker->command("say "+TP->query_name()+", what do you want to "+
      query_verb()+"?");
    banker->command("peer");
    return "";
}
string message_wrong_def()
{
    banker->command("say "+TP->query_name()+", you have to better define what "+
      "you want to change and to what it will be.");
    banker->command("pat "+TP->query_name());
    return "";
}
string message_no_coins()
{
    banker->command("say "+TP->query_name()+", you can only change coins "+
      "you hold.");
    banker->command("pat "+TP->query_name());
    return "";
}
string message_0()
{
    banker->command("say "+TP->query_name()+", don't you think that you ought "+
      "to give a number higher than 0?");
    banker->command("pat "+TP->query_name());
    return "";
}
string message_cannot_afford()
{
    banker->command("say "+TP->query_name()+", you cannot afford that!");
    banker->command("pat "+TP->query_name());
    return "";
}
string message_not_valid()
{
    banker->command("say "+TP->query_name()+", you have to choose a valid type "+
      "of coins.");
    banker->command("pat "+TP->query_name());
    return "";
}

int minimize(string str)
{
    int *money_arr, *money_arr2, value, i, new_sum, total_sum, greed;
    string change;

    if(!check_banker("minimize")) return 1;
    if(!check_intro("minimize")) return 1;
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

int test(string str)
{
    int i;
    string str1;

    notify_fail("Test what?\n");
    if (!str)
	return 0;

    if(!check_banker("test")) return 1;
    if(!check_intro("test")) return 1;
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
