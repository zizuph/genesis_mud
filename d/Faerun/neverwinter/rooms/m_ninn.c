/*  /d/Faerun/neverwinter/rooms/m_ninn.c
*
*   By Thessius, 2020
* 
*/

#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include <terrain.h>
#include <macros.h>
#include <money.h>
#include <language.h>
#include "defs.h"

inherit BASE_NEWERW_INDOOR;

object key;

//Items for cloning
public string ninn_key = DEFAULT_DIR + "obj/ninn_key.c";
public string ninn_ale = DEFAULT_DIR + "obj/ninn_ale.c";
public string ninn_bread_cheese = DEFAULT_DIR + "obj/ninn_bread_cheese.c";


int
check_keyholders()
{
    if (!(key = present("_ninn_key_inn", this_player())))
    {
        write("You don't have the key you need to go upstairs!\n");

        return 1;
    }

    return 0;
}


void
create_neverw_room()
{
    set_long("Iron Flagon Inn.\n"
       +"The inn is jampacked with people of all races and ages. Most "
       +"patrons surround grand tables situated around a large circular "
       +"stage. Because of the opening of Neverwinter, the Inn's "
       +"proprieter has had to hire extra help, whom can be spotted "
       +"dashing to and fro, taking care of the customer's every needs. "
       +"A few of the tavern-goers are sitting in the rooms darkest "
       +"corners, giving anyone a look if they deemed them too close. "
       +"A bar is set ten feet away from the western wall, where even "
       +"more hired help work tirelessly to furfill the overwhelming "
       +"amount of orders, flying in at all times. Three menus hang from "
       +"the top of the bar. A staircase is on the opposite side of the "
       +"Inn, leading upstairs to the Inn's many rooms.\n");
    
    set_short("Iron Flagon Inn");
    
    add_prop(ROOM_I_LIGHT, 1);
    
    add_item(({"people" , "patrons" , "tavern-goers"}),
       "The occupants of the Inn range from the smallest Gnome to the "
       +"largest Minotaur. All of the patrons' purses and pouches were "
       +"full to the brim, overflowing with the coin they had procured "
       +"amidst their travels.\n");
       
    add_item(({"tables"}),
       "The tables are all draped with a snow white cloth. Each table "
       +"is decorated with a small vase set in the middle, containing a "
       +"single rose.\n");
       
    add_item(({"cloth" , "tablecloth"}),
       "The cloths are colored snow white, with a small label on each at "
       +"their corners. Touching the cloth gives you a sense of "
       +"serenity.\n");

    add_item(({"label"}),
       "The label reads: 'This Snow-White Tablecloth was produce by the "
       +"hands of Inelrain. Those of you who read this may find my shop "
       +"to the east of the eastern alleys.'\n");
       
    add_item(({"vase"}),
       "The vase was delicately crafted from clay gathered from the "
       +"bottom of the Neverwinter River.\n");
       
    add_item(({"stage"}),
       "The stage has been lifted from the floor of the Inn by only a "
       +"foot. This is where the Inn's owner sends the various "
       +"performers. The people in the Inn, if they deem the performance "
       +"worthy, throw their coins on the stage, laughing out loud as "
       +"whoever is performing scrambles to gather it all as quick as "
       +"possible.\n");
       
    add_item(({"help"}),
       "Those who have been hired to help with the running of the Inn "
       +"are primarily human. There is no set uniform, as they seem to "
       +"have only been told to wear the finest clothes they could. "
       +"Some of the women have taken this to a certain degree, as they "
       +"deliberately dress as little as they can, whilst still looking "
       +"decent, to prod money from the Inn's patrons.\n");
       
    add_item(({"corners"}),
       "Some of the Inn's patrons set themselves snugly in a dimly lit "
       +"corner, far away from the noise and excitement that takes place "
       +"in the middle of the Inn. In the closest corner are a few "
       +"gamblers, arguing over the outcome of a game. In the other "
       +"three, dark-clad men speak in hushed voices.\n");
       
    add_item(({"bar"}),
       "The bar is constantly being cleaned from the numerous drinks "
       +"spilt atop it. The hired help hurry behind it, quickly pouring "
       +"drinks for the parched travelers.\n");
    
    add_item(({"menu" , "menus"}),
       "The menus are labled from left to right: 'Food', 'Drink', "
       +"and 'Today's Special'.\n");
       
    add_item(({"left menu", "food", "food menu"}),
       "'The food in stock is as follows:'\n"
       +"Apple...          10cc\n"
       +"Clam Chowder...   30cc\n\n"
       +"Key to a room... 160cc\n"
       +"\n"
       +"You can only order a maximum of 20 items at a time.\n");
       
    add_item(({"middle menu", "drink", "drink menu"}),
       "'The drinks availiable for purchase are as follows:'\n"
       +"Iron Flagon Ale...    20cc\n"
       +"Iron Flagon Mead...   20cc\n"
       +"Iron Flagon Rum...    20cc\n"
       +"Poison Serpant Ale... 80cc\n");
       
    add_item(({"right menu", "special", "todays special"}),
       "Todays Special is:\n"
       +"placeholder.\n");

    reset_faerun_room();
        
    add_exit(ROOM_DIR + "n4.c", "west");
    add_exit(ROOM_DIR + "m_ninnu", "up", check_keyholders);
}


