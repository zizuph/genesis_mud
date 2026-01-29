/*
 *   Based on ~Shire/lib/herbalist.c
 *
 *   A inheritable file for gemist npcs. Takes care of everything for you
 *   All you need to do is make your npc and configure by redefining the
 *   hooks supplied with this file.
 *
 *
 *   Copyright (C) Chad Richardson Apr 23, 1997
 *
 *   Revision history:
 *
 * Palmer added query_file() Mar 2003
 *
 * Updated display and added column herb display
 * -- Finwe, Oct 2003
 *
 * Converted over to a Gemist 
 * -- Finwe, Sept 2016
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

#define AMOUNT      0
#define PRICE       1
#define FILENAME    2
#define MAX_GEMS    40  /* Maxium number of gems this npc will save */
#define MAX_BUY     10  /* Maxium number of gems a player can buy */
#define MAX_SELL    20  /* Maxium number of gems a player can sell */
#define NUM         sizeof(MONEY_TYPES)

// Prototypes
nomask void save_gems();
nomask void restore_gems();
nomask int  gem_filter(object ob);
int         do_buy(string str);
int         do_list(string str);
int         do_sell(string str);
void        do_pay(object player, int amount);
string      add_white_space(string str);
string      del_white_space(string str);
//  Hook Prototypes
void gemist_room_dark_hook();
void gemist_no_see_hook();
void gemist_no_gems_to_sell_hook();
void gemist_max_sell_hook();
void gemist_sold_hook(object *gems);
void gemist_pay_hook(string text);
void gemist_no_gems_to_list_hook();
void gemist_list_header_hook();
void gemist_no_gem_match_hook(string str);
void gemist_found_gem_match_hook(string str);
void gemist_buy_no_gem_hook(string gem_name);
void gemist_buy_too_many_hook(int amount);
void gemist_buy_low_gem_hook(int amount);
void gemist_cant_pay_hook(int price);
void gemist_give_gems_hook(object *order,object player);
void gemist_sold_last_gem_hook(string str);
void gemist_not_gem_hook(object ob, object player);
void gemist_give_gem_back_hook(object gem, object player);
void gemist_identify_gem_hook(object gem, object player);
int  gemist_selling_price_modifier_hook(object player);
public string query_file();
    
// Global Vars
private mapping  Gems = ([]);
string    Save_file;
int       Maximum_gems = MAX_GEMS, Maximum_sell  = MAX_SELL;
int       Maximum_buy   = MAX_BUY, gBusy = 0, gDry = 1, gId_gem = 0;

/*
 * Function name : Configure_gemist
 * Arguments     : string filename: The filename for the save file.
 * Description   : Sets up and configures the trading and restores the 
 *                 Gems mapping.
 *                 This function _MUST_ be in the create_*() of your
 *                 gemist for it to work.
 */
nomask void
configure_gemist(string filename)
{
    config_default_trade();
    set_money_give_out(({ 10000,   700,  10,  10 }));
    set_money_give_reduce(({  0,     0,   0,   0 }));

    Save_file = filename;
    restore_gems();
}

/*
 * Function name : query_file
 * Description   : Returns gem mapping filename
 *
 */
public string
query_file()
{
    return Save_file;
}

/*
 * Function name : Init_gemist
 * Description   : Initalizes the commands for players to use this gemist
 *                 This function _MUST_ be in the init_living() of your
 *                 gemist for it to work.
 */
nomask void
init_gemist()
{
    add_action(do_sell, "sell");
    add_action(do_list, "list");
    add_action(do_buy,  "buy");
    
}

nomask void
init_gemist_identify(object gem, object from)
{
    if (!objectp(from) || !objectp(gem)) 
	return;
    if (!gId_gem)
	return;
    if (!function_exists("create_gems",gem)) 
    {
	set_alarm(1.0,0.0,&gemist_not_gem_hook(gem, from));
	return;
    }
    if (gBusy) 
    {
	set_alarm(1.0,0.0,&gemist_give_gem_back_hook(gem, from));
	return;
    }
    gBusy = 1;
    set_alarm(5.0,0.0, &gemist_identify_gem_hook(gem, from));
}

