/* -*- Mode: C -*-
 *
 * trade/houses/s-09.c
 *
 * Skippern 20(c)01
 *
 * An inn in Dol Amroth.
 */
#include "../../defs.h"

inherit DOL_STD + "inside";
inherit "/lib/trade";

#include <macros.h>
#include <money.h>

#define MY_PRICES    ({ 3, 10, 15, 30, 150, 5, 15, 25, 50, 80 })
#define FOOD        DOL_OBJ + "food/"
#define DRINK       DOL_OBJ + "drink/"
#define NUM         sizeof(MONEY_TYPES)

/* GLobale variables */
static string    Innkeeper_name, Innkeeper_Name;
       int       price, number;
       string    ware;
       object    file, ob;

/* Prototypes */
static int       can_afford(int price, string ware);
       string    price_long();
public void      set_innkeeper_name(string name);
public int       do_buy(string str);

/*
 * Function name:    create_inside
 * Description  :    Creates the room (according to lib/inside.c)
 */
void
create_inside()
{
    set_short("inside an inn");
    set_long("This is a large hall filled with tables and chairs. " +
	     "By the west wall a large counter stands, and behind " +
	     "it some maidens run back and fort serving food and " +
	     "drinks. By some of the table some people are playing " +
	     "various games such as bridge or chess, while some " +
	     "older men have a discussion about the growing shadow " +
	     "at another. A bouncer patroles the hall to control " +
	     "that nothing get damaged.\n");

    add_item( ({ "price", "price list", "menu", "list" }), 
	"Try reading it.\n");

    add_cmd_item( ({ "price", "price list", "menu", "list" }), ({ "read", 
        "study" }), &price_long() );

    config_default_trade();
    set_money_give_max(2000);
    set_money_give_out(( { 2000, 700, 50, 4 } ));
    set_money_give_reduce(( { 1, 1, 1, 1 } ));
    set_innkeeper_name("The maiden");

    reset_room();

    clone_object(DOL_OBJ + "doors/s-09-inn-door")->move(this_object());
}

/*
 * Function name:    init
 * Description  :    Adds verbs for the players to use
 */
void
init()
{
    ::init();
    add_action(do_buy, "buy");
    add_action(do_buy, "order");
}

/*
 * Function name:    reset_room
 * Description  :    This function is run every once in a while, so we can
 *                   have objects return, variables reset or npc's cloned
 *                   here.
 */
void
reset_room()
{
}

/*
 * Function name:    price_long
 * Description  :    Prints the menu.
 * Usage        :    in create_room()
 *                   add_item(( { "list", "menu" }), price_long());
 *                   add_cmd_item(( { "list", "menu" }), "read" price_long());
 */
string
price_long()
{
    return (
"/\\-------------------------------------------------------------------/\\ \n"+
"| \\_____________________________________________________________________\\\n"+
"| <>                                                               <> |  \n" +
"|       Today's menu:                                                 |  \n" +
"|                                                                     |  \n" +
"|   Beverages:                                                        |  \n" +
"|       Water                 -            " + MY_PRICES[0] + " copper                   |  \n" +
"|       Mead                  -           " + MY_PRICES[1] + " copper                   |  \n" +
"|       Ale                   -           " + MY_PRICES[2] + " copper                   |  \n" +
"|       Wine                  -           " + MY_PRICES[3] + " copper                   |  \n" +
"|       Whiskey               -          " + MY_PRICES[4] + " copper                   |  \n" +
"|                                                                     |  \n" +
"|   Provisions:                                                       |  \n" +
"|       Vegitable stew        -            " + MY_PRICES[5] + " copper                   |  \n" +
"|       Fish soup             -           " + MY_PRICES[6] + " copper                   |  \n" +
"|       Meat soup             -           " + MY_PRICES[7] + " copper                   |  \n" +
"|       Fried fish            -           " + MY_PRICES[8] + " copper                   |  \n" +
"|       Fried ham             -           " + MY_PRICES[9] + " copper                   |  \n" +
"|                                                                     |  \n" +
"|                                                                     |  \n" +
//"|  You can `order mead for gold' to pay with the coinage you desire.  |  \n" +
//"| Or you can specify the numbre of items by `order 3 mead'.           |  \n" +
"|  <>                                                             <>  |  \n" +
" \\                                                                     \\ \n" +
"  +---------------------------------------------------------------------+\n" +
"\n" );
}


