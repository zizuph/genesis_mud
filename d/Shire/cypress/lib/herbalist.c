/*
 *   ~Shire/project/lib/herbalist.c
 *
 *   A inheritable file for herbalists npcs. Takes care of everything for you
 *   All you need to do is make your npc and configure by redefining the
 *   hooks supplied with this file.
 *
 *
 *   Copyright (C) Chad Richardson Apr 23, 1997
 *
 *   Revision history:
 *   Modified for Mysteria
 *   --Finwe may 2001
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
#include "/d/Shire/cypress/sys/defs.h"

//  Error Defines
#define ERROR_LOG   "herbalist"
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
#define DEBUG(s)    DEBUG_WHO->catch_msg("HERBALIST:  "+ s +"\n")
#else
#define DEBUG(s)
#endif

#define AMOUNT      0
#define PRICE       1
#define FILENAME    2
#define MAX_HERBS   40  /* Maxium number of herbs this npc will save */
#define MAX_BUY     10  /* Maxium number of herbs one can buy */
#define MAX_SELL    20  /* Maxium number of herbs one can sell */
#define NUM         sizeof(MONEY_TYPES)

// Prototypes
nomask void save_herbs();
nomask void add_herb(object herb);
nomask void restore_herbs();
nomask int  herb_filter(object ob);
int         do_buy(string str);
int         do_list(string str);
int         do_sell(string str);
void        do_pay(object player, int amount);
string      add_white_space(string str);
string      del_white_space(string str);
//  Hook Prototypes
void herbalist_room_dark_hook();
void herbalist_no_see_hook();
void herbalist_no_herbs_to_sell_hook();
void herbalist_max_sell_hook();
void herbalist_sold_hook(object *herbs);
void herbalist_pay_hook(string text);
void herbalist_no_herbs_to_list_hook();
void herbalist_list_header_hook();
void herbalist_no_herb_match_hook(string str);
void herbalist_found_herb_match_hook(string str);
void herbalist_buy_no_herb_hook(string herb_name);
void herbalist_buy_too_many_hook(int amount);
void herbalist_buy_low_herb_hook(int amount);
void herbalist_cant_pay_hook(int price);
void herbalist_give_herbs_hook(object *order,object player);
void herbalist_sold_last_herb_hook(string str);
void herbalist_not_herb_hook(object ob, object player);
void herbalist_give_herb_back_hook(object herb, object player);
void herbalist_identify_herb_hook(object herb, object player);
int  herbalist_selling_price_modifier_hook(object player);

// Global Vars
private mapping  Herbs = ([]);
string    Save_file; 
int       Maximum_herbs = MAX_HERBS, Maximum_sell  = MAX_SELL;
int       Maximum_buy   = MAX_BUY, gBusy = 0, gDry = 1, gId_herb = 0;

/*
 * Function name : Configure_herbalist
 * Arguments     : string filename: The filename for the save file.
 * Description   : Sets up and configures the trading and restores the 
 *                 Herbs mapping.
 *                 This function _MUST_ be in the create_*() of your
 *                 herbalist for it to work.
 */
nomask void
configure_herbalist(string filename)
{

    config_default_trade();
    set_money_give_out(({ 10000,   700,  10,  10 }));
    set_money_give_reduce(({  0,     0,   0,   0 }));

    Save_file = filename;
    restore_herbs();
}

/*
 * Function name : Init_herbalist
 * Description   : Initalizes the commands for players to use this herbalist
 *                 This function _MUST_ be in the init_living() of your
 *                 herbalist for it to work.
 */
nomask void
init_herbalist()
{
    add_action(do_sell, "sell");
    add_action(do_list, "list");
    add_action(do_buy,  "buy");
}

nomask void
init_herbalist_identify(object herb, object from)
{
    if (!objectp(from) || !objectp(herb)) 
	return;
    if (!gId_herb)
	return;
    if (!function_exists("create_herb",herb)) 
    {
	set_alarm(1.0,0.0,&herbalist_not_herb_hook(herb, from));
	return;
    }
    if (gBusy) 
    {
	set_alarm(1.0,0.0,&herbalist_give_herb_back_hook(herb, from));
	return;
    }
    gBusy = 1;
    set_alarm(5.0,0.0, &herbalist_identify_herb_hook(herb,from));
}

