/*
 *   ~Faerun/lib/alchemist.c
 *
 *   This is the original herbalist originally coded for Shire as
 *   ~Shire/lib/herbalist.c by Igneous. It has been converted over as an
 *   alchemist to handle potions. alchemist_ex.c is a sample NPC.
 *   - Finwe, July 2007
 *
 *   Revision history:
 */

#pragma strict_types

inherit "/lib/trade.c";

#include <cmdparse.h>
#include <composite.h>
#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <std.h>
#include "/d/Faerun/defs.h"

//  Error Defines
#define ERROR_LOG   "alchemist"
#ifdef  ERROR_LOG
#define ERROR(s)    log_file(ERROR_LOG, MASTER_OB(TO) + ": " + s + "\n")
#else
#define ERROR(s)
#endif

//  Debugging Defines
#define DEBUGGING
#undef  DEBUGGING
#ifdef  DEBUGGING
#define DEBUG_WHO   find_player("finwe")
#define DEBUG(s)    DEBUG_WHO->catch_msg("ALCHEMIST:  "+ s +"\n")
#else
#define DEBUG(s)
#endif

#define AMOUNT      0
#define PRICE       1
#define FILENAME    2
#define MAX_POTIONS   40  /* Maxium number of potions this npc will save */
#define MAX_BUY     10  /* Maxium number of potions one can buy */
#define MAX_SELL    20  /* Maxium number of potions one can sell */
#define NUM         sizeof(MONEY_TYPES)
// #define WRAP "/d/Shire/common/herbs/obj/wrap.c"

// Prototypes
nomask void save_potions();
nomask void add_potion(object potion);
nomask void restore_potions();
int  potion_filter(object ob);
int         do_buy(string str);
int         do_list(string str);
int         do_sell(string str);
void        do_pay(object player, int amount);
string      add_white_space(string str);
string      del_white_space(string str);
//  Hook Prototypes
void alchemist_room_dark_hook();
void alchemist_no_see_hook();
void alchemist_no_potions_to_sell_hook(int i);
void alchemist_max_sell_hook();
void alchemist_sold_hook(object *potions);
void alchemist_pay_hook(string text);
void alchemist_no_potions_to_list_hook();
void alchemist_list_header_hook();
void alchemist_no_potion_match_hook(string str);
void alchemist_found_potion_match_hook(string str);
void alchemist_buy_no_potion_hook(string potion_name);
void alchemist_buy_too_many_hook(int amount);
void alchemist_buy_low_potion_hook(int amount);
void alchemist_cant_pay_hook(int price);
void alchemist_give_potions_hook(object *order,object player);
void alchemist_sold_last_potion_hook(string str);
void alchemist_not_potion_hook(object ob, object player);
void alchemist_give_potion_back_hook(object potion, object player);
void alchemist_identify_potion_hook(object potion, object player);
int  alchemist_selling_price_modifier_hook(object player);
public string query_file();
// public void add_wraps();

// Global Vars
private mapping  Potions = ([]);
string    Save_file;
int       Maximum_potions = MAX_POTIONS, Maximum_sell  = MAX_SELL;
int       Maximum_buy   = MAX_BUY, gBusy = 0, gDry = 1, gId_potion = 0;

/*
 * Function name : Configure_alchemist
 * Arguments     : string filename: The filename for the save file.
 * Description   : Sets up and configures the trading and restores the
 *                 Potions mapping.
 *                 This function _MUST_ be in the create_*() of your
 *                 alchemist for it to work.
 */
nomask void
configure_alchemist(string filename)
{

    config_default_trade();
    set_money_give_out(({ 10000,   700,  10,  10 }));
    set_money_give_reduce(({  0,     0,   0,   0 }));

    Save_file = filename;
    restore_potions();
//     add_wraps();
}

/*
 * Function name : query_file
 * Description   : Returns potion mapping filename
 *
 */
public string
query_file()
{
    return Save_file;
}

/*
 * Function name : Init_alchemist
 * Description   : Initalizes the commands for players to use this alchemist
 *                 This function _MUST_ be in the init_living() of your
 *                 alchemist for it to work.
 */
nomask void
init_alchemist()
{
    add_action(do_sell, "sell");
    add_action(do_list, "list");
    add_action(do_buy,  "buy");

}