/*
 * Function name:    do_buy
 * Description  :    Try to let a player buy an item.
 * Arguments    :    string -- describing how to pay and get change
 *
 */
public int
do_buy(string str)
{
    object item;
    string item_name;
    string  pay_type, get_type;
    
    if (!strlen(str))
    {
        notify_fail("Buy what?\n");
        return 0;
    }

    if (sscanf(str,"%s for %s and get %s",item_name,pay_type,get_type) != 3)
    {
        get_type = "";
	if (sscanf(str,"%s for %s",item_name,pay_type) != 2)
	{
	    pay_type = "";
	    item_name = str;
	}
    }
    switch (str)
    {
    case "water":
    case "waters":
        if (can_afford(MY_PRICES[0], "water"))
	{
	    item = clone_object(DRINK + "water.c");
	    say(QCTNAME(TP) + " orders some water.\n");
	    if (item->move(TP))
	    {
	        write("You cannot carry anymore!\n" +
		    Innkeeper_Name + " drops the " + item->short() + " on " +
		    "the counter.\n");
		item->move(TO);
	    } else write(Innkeeper_Name+" hand you the "+item->short()+".\n");
	}
	break;
    case "mead":
    case "meads":
        if (can_afford(MY_PRICES[1], "mead"))
	{
	    item = clone_object(DRINK + "mead.c");
	    say(QCTNAME(TP) + " orders some mead.\n");
	    if (item->move(TP))
	    {
	      write("You cannot carry anymore!\n" +
		  Innkeeper_Name + " drops the " + item->short() + " on the " +
		  "counter.\n");
	      item->move(TO);
	    } else write(Innkeeper_Name+" hand you the "+item->short()+".\n");
	}
	break;
    case "ale":
    case "ales":
        if (can_afford(MY_PRICES[2], "ale"))
	{
	    item = clone_object(DRINK + "ale.c");
	    say(QCTNAME(TP) + " orders some ale.\n");
	    if (item->move(TP))
	    {
		write("You cannot carry anymore!\n" + 
		      Innkeeper_Name + " drops the " + item->short() + " on the " +
		      "counter.\n");
		item->move(TO);
	    } else write(Innkeeper_Name+" hand you the "+item->short()+".\n");
	}
	break;
    case "wine":
        if (can_afford(MY_PRICES[3], "wine"))
	{
	    item = clone_object(DRINK + "wine.c");
	    say(QCTNAME(TP) + " orders some wine.\n");
	    if (item->move(TP))
	    {
		write("You cannot carry anymore!\n" +
		      Innkeeper_Name + " drops the " + item->short() + " on the " +
		      "counter.\n");
		item->move(TO);
	    } else write(Innkeeper_Name+" hand you the "+item->short()+".\n");
	}
	break;
    case "whiskey":
        if (can_afford(MY_PRICES[4], "whiskey"))
        {
	    item = clone_object(DRINK + "whiskey.c");
	    say(QCTNAME(TP) + " orders some whiskey.\n");
	    if (item->move(TP))
            {
	        write("You cannot carry anymore!\n" +
		      Innkeeper_Name + " drops the " + item->short() + " on the " +
		      "counter.\n");
		item->move(TO);
            } else write(Innkeeper_Name+" hand you the "+item->short()+".\n");
        }
	break;
    case "vegitable":
    case "vegitables":
    case "stew":
    case "vegitable stew":
        if (can_afford(MY_PRICES[5], "stew"))
        {
	    item = clone_object(FOOD + "stew.c");
	    say(QCTNAME(TP) + " orders some vegitable stew.\n");
	    if (item->move(TP))
            {
	        write("You cannot carry anymore!\n" +
		      Innkeeper_Name + " drops the " + item->short() + " on the " +
		      "counter.\n");
		item->move(TO);
            } else write(Innkeeper_Name+" hand you the "+item->short()+".\n");
        }
	break;
    case "fish":
    case "soup":
    case "fish soup":
        if (can_afford(MY_PRICES[6], "fish soup"))
        {
	    item = clone_object(FOOD + "f-soup.c");
	    say(QCTNAME(TP) + " orders some fish soup.\n");
	    if (item->move(TP))
            {
	        write("You cannot carry anymore!\n" +
		      Innkeeper_Name + " drops the " + item->short() + " on the " +
		      "counter.\n");
		item->move(TO);
            } else write(Innkeeper_Name+" hand you the "+item->short()+".\n");
        }
	break;
    case "meat":
    case "meat soup":
      if (can_afford(MY_PRICES[7], "meat soup"))
        {
	  item = clone_object(FOOD + "m-soup.c");
	  say(QCTNAME(TP) + " orders some meat soup.\n");
	  if (item->move(TP))
            {
	      write("You cannot carry anymore!\n" +
		    Innkeeper_Name + " drops the " + item->short() + " on the " +
		    "counter.\n");
	      item->move(TO);
            } else write(Innkeeper_Name+" hand you the "+item->short()+".\n");
        }
      break;
    case "fried fish":
    case "fries":
      if (can_afford(MY_PRICES[8], "fried fish"))
        {
	  item = clone_object(FOOD + "f-fish.c");
	  say(QCTNAME(TP) + " orders some fried fish.\n");
	  if (item->move(TP))
            {
	      write("You cannot carry anymore!\n" +
		    Innkeeper_Name + " drops the " + item->short() + " on the " +
		    "counter.\n");
	      item->move(TO);
            } else write(Innkeeper_Name+" hand you the "+item->short()+".\n");
        }
      break;
    case "fried meat":
    case "ham":
    case "fried ham":
      if (can_afford(MY_PRICES[3], "fried ham"))
        {
	  item = clone_object(FOOD + "f-ham.c");
	  say(QCTNAME(TP) + " orders some fried ham.\n");
	  if (item->move(TP))
            {
	      write("You cannot carry anymore!\n" +
		    Innkeeper_Name + " drops the " + item->short() + " on the " +
		    "counter.\n");
	      item->move(TO);
            } else write(Innkeeper_Name+" hand you the "+item->short()+".\n");
        }
      break;
    default:
        NFN(Innkeeper_name + " says: We don't have any "+str+" on the menu.\n");
	return 0;
	break;
    }
    return 1;
}