void
set_herbalist_id_herbs()
{
    this_object()->remove_prop(NPC_M_NO_ACCEPT_GIVE);
    gId_herb = 1;     
}

void
set_herbalist_dry_herbs()
{
    gDry = 1;
}

void
unset_herbalist_dry_herbs()
{
    gDry = 0;
}

/*
 * Function name : Set_max_herbs_kept
 * Arguments     : int amount:  The amount of herbs to be kept
 * Description   : sets the maximum limit of herbs that are kept by the
 *                 Herbalist
 */
void
set_max_herbs_kept(int amount)
{
    if (amount > 0)
	Maximum_herbs = amount;
}

/*
 * Function name : Set_max_buy
 * Arguments     : int amount:  The amount to set the maximum to
 * Description   : sets the maximium amount of herbs the player can buy at
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
 * Description   : sets the maximum amount of herbs a player can sell at 
 *                 one time
 */
void
set_max_sell(int amount)
{
    if (amount > 0)
	Maximum_sell = amount;
}

int
query_herb_list_size()
{
    return sizeof(m_indexes(Herbs));
}

string
query_herb_list()
{
    string herbname, str = "";
    int i;

    for (i = 0;i < sizeof(m_indexes(Herbs));i++)
    {
	herbname = m_indexes(Herbs)[i];
	str += Herbs[herbname][AMOUNT] + " of "+ herbname +" "+
	Herbs[herbname][FILENAME]+" at a cost of "+Herbs[herbname][PRICE]+
	" copper coins each.\n";
    }
    str += "\n";

    return str;
}

int
query_herbs_max_kept()
{
    return Maximum_herbs;
}

int
query_herbs_max_buy()
{
    return Maximum_buy;
}

int
query_herbs_max_sell()
{
    return Maximum_sell;
}


/*
 * Function name : Restore_herbs
 * Description   : restores the Herbs mapping from the Save_file.
 */
nomask private void
restore_herbs()
{
    setuid(); seteuid(getuid());
    if (!Save_file || !stringp(Save_file))
    {
	ERROR("No save file for the herbalist, Herbalist removed!!");
	TO->remove_object();
    }
    Herbs = restore_map(Save_file);
    if (!mappingp(Herbs))
	Herbs = ([ ]);
}

/*
 * Function name : Save_herbs
 * Description   : saves the Herbs mapping
 */
nomask private void
save_herbs()
{
    if (!Save_file || !stringp(Save_file))
    {
	ERROR("Unable to save the herb information, no save file.");
	return;
    }
    save_map(Herbs, Save_file);
}

/*
 * Function name : Add_herb
 * Arguments     : object herb: The herb we are currently looking at
 * Description   : adds a herb to the mapping and removes the herb object.
 */
nomask private void
add_herb(object herb)
{
    int number;
    string name;

    name = herb->query_herb_name();
    name = del_white_space(name);
    if (!pointerp(Herbs[name]))
    {
	Herbs[name] = ({1, herb->query_herb_value(), 
	  MASTER_OB(herb)});
    }
    else
    {
	if (MASTER_OB(herb) != Herbs[name][FILENAME])
	    ERROR(MASTER_OB(herb) + " already exists in mapping "+
	      "under a different filename, and was not added.");
	else
	{
	    number = Herbs[name][AMOUNT];
	    if (number < Maximum_herbs)
		Herbs[name][AMOUNT] = number + 1;
	}
    }

    herb->remove_object();
    // Hammer time!
    if (objectp(herb))
	SECURITY->do_debug("destroy",herb);
}

/*
 * Function name : Herb_filter
 * Arguments     : object ob: Some object
 * Description   : Filters non-herb objects from an array.
 * Returns       : 1 if a herb / 0 if not
 */