nomask void
init_alchemist_identify(object potion, object from)
{
    if (!objectp(from) || !objectp(potion))
	    return;

    if (!gId_potion)
	    return;

    if (!function_exists("create_potion",potion))
    {
	    set_alarm(1.0,0.0,&alchemist_not_potion_hook(potion, from));
	    return;
    }

    if (gBusy)
    {
	    set_alarm(1.0,0.0,&alchemist_give_potion_back_hook(potion, from));
	    return;
    }
    gBusy = 1;
    set_alarm(1.0,0.0, &alchemist_identify_potion_hook(potion,from));
}

void
set_alchemist_id_potions()
{
    this_object()->remove_prop(LIVE_M_NO_ACCEPT_GIVE);
    gId_potion = 1;
}

void
set_alchemist_dry_potions()
{
    gDry = 1;
}

void
unset_alchemist_dry_potions()
{
    gDry = 0;
}

/*
 * Function name : Set_max_potions_kept
 * Arguments     : int amount:  The amount of potions to be kept
 * Description   : sets the maximum limit of potions that are kept by the
 *                 Herbalist
 */
void
set_max_potions_kept(int amount)
{
    if (amount > 0)
	Maximum_potions = amount;
}

/*
 * Function name : Set_max_buy
 * Arguments     : int amount:  The amount to set the maximum to
 * Description   : sets the maximium amount of potions the player can buy at
 *                 one time.
 */
void
set_max_buy(int amount)
{
    if (amount > 0)
	Maximum_buy = amount;
}

/*
 * Function name : Set_max_sell
 * Arguments     : int amount:  The amount to set the maximum to
 * Description   : sets the maximum amount of potions a player can sell at
 *                 one time
 */
void
set_max_sell(int amount)
{
    if (amount > 0)
	Maximum_sell = amount;
}

int
query_potion_list_size()
{
    return sizeof(m_indexes(Potions));
}

string
query_potion_list()
{
    string potionname, str = "";
    int i;

    for (i = 0;i < sizeof(m_indexes(Potions));i++)
    {
	potionname = m_indexes(Potions)[i];
	str += Potions[potionname][AMOUNT] + " of "+ potionname +" "+
	Potions[potionname][FILENAME]+" at a cost of "+Potions[potionname][PRICE]+
	" copper coins each.\n";
    }
    str += "\n";

    return str;
}

int
query_potions_max_kept()
{
    return Maximum_potions;
}

int
query_potions_max_buy()
{
    return Maximum_buy;
}

int
query_potions_max_sell()
{
    return Maximum_sell;
}

/*
 * Function name : add_wraps
 * Description   : gives the alchemist 100 potion wraps
 */
public void
add_wraps()
{
//    Potions += (["wrap": ({100, 33, WRAP})]);
}


/*
 * Function name : Restore_potions
 * Description   : restores the Potions mapping from the Save_file.
 */
nomask private void
restore_potions()
{
    setuid(); seteuid(getuid());
    if (!Save_file || !stringp(Save_file))
    {
	ERROR("No save file for the alchemist, Herbalist removed!!");
	TO->remove_object();
    }
    Potions = restore_map(Save_file);
    if (!mappingp(Potions))
	Potions = ([ ]);
}

/*
 * Function name : Save_potions
 * Description   : saves the Potions mapping
 */
nomask private void
save_potions()
{
    if (!Save_file || !stringp(Save_file))
    {
	ERROR("Unable to save the potion information, no save file.");
	return;
    }
    save_map(Potions, Save_file);
}

/*
 * Function name : Add_potion
 * Arguments     : object potion: The potion we are currently looking at
 * Description   : adds a potion to the mapping and removes the potion object.
 */
nomask private void
add_potion(object potion)
{
    int number;
    string name;

    name = potion->query_potion_name();
    name = del_white_space(name);
    if (!pointerp(Potions[name]))
    {
    	Potions[name] = ({1, potion->query_potion_value(), MASTER_OB(potion)});
    }
    else
    {
	if (MASTER_OB(potion) != Potions[name][FILENAME])
	    ERROR(MASTER_OB(potion) + " already exists in mapping "+
	      "under a different filename, and was not added.");
	else
	{
	    number = Potions[name][AMOUNT];
	    if (number < Maximum_potions)
		Potions[name][AMOUNT] = number + 1;
	}
    }

    potion->remove_object();

    if (objectp(potion))
	SECURITY->do_debug("destroy",potion);
}