/*
 * Function name:    can_afford
 * Description  :    Tests if the player are able to pay for the goods he
 *                   orders.
 * Arguments    :    int price - The prace of the goods
 *                   string ware - What goods
 * Returns      :    1 - can afford
 *                   0 - can't afford
 */
static int
can_afford(int price, string ware)
{
    int    *money_arr;
    string  pay_type, get_type, coin_pay_text, coin_get_text;

    if (sizeof(money_arr = pay(price, TP,pay_type,0,0,get_type)) == 1)
    {
        if (money_arr[0] == 2)
	{
	    tell_room(TO,break_string(
                "The innkeeper says: You haven't got any "+pay_type+
                " coins, honoured "+QNAME(TP)+".\n",75));
	    return 0;
	}
	if (money_arr[0] == 1)
	{
	    tell_room(TO,break_string(
	        "The innkeeper says: You haven't got enough "+pay_type+
		" coins to pay for the "+ware+", honoured "+QNAME(TP)+".\n",75));
	    return 0;
	}
        else
	{
	    tell_room(TO,break_string(
	        "The innkeeper says: When you have enough money for it, " +
		"I would be glad to serve you "+ware+".\n",75));
	    return 0;
	}
    }
    coin_pay_text = text(exclude_array(money_arr, NUM, NUM*2-1));
    coin_get_text = text(exclude_array(money_arr, 0, NUM-1));
    write("You order a "+ware+" and pay "+coin_pay_text+".\n");
    if (coin_get_text)
        write(Innkeeper_Name+" hands you "+coin_get_text+" back in change.\n");
    return 1;
}

/*
 * Function name:    set_innkeeper_name
 * Description  :    Sets the values of Innkeeper_name and Innkeeper_Name.
 * Arguments    :    string name - the name of the innkeeper
 */
public void
set_innkeeper_name(string name)
{
    if ( strlen(name) )
    {
        Innkeeper_name = LOW(name);
	Innkeeper_Name = CAP(name);
    }
}