nomask int
herb_filter(object ob)
{
    if (!function_exists("create_herb",ob)) 
	return 0;
    if (!ob->query_herb_name() || !ob->query_herb_value()) 
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
 * Arguments     : What herb we want to buy and how many
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
	ERROR("No herb save file found!!");
    }
    if (!CAN_SEE_IN_ROOM(TO))
    {
	herbalist_room_dark_hook();
	return 1;
    }
    if (!CAN_SEE(TO, TP))
    {
	herbalist_no_see_hook();
	return 1;
    }
    if (!strlen(str))
    {
	notify_fail("Buy what?\n");
	return 0;
    }

    str = lower_case(str);
    if (str == "herbs")
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
    if (!pointerp(Herbs[item_name]))
    {
	herbalist_buy_no_herb_hook(str);
	return 1;
    }
    if (Herbs[item_name][AMOUNT] < amount)
    {
	herbalist_buy_low_herb_hook(amount);
	return 1;
    }
    if (amount > Maximum_buy)
    {
	herbalist_buy_too_many_hook(amount);
	return 1;
    }

    // Make sure the herb is loaded.
    Herbs[item_name][FILENAME]->load_me();
    if (!find_object(Herbs[item_name][FILENAME]))
    {
	command("hmm");
	command("say I'm sorry I can't find "+item_name+" anywhere.");
	command("say This is a definate bug please leave a bug report.");
	ERROR(Herbs[item_name][FILENAME] +" does not exist!");
	return 1;
    }

    price = Herbs[item_name][PRICE] * amount;
    if (sizeof(money_arr = pay(price)) == 1)
    {
	herbalist_cant_pay_hook(price);
	return 1;
    }

    coin_pay_text = text(exclude_array(money_arr, NUM, NUM*2-1));
    coin_get_text = text(exclude_array(money_arr, 0, NUM-1));     
    write("You pay the herbalist "+coin_pay_text+" for "+amount+
      " "+str+".\n");
    if (coin_get_text)
	write("You get " + coin_get_text + " back.\n");

    order = allocate(amount);
    for (i = 0; i < amount; i++)
    {
	order[i] = clone_object(Herbs[item_name][FILENAME]);
	if (gDry)
	    order[i]->force_dry();
	order[i]->start_decay();
    }

    Herbs[item_name][AMOUNT] -= amount;
    herbalist_give_herbs_hook(order, TP);
    if (Herbs[item_name][AMOUNT] == 0)
    {
	Herbs = m_delete(Herbs, item_name);
	herbalist_sold_last_herb_hook(str);
    }
    save_herbs();
    return 1;   
}

/*
 * Function name : Do_sell
 * Arguments     : str: The herbs we want to sell.
 * Description   : The selling function
 * Returns       : 1/0
 */
int
do_sell(string str)
{
    object *herbs;
    int value, skill_avg, i;

    if (!Save_file)
    {
	ERROR("No herb save file found!!!");
    }
    if (!CAN_SEE_IN_ROOM(TO))
    {
	herbalist_room_dark_hook();
	return 1;
    }
    if (!CAN_SEE(TO, TP))
    {
	herbalist_no_see_hook();
	return 1;
    }
    if (!strlen(str))
    {
	notify_fail("Sell what?\n");
	return 0;
    }
    str = lower_case(str);

    // Find the herbs we are selling.

    herbs = FIND_STR_IN_OBJECT(str, TP);
    herbs = filter(herbs, &herb_filter());

    if (!sizeof(herbs))
    {
	herbalist_no_herbs_to_sell_hook();
	return 1;
    }

    if (sizeof(herbs) > Maximum_sell)
    {
	herbalist_max_sell_hook();
	return 1;
    }    
    herbalist_sold_hook(herbs);     
    skill_avg = herbalist_selling_price_modifier_hook(TP);
    skill_avg = MAX(50,skill_avg);
    for (i = 0;i < sizeof(herbs);i++)
	value += herbs[i]->query_herb_value() * skill_avg / 100;
    do_pay(TP, value);
    map(herbs, add_herb);
    save_herbs();
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
    herbalist_pay_hook(MONEY_TEXT(({c, s, g, 0})));
}

/*
 * Function name : Do_list
 * Arguments     : str: the list we are interested in.
 * Description   : List the inventory of the herbalist
 * Returns       : 1/0
 */