void
set_gemist_id_gems()
{
    this_object()->remove_prop(NPC_M_NO_ACCEPT_GIVE);
    gId_gem = 1;     
}

/*
 * Function name : Set_max_gems_kept
 * Arguments     : int amount:  The number of gems to be kept
 * Description   : sets the maximum limit of gems that are kept by the
 *                 Gemistt
 */
void
set_max_gems_kept(int amount)
{
    if (amount > 0)
	Maximum_gems = amount;
}

/*
 * Function name : Set_max_buy
 * Arguments     : int amount:  The amount to set the maximum to
 * Description   : sets the maximium amount of gems the player can buy at
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
 * Description   : sets the maximum amount of gems a player can sell at 
 *                 one time
 */
void
set_max_sell(int amount)
{
    if (amount > 0)
	Maximum_sell = amount;
}

int
query_gem_list_size()
{
    return sizeof(m_indexes(Gems));
}

string
query_gem_list()
{
    string gemname, str = "";
    int i;

    for (i = 0;i < sizeof(m_indexes(Gems));i++)
    {
	gemname = m_indexes(Gems)[i];
	str += Gems[gemname][AMOUNT] + " of "+ gemname +" "+
	Gems[gemname][FILENAME]+" at a cost of "+Gems[gemname][PRICE]+
	" copper coins each.\n";
    }
    str += "\n";

    return str;
}

int
query_gems_max_kept()
{
    return Maximum_gems;
}

int
query_gems_max_buy()
{
    return Maximum_buy;
}

int
query_gems_max_sell()
{
    return Maximum_sell;
}


/*
 * Function name : Restore_gems
 * Description   : restores the Gems mapping from the Save_file.
 */
nomask private void
restore_gems()
{
    setuid(); seteuid(getuid());
    if (!Save_file || !stringp(Save_file))
    {
	TO->remove_object();
	return;
    }
    Gems = restore_map(Save_file);
    if (!mappingp(Gems))
	Gems = ([ ]);
}

/*
 * Function name : Save_gems
 * Description   : saves the Gems mapping
 */
nomask private void
save_gems()
{
    if (!Save_file || !stringp(Save_file))
    {
	return;
    }
    save_map(Gems, Save_file);
}

/*
 * Function name : Add_gem
 * Arguments     : object gem: The gem we are currently looking at
 * Description   : adds a gem to the mapping and removes the gem object.
 */
nomask private void
add_gem(object gem)
{
    int number = gem->num_heap();
    string name;

    name = del_white_space(gem->query_gem_name());
    if (!pointerp(Gems[name]))
    {
	Gems[name] = ({ number, gem->query_gem_value(), MASTER_OB(gem)});
    }
    else
    {
	if (MASTER_OB(gem) == Gems[name][FILENAME])
	{
	    Gems[name][AMOUNT] = min(Gems[name][AMOUNT] + number, Maximum_gems);
	}
    }

    gem->remove_split_heap();
}

/*
 * Function name : Herb_filter
 * Arguments     : object ob: Some object
 * Description   : Filters non-gem objects from an array.
 * Returns       : 1 if a gem / 0 if not
 */