/*
 * Function name : potion_filter
 * Arguments     : object ob: Some object
 * Description   : Filters non-potion objects from an array.
 * Returns       : 1 if a potion / 0 if not
 */
int
potion_filter(object ob)
{
    if (!function_exists("create_potion",ob))
	    return 0;

    if (!ob->query_potion_name() || !ob->query_potion_value())
	    return 0;

    if (ob->query_prop(OBJ_M_NO_SELL))
	    return 0;

    return 1;
}

string
del_white_space(string str)
{
    string *words;

    if (sizeof(words = explode(str, " ")) > 1)
	str = implode(words, "_");
    return str;
}

string
add_white_space(string str)
{
    string *words;

    if (sizeof(words = explode(str, "_")) > 1)
	str = implode(words, " ");
    return str;
}


/*
 * Function name : Do_buy
 * Arguments     : What potion we want to buy and how many
 * Description   : The buy function.
 * Returns       : 1/0
 */

int
do_buy(string str)
{
    string item_name, coin_pay_text, coin_get_text;
    string *words;
    int    *money_arr, amount, price, i;
    object *order;

    if (!Save_file)
    {
	ERROR("No potion save file found!!");
    }
    if (!CAN_SEE_IN_ROOM(TO))
    {
	    alchemist_room_dark_hook();
	    return 1;
    }
    if (!CAN_SEE(TO, TP))
    {
	    alchemist_no_see_hook();
	    return 1;
    }
    if (!strlen(str))
    {
	    notify_fail("Buy what?\n");
	    return 0;
    }

    str = lower_case(str);
    if (str == "potions")
	    return do_list(str);

    words = explode(str, " ");

    if (sizeof(words) > 1)
    {
	    sscanf(words[0], "%d", amount);
	    if (amount > 0)
	        str = implode(words[1..sizeof(words)], " ");
	    else
	        amount = 1;
    }
    else
	amount = 1;

    item_name = del_white_space(str);

    if (!pointerp(Potions[item_name]))
    {
	    alchemist_buy_no_potion_hook(str);
	return 1;
    }
    if (Potions[item_name][AMOUNT] < amount)
    {
	alchemist_buy_low_potion_hook(amount);
	return 1;
    }
    if (amount > Maximum_buy)
    {
	alchemist_buy_too_many_hook(amount);
	return 1;
    }

    // Make sure the potion is loaded.
    Potions[item_name][FILENAME]->load_me();
    if (!find_object(Potions[item_name][FILENAME]))
    {
	command("hmm");
	command("say I'm sorry I can't find "+item_name+" anywhere.");
	command("say This is a definite bug, please leave a bug report.");
	ERROR(Potions[item_name][FILENAME] +" does not exist!");
	return 1;
    }

    price = Potions[item_name][PRICE] * amount;
    if (sizeof(money_arr = pay(price)) == 1)
    {
	alchemist_cant_pay_hook(price);
	return 1;
    }

    coin_pay_text = text(exclude_array(money_arr, NUM, NUM*2-1));
    coin_get_text = text(exclude_array(money_arr, 0, NUM-1));
    write("You pay the alchemist "+coin_pay_text+" for "+amount+
      " "+str+".\n");
    if (coin_get_text)
	write("You get " + coin_get_text + " back.\n");

    order = allocate(amount);
    for (i = 0; i < amount; i++)
    {
	order[i] = clone_object(Potions[item_name][FILENAME]);
    }

    Potions[item_name][AMOUNT] -= amount;
    alchemist_give_potions_hook(order, TP);
    if (Potions[item_name][AMOUNT] == 0)
    {
	Potions = m_delete(Potions, item_name);
	alchemist_sold_last_potion_hook(str);
    }
    save_potions();
    return 1;
}

/*
 * Function name : Do_sell
 * Arguments     : str: The potions we want to sell.
 * Description   : The selling function
 * Returns       : 1/0
 */