int
do_list(string str)
{ 
    int i;
    string item_name, herbname, *herb_list, list = "";

    if (!Save_file)
    {
	ERROR("No herb save file found!!!");
    }
    if (!CAN_SEE_IN_ROOM(TO))
    {
	herbalist_room_dark_hook();
	return 1;
    }
    if (!CAN_SEE(TO, TP))
    {
	herbalist_no_see_hook();
	return 1;
    }
    if (!str)
    {
	notify_fail("List what?\n");
	return 0;
    }
    herb_list = m_indexes(Herbs);
    if (!sizeof(herb_list))
    {
	herbalist_no_herbs_to_list_hook();
	return 1;    
    }
    if (str == "herbs" || str == "all herbs")
    {
	herbalist_list_header_hook();
	herb_list = sort_array(herb_list);
	for (i = 0;i < sizeof(herb_list) ; i++)
	{
	    herbname = herb_list[i];
	    item_name = add_white_space(herbname);
	    list += Herbs[herbname][AMOUNT]+"\t"+item_name+" for "+
	    Herbs[herbname][PRICE]+" copper coins each.\n";
	}
	TP->more(list);
	return 1;
    }
    item_name = del_white_space(str);
    if (!pointerp(Herbs[item_name]))
    {
	herbalist_no_herb_match_hook(str);
	return 1;
    }
    herbalist_found_herb_match_hook(str);
    return 1;
}

/****************************************************************************  
    The bellow functions are hooks which will enable you to change how your
    Npc will react.  There is no need to redefine these but if you want your
    herbalist not to react like everyone elses then you probably will.
*****************************************************************************/

// General Hooks

void
herbalist_room_dark_hook()
{
    command("say Who is there?");
    command("say I can't see a blasted thing!");
}

void 
herbalist_no_see_hook()
{
    command("say Who said that?");
    command("say How do you expect me to do business with someone I can't "+
      "even see?");
}

// Buying hooks

void
herbalist_buy_no_herb_hook(string herb_name)
{
    command("say I'm sorry but I have no "+herb_name+" in stock");
    command("say I shall have to gather some more "+herb_name+" later.");
}

void
herbalist_buy_too_many_hook(int amount)
{
    command("say I'm sorry buy you can only buy "+Maximum_buy+" herbs "+
      "at one time.");
}

void
herbalist_buy_low_herb_hook(int amount)
{
    command("chuckle");
    command("say I'm sorry but I don't have "+amount+" of that herb in stock.");
}

void
herbalist_cant_pay_hook(int price)
{
    command("shake");
    command("say Do you think I'm giving these herbs away for free?");
}

void
herbalist_give_herbs_hook(object *order,object player)
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
	command("say Seems you can't carry all these herbs, I'll place them "+
	  "on the "+(ENV(TO)->query_prop(ROOM_I_INSIDE) ? "floor" : 
	    "ground")+" for you.");
}

void 
herbalist_sold_last_herb_hook(string str)
{
    command("emote mutters something.");
    command("say That was my last "+str+"!");
    command("say I suppose I should go out looking for some more.");
}

//  Selling hooks

void 
herbalist_no_herbs_to_sell_hook()
{
    command("hmm");
    command("say What was it you wanted to sell me again?");
    command("say I only want to buy herbs from you.");
}

void 
herbalist_max_sell_hook()
{
    command("say I only can purchase "+Maximum_sell+" herbs at a time.");
    command("say My poor brain can't handle any more than that.");
}

void 
herbalist_sold_hook(object *herbs)
{
    command("say I shall pay you handsomely for these herbs.");
    command("emote places "+COMPOSITE_DEAD(herbs)+" in a pouch.");
}

int
herbalist_selling_price_modifier_hook(object player)
{
    return (player->query_skill(SS_TRADING) + 
      player->query_skill(SS_HERBALISM)) / 2;
}

void 
herbalist_pay_hook(string text)
{
    TP->catch_msg(QTNAME(TO)+" hands you "+text+" and completes the "+
      "transaction.\n");
}

// Listing hooks

void 
herbalist_no_herbs_to_list_hook()
{
    command("say I'm sorry but I'm all out of herbs at the moment.");
    command("frown");
}

void 
herbalist_list_header_hook()
{
    command("hmm");
    command("say This is what all I have in stock at the moment.");
}