nomask int
gem_filter(object ob)
{
    if (!function_exists("create_gems",ob)) 
	return 0;
    if (!ob->query_gem_name() || !ob->query_gem_value()) 
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
 * Arguments     : What gem we want to buy and how many
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

    if (!CAN_SEE_IN_ROOM(TO))
    {
        gemist_room_dark_hook();
        return 1;
    }
    if (!CAN_SEE(TO, TP))
    {
        gemist_no_see_hook();
        return 1;
    }
    if (!strlen(str))
    {
	notify_fail("Buy what?\n");
	return 0;
    }

    str = lower_case(str);

    if (str == "gems")
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
    
    if (!pointerp(Gems[item_name]))
    {
        notify_fail("That gem is not in stock.\n");
        return 0;
	//gemist_buy_no_gem_hook(str);
	//return 1;
    }

    if (Gems[item_name][AMOUNT] < amount)
    {
        gemist_buy_low_gem_hook(amount);
        return 1;
    }

    if (amount > Maximum_buy)
    {
        gemist_buy_too_many_hook(amount);
        return 1;
    }

    // Make sure the gem is loaded.
    Gems[item_name][FILENAME]->load_me();

    if (!find_object(Gems[item_name][FILENAME]))
    {
        command("hmm");
        command("say I'm sorry I can't find "+item_name+" anywhere.");
        command("say This is a definite bug; please leave a bug report.");
        return 1;
    }

    price = Gems[item_name][PRICE] * amount;
    if (sizeof(money_arr = pay(price)) == 1)
    {
        gemist_cant_pay_hook(price);
        return 1;
    }

    coin_pay_text = text(exclude_array(money_arr, NUM, NUM*2-1));
    coin_get_text = text(exclude_array(money_arr, 0, NUM-1));     
    write("You pay the gemist "+coin_pay_text+" for "+amount+
      " "+str+".\n");
    if (coin_get_text)
    	write("You get " + coin_get_text + " back.\n");

    order = allocate(amount);

    for (i = 0; i < amount; i++)
    {
    	order[i] = clone_object(Gems[item_name][FILENAME]);
    }

    Gems[item_name][AMOUNT] -= amount;
    gemist_give_gems_hook(order, TP);

    if (Gems[item_name][AMOUNT] == 0)
    {
        Gems = m_delete(Gems, item_name);
        gemist_sold_last_gem_hook(str);
    }

    save_gems();
    return 1;   
}

/*
 * Function name : Do_sell
 * Arguments     : str: The gems we want to sell.
 * Description   : The selling function
 * Returns       : 1/0
 */
int
do_sell(string str)
{
    object *gems;
    int value, skill_avg, i;

    if (!CAN_SEE_IN_ROOM(TO))
    {
        gemist_room_dark_hook();
        return 1;
    }

    if (!CAN_SEE(TO, TP))
    {
        gemist_no_see_hook();
        return 1;
    }

    if (!strlen(str))
    {
        notify_fail("Sell what?\n");
        return 0;
    }

    str = lower_case(str);

    // Find the gems we are selling.
    gems = FIND_STR_IN_OBJECT(str, TP);
    gems = filter(gems, &gem_filter());

    if (!sizeof(gems))
    {
        gemist_no_gems_to_sell_hook();
        return 1;
    }

    if (sizeof(gems) > Maximum_sell)
    {
        gemist_max_sell_hook();
        return 1;
    }

    gemist_sold_hook(gems);     
    skill_avg = gemist_selling_price_modifier_hook(TP);
    skill_avg = MAX(50,skill_avg);

    for (i = 0;i < sizeof(gems);i++)
    	value += gems[i]->query_gem_value() * gems[i]->num_heap() * skill_avg / 100;
    
    do_pay(TP, value);
    map(gems, add_gem);
    save_gems();
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

    gemist_pay_hook(MONEY_TEXT(({c, s, g, 0})));
}

/*
 * Function name : Do_list
 * Arguments     : str: the list we are interested in.
 * Description   : List the inventory of the gemist
 * Returns       : 1/0
 */