int
do_sell(string str)
{
    object *potions;
    int value, skill_avg, i, intPotion;

    if (!Save_file)
    {
	ERROR("No potion save file found!!!");
    }
    if (!CAN_SEE_IN_ROOM(TO))
    {
	alchemist_room_dark_hook();
	return 1;
    }
    if (!CAN_SEE(TO, TP))
    {
	alchemist_no_see_hook();
	return 1;
    }
    if (!strlen(str))
    {
	notify_fail("Sell what?\n");
	return 0;
    }
    str = lower_case(str);

    // Find the potions we are selling.

    potions = FIND_STR_IN_OBJECT(str, TP);
    potions = filter(potions, &potion_filter());

    if (!sizeof(potions))
    {
	alchemist_no_potions_to_sell_hook(intPotion);
	return 1;
    }

    if (sizeof(potions) > Maximum_sell)
    {
	alchemist_max_sell_hook();
	return 1;
    }
    alchemist_sold_hook(potions);
    skill_avg = alchemist_selling_price_modifier_hook(TP);
    skill_avg = MAX(50,skill_avg);
    for (i = 0;i < sizeof(potions);i++)
	value += potions[i]->query_potion_value() * skill_avg / 100;
    do_pay(TP, value);
    map(potions, add_potion);
    save_potions();
    return 1;
}

/*
 * Function name : Do_pay
 * Arguments     : object player: Player to pay the money too.
 *               : int price:     The price in cc we are to pay the player
 * Description   : pays the player.
 */
void
do_pay(object player, int price)
{
    object gc, sc, cc;
    int g, s, c;

    g = price / 144;
    s = (price - (g * 144)) / 12;
    c = price - g * 144 - s * 12;
    cc = MONEY_MAKE_CC(c);
    if (g)
    {
	gc = MONEY_MAKE_GC(g);
	gc->move(TP, 1);
    }
    if (s)
    {
	sc = MONEY_MAKE_SC(s);
	sc->move(TP, 1);
    }
    if (c)
    {
	cc = MONEY_MAKE_CC(c);
	cc->move(TP, 1);
    }
    alchemist_pay_hook(MONEY_TEXT(({c, s, g, 0})));
}

/*
 * Function name : Do_list
 * Arguments     : str: the list we are interested in.
 * Description   : List the inventory of the alchemist
 * Returns       : 1/0
 */
int
do_list(string str)
{
    int i, price, price2, potion_amt, potion_amt2,wrap_count;
    string item_name, item_name2, potionname, potionname2, *potion_list, potion_type,list = "";


    if (!Save_file)
    {
	    ERROR("No potion save file found!!!");
    }

    if (!CAN_SEE_IN_ROOM(TO))
    {
        alchemist_room_dark_hook();
        return 1;
    }

    if (!CAN_SEE(TO, TP))
    {
        alchemist_no_see_hook();
        return 1;
    }

    if (!str)
    {
        notify_fail("List what, potions?\n");
        return 0;
    }

    potion_list = m_indexes(Potions);

    if (!sizeof(potion_list))
    {
        alchemist_no_potions_to_list_hook();
        return 1;
    }

    if (str == "potions" || str == "all potions")
    {
        alchemist_list_header_hook();
        potion_list = sort_array(potion_list);
        write("\t+----------------------------------------------+\n");
        write("\t|  Qty  Potion                     PC GC SC CC |\n");
//        write("Qty  Potion             PC GC SC CC\n");
//        write("--------------------------------------");
        write("\t|----------------------------------------------|\n");
        for (i = 0;i < sizeof(potion_list) ; i++)
        {
//left column
            potionname = potion_list[i];
            item_name = add_white_space(potionname);
            potion_amt = Potions[potionname][AMOUNT];
            price = Potions[potionname][PRICE];
//            i++;
            if (i>= sizeof(potion_list))
                break;
//right column
//            potionname2 = potion_list[i];
//            item_name2 = add_white_space(potionname2);
//            price2 = Potions[potionname2][PRICE];
//            potion_amt2 = Potions[potionname2][AMOUNT];
//            list = sprintf("%4d  %-=17s  %2d %2d %2d %2d |%4d  %-=17s  %2d %2d %2d %2d ",
//                potion_amt, item_name,
//                price / 1728, (price % 1728) / 144, (price % 144) / 12, price % 12,
//                potion_amt2, item_name2,
//                price2 / 1728, (price2 % 1728) / 144, (price2 % 144) / 12, price2 % 12);
            list = sprintf("\t| %4d  %-=25s  %2d %2d %2d %2d |",
                potion_amt, item_name,
                price / 1728, (price % 1728) / 144, (price % 144) / 12, price % 12);
            write(list + "\n");

        }
        write("\t+----------------------------------------------+\n");
	    return 1;

    }

    item_name = del_white_space(str);

    if (!pointerp(Potions[item_name]))
    {
        alchemist_no_potion_match_hook(str);
        return 1;
    }

        alchemist_found_potion_match_hook(str);
    return 1;
}