void 
herbalist_no_herb_match_hook(string str)
{
    command("think");
    command("say I can't find "+str+" anywhere in my stock.");
}

void 
herbalist_found_herb_match_hook(string str)
{
    string item_name;

    item_name = del_white_space(str);
    command("say I have "+Herbs[item_name][AMOUNT]+" "+str+" in stock.");
    command("say The going price for one "+str+" is "+
      Herbs[item_name][PRICE]+" copper coins.");
}

// Herbalist idenfity hooks

void
herbalist_not_herb_hook(object ob, object player)
{
    command("say I do not care for anything but herbs!");
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
	command("say I am a herbalist, "+player->query_race_name()+
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
herbalist_give_herb_back_hook(object herb, object player)
{
    command("say Please wait till I am finished with this other herb, "+
      ((player->query_gender() == G_MALE) ? "sir" : "my lady")+".");
    if (!command("give "+OB_NAME(herb)+" to "+player->query_real_name()))
	command("drop "+OB_NAME(herb));
}

void
herbalist_identify_herb_hook(object herb, object player)
{
    string id_str, find_str;

    say(QCTNAME(TO)+" looks closely at "+LANG_THESHORT(herb)+".\n");
    command("think");
    switch(herb->query_id_diff()/10) 
    {
    case 0: 
	command("laugh");
	id_str = "Even the children can recognize this one.";
	break;
    case 1: 
	command("giggle");
	id_str = "Hmm...one of the easiest recognizable herbs.";
	break;
    case 2: 
	command("giggle");
	id_str = "Ahh..a nice one. Some people often mistake this for another.";
	break;
    case 3: 
	command("frown");
	id_str = "I've seen this one a lot. Easily mistaken though.";
	break;
    case 4: 
	command("smile");
	id_str = "Ah - I can't blame you for not recognizing this one.";
	break;
    case 5: 
	command("smile");
	id_str = "Exciting! This one is hard to tell from the Crimbul herb.";
	break;
    case 6: 
	command("think");
	id_str = "My dear friend - you need to be quite skilled to identify this one.";
	break;
    case 7: 
	command("think");
	id_str = "Oh! Can it really be...? Ah...yes it is.";
	break;
    case 8: 
	command("gasp");
	id_str = "By the Holy Beard of Eru!! This is one of the most difficult herbs!";
	break;
    case 9: 
	command("gasp");
	id_str = "Oh dear. Not even I am sure about this....but..it must be.";
	break;
    default: 
	command("confused");
	id_str = "Impossible! Absolutely impossible! It just can't be...?!";
    }
    command("say "+id_str);
    switch(herb->query_find_diff()) 
    {
    case 0: 
	command("laugh");
	find_str = "Ah..this is as normal as ordinary grass.";
	break;
    case 1: 
	command("giggle");
	find_str = "This one is quite a usual sight.";
	break;
    case 2: 
	command("giggle");
	find_str = "Not so hard to find.";
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
	find_str = "Ah! I guess you spent some time looking for this one!";
	break;
    case 6: 
	command("think");
	find_str = "Hmmm. I wonder where you found this one?";
	break;
    case 7: 
	command("whistle");
	find_str = "You must have been quite lucky to find this herb!";
	break;
    case 8: 
	command("gasp");
	find_str = "I am absolutely astonished! This is extremely rare!";
	break;
    case 9: 
	command("gasp");
	find_str = "How can this be?? I have only seen this herb about twice in my life!";
	break;
    default: 
	command("confused");
	find_str = "I cannot believe it! You have actually found it! I have only "+
	"read about this in old books of herblore!";
    }
    command("say " + find_str);
    if (herb->do_id_check(TO))
	command("say "+herb->query_id_long());
    else 
	command("say It is unknown to me what the effect of this "+herb->short()+" is.");
    if (!command("give "+OB_NAME(herb)+" to "+player->query_real_name()))
	command("drop "+OB_NAME(herb));
    command("say I hope my information has been useful, "+
      ((player->query_gender()==G_MALE) ? "sir" : "mylady")+".");
    command((TO->query_gender() == G_MALE ? "bow" : "curstey"));
    gBusy = 0;
}