int
do_list(string str)
{
    int i, price, price2, gem_amt, gem_amt2;
    string item_name, item_name2, gemname, gemname2, *gem_list, gem_type,list = "";

    if (!CAN_SEE_IN_ROOM(TO))
    {
        gemist_room_dark_hook();
        return 1;
    }

    if (!CAN_SEE(TO, TP))
    {
        gemist_no_see_hook();
        return 1;
    }

    if (!str)
    {
        notify_fail("List what?\n");
        return 0;
    }

    // allows the gemist to be based in a normal store room
    if (str == "equipment")
    {
       return 0;
    }

    gem_list = m_indexes(Gems);

    if (!sizeof(gem_list))
    {
        gemist_no_gems_to_list_hook();
        return 1;
    }

    if (str == "gems" || str == "all gems")
    {
        gemist_list_header_hook();
        gem_list = sort_array(gem_list);
        write(" Qty  Gem               PC GC SC CC |");
        write(" Qty  Gem               PC GC SC CC\n");
        write("--------------------------------------");
        write("-------------------------------------\n");
        for (i = 0;i < sizeof(gem_list) ; i++)
    	{
            //left column
            gemname = gem_list[i];
            item_name = add_white_space(gemname);
            gem_amt = Gems[gemname][AMOUNT];
            price = Gems[gemname][PRICE];
            i++;
            if (i>= sizeof(gem_list))
            {
                list = sprintf("%4d  %-=17s  %2d %2d %2d %2d |",
                    gem_amt, item_name,
                    price / 1728, (price % 1728) / 144, (price % 144) / 12, price % 12);
                write(list + "\n");
                break;
            }

            //right column
            gemname2 = gem_list[i];
            item_name2 = add_white_space(gemname2);
            price2 = Gems[gemname2][PRICE];
            gem_amt2 = Gems[gemname2][AMOUNT];
            list = sprintf("%4d  %-=17s  %2d %2d %2d %2d |%4d  %-=17s  %2d %2d %2d %2d ",
                gem_amt, item_name,
                price / 1728, (price % 1728) / 144, (price % 144) / 12, price % 12,
                gem_amt2, item_name2,
                price2 / 1728, (price2 % 1728) / 144, (price2 % 144) / 12, price2 % 12);

            write(list + "\n");

	    }
    	return 1;
    }

    item_name = del_white_space(str);

    if (!pointerp(Gems[item_name]))
    {
        gemist_no_gem_match_hook(str);
        return 1;
    }
    
    gemist_found_gem_match_hook(str);
    return 1;
}

/****************************************************************************  
    The functions below are hooks which will enable you to change how your
    Npc will react.  There is no need to redefine these but if you want your
    gemist not to react like everyone elses then you probably will.
*****************************************************************************/

// General Hooks

void
gemist_room_dark_hook()
{
    command("say Who is there?");
    command("say It suddenly went dark and I can't see anything!");
}

void 
gemist_no_see_hook()
{
    command("say Who said that?");
    command("say How do you expect me to do business with someone I can't "+
      "even see?");
}

// Buying hooks

void
gemist_buy_no_gem_hook(string gem_name)
{
    command("say I'm sorry but I have no "+gem_name+" in stock");
    command("say I shall have to gather some more "+gem_name+" later.");
}

void
gemist_buy_too_many_hook(int amount)
{
    command("say I'm sorry buy you can only buy "+Maximum_buy+" gems "+
      "at one time.");
}

void
gemist_buy_low_gem_hook(int amount)
{
    command("chuckle");
    command("say I'm sorry but I don't have "+amount+" of that gem in stock.");
}

void
gemist_cant_pay_hook(int price)
{
    command("shake");
    command("say Do you think I'm giving these gems away for free?");
}

void
gemist_give_gems_hook(object *order,object player)
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
	command("say Seems you can't carry all these gems, I'll place them "+
	  "on the "+(ENV(TO)->query_prop(ROOM_I_INSIDE) ? "floor" : 
	    "ground")+" for you.");
}

void 
gemist_sold_last_gem_hook(string str)
{
    command("emote mutters something.");
    command("say That was my last "+str+"!");
    command("say I suppose I should go out looking for some more.");
}

//  Selling hooks

void 
gemist_no_gems_to_sell_hook()
{
    command("hmm");
    command("say What was it you wanted to sell me again?");
    command("say I only want to buy gems from you.");
}

void 
gemist_max_sell_hook()
{
    command("say I only can purchase "+Maximum_sell+" gems at a time.");
    command("say My poor brain can't handle any more than that.");
}

void 
gemist_sold_hook(object *gems)
{
    command("say I shall pay you handsomely for these gems.");
    command("emote places "+COMPOSITE_DEAD(gems)+" in a pouch.");
}

int
gemist_selling_price_modifier_hook(object player)
{
    return (player->query_skill(SS_TRADING) + 
      player->query_skill(SS_APPR_VAL)) / 2;
}

void 
gemist_pay_hook(string text)
{
    TP->catch_msg(QCTNAME(TO)+" hands you "+text+" and completes the "+
      "transaction.\n");
}

// Listing hooks

void 
gemist_no_gems_to_list_hook()
{
    command("say I'm sorry but I'm all out of gems at the moment.");
    command("frown");
}