/****************************************************************************
    The functions below are hooks which will enable you to change how your
    Npc will react.  There is no need to redefine these but if you want your
    alchemist not to react like everyone elses then you probably will.
*****************************************************************************/

// General Hooks

void
alchemist_room_dark_hook()
{
    command("say Who is there?");
    command("say I can't see a blasted thing!");
}

void
alchemist_no_see_hook()
{
    command("say Who said that?");
    command("say How do you expect me to do business with someone I can't "+
      "even see?");
}

// Buying hooks

void
alchemist_buy_no_potion_hook(string potion_name)
{
    command("say I'm sorry but I have no "+potion_name+" in stock");
    command("say I shall have to gather some more "+potion_name+" later.");
}

void
alchemist_buy_too_many_hook(int amount)
{
    command("say I'm sorry buy you can only buy "+Maximum_buy+" potions "+
      "at one time.");
}

void
alchemist_buy_low_potion_hook(int amount)
{
    command("chuckle");
    command("say I'm sorry but I don't have "+amount+" of that potion in stock.");
}

void
alchemist_cant_pay_hook(int price)
{
    command("shake");
    command("say Do you think I'm giving these potions away for free?");
}

void
alchemist_give_potions_hook(object *order,object player)
{
    int i, flag;

    for (i = 0;i < sizeof(order);i++)
    {
	if (order[i]->move(player))
	{
	    flag = 1;
	    order[i]->move(ENV(player));
	}
    }
    if (flag)
	command("say Seems you can't carry all these potions, I'll place them "+
	  "on the "+(ENV(TO)->query_prop(ROOM_I_INSIDE) ? "floor" :
	    "ground")+" for you.");
}

void
alchemist_sold_last_potion_hook(string str)
{
    command("emote mutters something.");
    command("say That was my last "+str+"!");
    command("say I suppose I should go out looking for some more.");
}

//  Selling hooks

void
alchemist_no_potions_to_sell_hook(object obj)
{

    command("hmm");
    command("say What was it you wanted to sell me again?");
    command("say I only want to buy potions from you.");
}

void
alchemist_max_sell_hook()
{
    command("say I only can purchase "+Maximum_sell+" potions at a time.");
    command("say My poor brain can't handle any more than that.");
}

void
alchemist_sold_hook(object *potions)
{
    command("say I shall pay you handsomely for these potions.");
    command("emote places "+COMPOSITE_DEAD(potions)+" in a pouch.");
}

int
alchemist_selling_price_modifier_hook(object player)
{
    return (player->query_skill(SS_TRADING) +
      player->query_skill(SS_HERBALISM)) / 2;
}

void
alchemist_pay_hook(string text)
{
    TP->catch_msg(QCTNAME(TO)+" hands you "+text+" and completes the "+
      "transaction.\n");
}

// Listing hooks

void
alchemist_no_potions_to_list_hook()
{
    command("say I'm sorry but I'm all out of potions at the moment.");
    command("frown");
}

void
alchemist_list_header_hook()
{
    command("hmm");
    command("say This is what all I have in stock at the moment.\n");
}

void
alchemist_no_potion_match_hook(string str)
{
    command("think");
    command("say I can't find "+str+" anywhere in my stock.");
}

void
alchemist_found_potion_match_hook(string str)
{
    string item_name;

    item_name = del_white_space(str);
    command("say I have "+Potions[item_name][AMOUNT]+" "+str+" in stock.");
    command("say The going price for one "+str+" is "+
      Potions[item_name][PRICE]+" copper coins.");
}

// Herbalist idenfity hooks