/*
 * Returns the failure message when a player cannot pay
 */
int inn_hook_cant_pay(int price)
{
    write("You haven't got enough money to pay for your order.\n");
    return 0;
}


/*
 * Returns the purchase message when a player buys an item
 */
int inn_hook_player_buys(int price)
{
    write("You place an order at the bar and pay " + price + " copper. "
          +"You quickly receive your order.\n");
    say(QCTNAME(this_player()) + " places an order at the bar.\n");
    return 0;
}


/*
 * Returns the failure message when a player uses a bad syntax
 */
int inn_hook_syntax_failure(string str)
{
    write("What would you like to buy?\n");
    return 0;
}


/*
 * Returns the failure message when a player orders too much
 */
int inn_hook_num_failure(int num)
{
    write("You cannot order more than 20 items at a time.\n");
    return 0;
}


/*
 * Function for ordering food
 */
int order(string str)
{
    string *words;
    int num, tmp, i, price;
    object ob;

    if (!str)
    {
        return inn_hook_syntax_failure(str);
    }

    words = explode(str, " ");
    num = 1;
    if(sizeof(words) > 1)
    {
        tmp = LANG_NUMW(words[0]);
        if (!tmp)
            sscanf(words[0], "%d", tmp);
        if (tmp > 0)
        {
            num = tmp;
            str = implode(words[1 .. sizeof(words)], " ");
        }
    }

    if (num > 20)
    {
      return inn_hook_num_failure(num);
    }

    switch(str)
    {
       /* case "water":
        case "waters":
        case "well":
        case "well water":
        case "well waters":
            ob = clone_object(sir_water);
            price = num * 10;
            break;*/
        case "ale":
        case "ales":
        case "siren's":
        case "siren's ale":
        case "siren's ales":
            ob = clone_object(ninn_ale);
            price = num * 12;
            break;
       /*case "grog":
        case "grogs":
        case "bay":
        case "martira":
        case "martira bay":
        case "martira grog":
        case "martira grogs":
        case "bay grog":
        case "bay grogs":
        case "martira bay grog":
        case "martira bay grogs":
            ob = clone_object(sir_grog);
            price = num * 72;
            break;*/
        /*case "sailor":
        case "sailors":
        case "angry":
        case "angries":
        case "angrys":
        case "angry sailor":
        case "angry sailors":
        case "the angry sailor":
        case "the angry sailors":
            ob = clone_object(sir_sailor);
            price = num * 100;
            break;*/
        case "key":
        case "keys":
        case "roomkey":
        case "room key":
            ob = clone_object(ninn_key);
            price = num * 100;
            break;
        case "bread":
        case "breads":
        case "cheese":
        case "cheeses":
        case "bread and cheese":
        case "bread and cheeses":
            ob = clone_object(ninn_bread_cheese);
            price = num * 25;
            break;
       /* case "beef":
        case "beefs":
        case "vegetable":
        case "vegetables":
        case "stew":
        case "stews":
        case "beef and vegetable":
        case "beef and vegetables":
        case "beef and vegetable stew":
        case "beef and vegetable stews":
            ob = clone_object(sir_stew);
            price = num * 80;
            break;
        case "grub":
        case "grubs":
        case "grub of the moment":
        case "grub of the moments":
        case "grubs of the moment":
        case "grubs of the moments":
            ob = clone_object(sir_grub);
            price = num * 160;
            break;*/
        default:
            return inn_hook_syntax_failure(str);
    }

    if(!MONEY_ADD(this_player(),-price))
    {
        inn_hook_cant_pay(price);
        return 1;
    }

    inn_hook_player_buys(price);
    ob->set_heap_size(num);
    ob->move(this_player(), 1);
    return 1;
}