void 
gemist_list_header_hook()
{
    command("hmm");
    command("say This is what all I have in stock at the moment.");
}

void 
gemist_no_gem_match_hook(string str)
{
    command("think");
    command("say I can't find "+str+" anywhere in my stock.");
}

void 
gemist_found_gem_match_hook(string str)
{
    string item_name;

    item_name = del_white_space(str);
    command("say I have "+Gems[item_name][AMOUNT]+" "+str+" in stock.");
    command("say The going price for one "+str+" is "+
      Gems[item_name][PRICE]+" copper coins.");
}

// Herbalist idenfity hooks

void
gemist_not_gem_hook(object ob, object player)
{
    command("say I do not care for anything but gems!");
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
	command("say I am a gemist, "+player->query_race_name()+
	  ", not a stupid pawnshop owner!"); 
	break;
    case 3: 
	command("say This is of no interest to me, "+
	  ((player->query_gender() == G_MALE) ? "Sir" : "Milady")+"."); 
	break;
    }
    if (!command("give "+OB_NAME(ob)+" to "+player->query_real_name()))
	command("drop "+OB_NAME(ob));
}

void
gemist_give_gem_back_hook(object gem, object player)
{
    command("say Please wait till I am finished with this other gem, "+
      ((player->query_gender() == G_MALE) ? "Sir" : "Milady")+".");
    if (!command("give "+OB_NAME(gem)+" to "+player->query_real_name()))
	command("drop "+OB_NAME(gem));
}

void
gemist_identify_gem_hook(object gem, object player)
{
    string id_str, find_str;

    say(QCTNAME(TO)+" looks closely at "+LANG_THESHORT(gem)+".\n");
    command("think");
    switch(gem->query_id_diff()/10) 
    {
        case 0: 
           command("laugh");
            id_str = "Even young ones can easily recognize this gem!.";
            break;
        case 1: 
        command("giggle");
            id_str = "This is one of the most recognizable gems.";
            break;
        case 2: 
            command("giggle");
            id_str = "Some less experienced travellers mistake this gem for another one.";
            break;
        case 3: 
            command("frown");
            id_str = "I see this gem all the time, but most travellers easily misidentify it.";
            break;
        case 4: 
            command("smile");
            id_str = "I can see why you werent able to identify this gem.";
            break;
        case 5: 
            command("smile");
            id_str = "This is exciting! It is hard to tell from similar gems.";
            break;
        case 6: 
            command("think");
            id_str = "My dear friend, you need better skills to identify this gem.";
            break;
        case 7: 
            command("think");
            id_str = "Oh! Can it really be...? Ah...yes it is.";
            break;
        case 8: 
            command("gasp");
            id_str = "Wow! This is incredible! This is one of the most difficult gems to find!";
            break;
        case 9: 
            command("gasp");
            id_str = "Oh dear. I'm not sure about this, but it must be.";
            break;
        default: 
            command("confused");
            id_str = "Impossible! Absolutely impossible! It just can't be ...?!?";
    }

    command("say "+id_str);

    switch(gem->query_find_diff()) 
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
	find_str = "You must have been quite lucky to find this gem!";
	break;
    case 8: 
	command("gasp");
	find_str = "I am absolutely astonished! This is extremely rare!";
	break;
    case 9: 
	command("gasp");
	find_str = "How can this be?? I have only seen this gem about twice in my life!";
	break;
    default: 
	command("confused");
	find_str = "I cannot believe it! You have actually found it! I have only "+
	"read about this in old books of gemlore!";
    }

    command("say " + find_str);

    if (gem->do_id_check(TO))
    	command("say "+gem->query_id_long());
    else 
	    command("say It is unknown to me what the effect of this "+gem->short()+" is.");

    if (!command("give "+OB_NAME(gem)+" to "+player->query_real_name()))
    	command("drop "+OB_NAME(gem));
    
    command("say I hope my information has been useful, "+
      ((player->query_gender()==G_MALE) ? "Sir" : "Milady")+".");
    
    command((TO->query_gender() == G_MALE ? "bow" : "curstey"));
    gBusy = 0;
}