void
alchemist_not_potion_hook(object ob, object player)
{
    command("say I do not care for anything but potions!");
    switch(random(4))
    {
    case 0:
	command("say Why should I care about a silly "+ob->query_name()+"?");
	break;
    case 1:
	command("say I am too busy to be disturbed with "
	  +LANG_PWORD(ob->query_name())+", "+player->query_race_name()+".");
	break;
    case 2:
	command("say I am a alchemist, "+player->query_race_name()+
	  ", not a stupid pawnshop owner!");
	break;
    case 3:
	command("say This is of no interest to me, "+
	  ((player->query_gender() == G_MALE) ? "mister" : "madam")+".");
	break;
    }
    if (!command("give "+OB_NAME(ob)+" to "+player->query_real_name()))
	command("drop "+OB_NAME(ob));
}

void
alchemist_give_potion_back_hook(object potion, object player)
{
    command("say Please wait till I am finished with this other potion, "+
      ((player->query_gender() == G_MALE) ? "sir" : "my lady")+".");
    if (!command("give "+OB_NAME(potion)+" to "+player->query_real_name()))
	command("drop "+OB_NAME(potion));
}


void
alchemist_identify_potion_hook(object potion, object player)
{
    string id_str, find_str;

    say(QCTNAME(TO)+" looks closely at "+LANG_THESHORT(potion)+".\n");
    command("think");
    switch(potion->query_id_diff()/10)
    {
        case 0:
        	command("chuckle");
        	id_str = "The least skilled can recognize this.";
        	break;
        case 1:
	        command("eyebrow .");
        	id_str = "This is a rather common potion.";
        	break;
        case 2:
	        command("smile .");
        	id_str = "Not to worry, this is often mistaken for another potion.";
        	break;
        case 3:
	        command("frown");
        	id_str = "I see this one in alot.";
        	break;
        case 4:
            command("smile");
            id_str = "Ahh, I can understand why you didn't recognize this one.";
            break;
        case 5:
            command("smile");
            id_str = "Oh my! This is hard to identify. Don't feel bad.";
            break;
        case 6:
            command("think");
            id_str = "You need exceptional skills to recognize this potion.";
            break;
        case 7:
            case 8:
            command("gasp");
            id_str = "Oh, this potion is one of the hardest to identify.";
            break;
        case 9:
            command("gasp");
            id_str = "This is astonishing! I can't believe it!";
            break;
        default:
            command("confused");
            id_str = "Impossible! Absolutely impossible! It just can't be...?!";
    }

    command("say "+id_str);

    switch(potion->query_find_diff())
    {
        case 0:
            command("laugh");
            find_str = "Ah...this is as common as water.";
            break;
        case 1:
            command("giggle");
            find_str = "Anyone with a little skill can find this this.";
            break;
        case 2:
            command("smirk");
            find_str = "This one is not so hard to find.";
            break;
        case 3:
            command("smile");
            find_str = "Interesting. Not everybody knows where to find this one.";
            break;
        case 4:
            command("smile");
            find_str = "Good work! This one is not easy to locate.";
            break;
        case 5:
            command("smile");
            find_str = "Ah! It seems you spent some time looking for this.";
            break;
        case 6:
            command("think");
            find_str = "Hmmm. I wonder where you found this one?";
            break;
        case 7:
            command("whistle");
            find_str = "You must have been quite lucky to find this potion!";
            break;
        case 8:
            command("gasp");
            find_str = "I am absolutely astonished! This is extremely rare!";
            break;
        case 9:
            command("gasp");
            find_str = "How can this be?? This is one of the rarest potions!";
            break;
        default:
            command("confused");
            find_str = "I cannot believe it! You have actually found it! I have only "+
            "read about this in old books of lore!";
        }

    command("say " + find_str);

    if (potion->do_id_check(TO))
	    command("say "+potion->query_id_long());
    else
	    command("say It is unknown to me what the effect of this "+potion->short()+" is.");

    if (!command("give "+OB_NAME(potion)+" to "+player->query_real_name()))
	    command("drop "+OB_NAME(potion));

    command("say I hope my information has been useful, "+
        ((player->query_gender()==G_MALE) ? "sir" : "mylady")+".");
    command((TO->query_gender() == G_MALE ? "bow" : "curstey"));
    gBusy = 0;
}