/*
 * Function that allows the player to sit at a table or the bar
 */
int action_sit(string str)
{
    if(this_player()->query_prop("_sitting_at_ninn_bar"))
    {
        write("But you are already sitting by the bar!\n");
        return 1;
    }

    if(this_player()->query_prop("_sitting_at_ninn_table"))
    {
        write("But you are already sitting by the bar!\n");
        return 1;
    }

    if(str == "around table" | str == "around the table"
    | str == "at table" | str == "at the table"
    | str == "by table" | str == "by the table"
    | str == "table" | str == "chair around table"
    | str == "in chair around table" | str == "in a chair around the table"
    | str == "chair at table"
    |   str == "in chair at table" | str == "in a chair at the table"
    | str == "chair by table"
    | str == "in chair by table" | str == "in a chair by the table")
    {
        this_player()->catch_msg("You sit down in one of the rickety "
        +"chairs near the table in the corner.\n");
        say(QCTNAME(this_player()) + " sits down in one of the rickety "
        +"chairs near the table in the corner.\n");
        this_player()->add_prop("_sitting_at_ninn_table", 1);
        this_player()->add_prop(LIVE_S_EXTRA_SHORT," who is sitting near a "
        +"corner table");
        return 1;
    }

    if(str == "at bar" | str == "at the bar" | str == "by bar"
    | str == "by the bar" | str == "bar" | str == "chair at bar"
    | str == "in chair at bar" | str == "in a chair at the bar"
    | str == "chair by bar" | str == "in chair by bar"
    | str == "in a chair by the bar")
    {
        this_player()->catch_msg("You sit down in one of the "
        +"rickety chairs near the bar.\n");
        say(QCTNAME(this_player()) + " sits down in a rickety "
        +"chair near the bar.\n");
        this_player()->add_prop("_sitting_at_ninn_bar", 1);
        this_player()->add_prop(LIVE_S_EXTRA_SHORT," who is sitting "
        +"near the bar");
        return 1;
    }

    else
    {
        this_player()->catch_msg("Where would you like to sit? "
        +"By the bar or around the corner table?\n");
        return 1;
    }

    return 1;
}


/*
 * Function that allows the player to stand from a table or the bar
 */
int
action_stand(string str)
{
    if(str == "up")
    {
        if(this_player()->query_prop("_sitting_at_ninn_table"))
        {
            this_player()->catch_msg("You stand up and leave the table.\n");
            say(QCTNAME(this_player())+" stands up from the table.\n");
            this_player()->remove_prop("_sitting_at_ninn_table");
            this_player()->remove_prop(LIVE_S_EXTRA_SHORT);
            return 1;
        }

        if(this_player()->query_prop("_sitting_at_ninn_bar"))
        {
            this_player()->catch_msg("You stand up and leave the bar.\n");
            say(QCTNAME(this_player())+" stands up from the bar.\n");
            this_player()->remove_prop("_sitting_at_ninn_bar");
            this_player()->remove_prop(LIVE_S_EXTRA_SHORT);
            return 1;
        }
    }

    else
    {
        this_player()->catch_msg("Stand? Stand up?\n");
        return 1;
    }

    return 1;
}

/*
 * Function to cleanup props if a player leaves before standing
 */
void leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if(!objectp(to) || !objectp(ob))
      return;
                
    if(ob->query_prop("_sitting_at_ninn_table"))
    {
        ob->catch_msg("You stand up from the table before leaving.\n");
        say(QCTNAME(ob) + " stands up from the table before "
        +"leaving the inn.\n");
        ob->remove_prop(LIVE_S_EXTRA_SHORT);
        ob->remove_prop("_sitting_at_ninn_table");
    }

    if(ob->query_prop("_sitting_at_ninn_bar"))
    {
        ob->catch_msg("You stand up from the bar before leaving.\n");
        say(QCTNAME(ob) + " stands up from the bar before "
        +"leaving the inn.\n");
        ob->remove_prop(LIVE_S_EXTRA_SHORT);
        ob->remove_prop("_sitting_at_ninn_bar");
    }
}



void init()
{
    ::init();
    add_action(order, "buy");
    add_action(order, "order");
    add_action("action_sit", "sit");
    add_action("action_stand", "stand");
}


void
reset_faerun_room()
{
    set_searched(0);
}