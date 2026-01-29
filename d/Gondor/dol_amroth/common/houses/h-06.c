/*
 * common/houses/h-06.c
 *
 * Skippern 20(c)02
 *
 * An inn in Dol Amroth.
 */
#include "../../defs.h"

inherit DOL_STD + "inside";
inherit "/lib/trade";

#include <macros.h>
#include <money.h>

#define MY_PRICES    ({ 3, 8, 10, 15, 30, 50, 80, 110, 150 })
#define DRINK        DOL_OBJ + "drink/"
#define NUM          sizeof(MONEY_TYPES)

#define RESET_SOUND ({ "A bar maiden sweaps some tables.", \
                       "A drunk tries his luck with the bar " +\
                       "maiden, and failes." })

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
    set_short("inside a tavern");
    set_long("This is a small hall filled with tables and chairs. " +
	     "By the south wall a large counter stands, and behind " +
	     "it a man stands serving  " +
	     "drinks. By some of the table some people are playing " +
	     "various games such as bridge or chess, while some " +
	     "older men have a discussion about the growing shadow " +
	     "at another.\n");

    add_item( ({ "price", "price list", "menu", "list" }), 
	"Try reading it.\n");
    add_item( ({ "man", "innkeeper", "bartender" }),
	      "A man wearing an apron full of stains.\n");
    add_item("counter", "The south wall is occupied by a large counter. " +
	     "Behind it a man stands juggeling bottles, or serving " +
	     "drinks as somebody would call it. The counter is made " +
	     "from redwood with brass edges.\n");
    add_item( ({ "table", "tables" }), "Scattered round the room are " +
	      "several tables. Their places looks like they have been " +
	      "left where they landed after somebody threw them into " +
	      "the room, which might be true. There are various forms " +
	      "of activeties on most of the tables. Some people " +
	      "discussing the growing shadow, and other playing " +
	      "various games like chess and bridge.\n");
    add_item( ({ "people", "men" }), "A group of people, mostly men " +
	      "hang round this place. Most of them are occupied with " +
	      "some sort of activities, such as plaing bridge or " +
	      "chess, or discussing politics or other important issues.\n");
    add_item("hall", "This small hall is filled with tables and chairs. " +
	     "By the south wall a large counter stands.\n");

    add_cmd_item( ({ "price", "price list", "menu", "list" }), ({ "read", 
        "study" }), &price_long() );

    config_default_trade();
    set_money_give_max(2000);
    set_money_give_out(( { 2000, 700, 50, 4 } ));
    set_money_give_reduce(( { 1, 1, 1, 1 } ));
    set_innkeeper_name("The innkeeper");

    reset_room();

    clone_object(DOL_OBJ + "doors/h-06-door")->move(this_object());
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
    tell_room(this_object(), one_of_list(RESET_SOUND)+"\n", 0, 0);
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
"|       Coffee                -            " + MY_PRICES[1] + " copper                   |  \n" +
"|       Mead                  -           " + MY_PRICES[2] + " copper                   |  \n" +
"|       Ale                   -           " + MY_PRICES[3] + " copper                   |  \n" +
"|       Wine, white           -           " + MY_PRICES[4] + " copper                   |  \n" +
"|       Wine, red             -           " + MY_PRICES[5] + " copper                   |  \n" +
"|       Gin                   -           " + MY_PRICES[6] + " copper                   |  \n" +
"|       Champaign             -          " + MY_PRICES[7] + " copper                   |  \n" +
"|       Whiskey               -          " + MY_PRICES[8] + " copper                   |  \n" +
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
	    }
	}
	break;
    case "caffee":
    case "coffee":
        if (can_afford(MY_PRICES[1], "coffee"))
	{
	    item = clone_object(DRINK + "caffee.c");
	    say(QCTNAME(TP) + " orders some coffee.\n");
	    if (item->move(TP))
	    {
	        write("You cannot carry anymore!\n" +
		    Innkeeper_Name + " drops the " + item->short() + " on " +
		    "the counter.\n");
		item->move(TO);
	    }
	}
	break;
    case "mead":
        if (can_afford(MY_PRICES[2], "mead"))
	{
	    item = clone_object(DRINK + "mead.c");
	    say(QCTNAME(TP) + " orders some mead.\n");
	    if (item->move(TP))
	    {
	        write("You cannot carry anymore!\n" +
		    Innkeeper_Name + " drops the " + item->short() + " on " +
		    "the counter.\n");
		item->move(TO);
	    }
	}
	break;
    case "ale":
        if (can_afford(MY_PRICES[3], "ale"))
	{
	    item = clone_object(DRINK + "ale.c");
	    say(QCTNAME(TP) + " orders some ale.\n");
	    if (item->move(TP))
	    {
	        write("You cannot carry anymore!\n" +
		    Innkeeper_Name + " drops the " + item->short() + " on " +
		    "the counter.\n");
		item->move(TO);
	    }
	}
	break;
    case "wine":
    case "white wine":
        if (can_afford(MY_PRICES[4], "white wine"))
	{
	    item = clone_object(DRINK + "wwine.c");
	    say(QCTNAME(TP) + " orders some white wine.\n");
	    if (item->move(TP))
	    {
	        write("You cannot carry anymore!\n" +
		    Innkeeper_Name + " drops the " + item->short() + " on " +
		    "the counter.\n");
		item->move(TO);
	    }
	}
	break;
    case "red wine":
        if (can_afford(MY_PRICES[5], "red wine"))
	{
	    item = clone_object(DRINK + "wine.c");
	    say(QCTNAME(TP) + " orders some red wine.\n");
	    if (item->move(TP))
	    {
	        write("You cannot carry anymore!\n" +
		    Innkeeper_Name + " drops the " + item->short() + " on " +
		    "the counter.\n");
		item->move(TO);
	    }
	}
	break;
    case "gin":
        if (can_afford(MY_PRICES[6], "gin"))
	{
	    item = clone_object(DRINK + "gin.c");
	    say(QCTNAME(TP) + " orders some gin.\n");
	    if (item->move(TP))
	    {
	        write("You cannot carry anymore!\n" +
		    Innkeeper_Name + " drops the " + item->short() + " on " +
		    "the counter.\n");
		item->move(TO);
	    }
	}
	break;
    case "champaign":
        if (can_afford(MY_PRICES[7], "champaign"))
	{
	    item = clone_object(DRINK + "champaign.c");
	    say(QCTNAME(TP) + " orders some champaign.\n");
	    if (item->move(TP))
	    {
	        write("You cannot carry anymore!\n" +
		    Innkeeper_Name + " drops the " + item->short() + " on " +
		    "the counter.\n");
		item->move(TO);
	    }
	}
	break;
    case "whiskey":
        if (can_afford(MY_PRICES[8], "whiskey"))
	{
	    item = clone_object(DRINK + "whiskey.c");
	    say(QCTNAME(TP) + " orders some whiskey.\n");
	    if (item->move(TP))
	    {
	        write("You cannot carry anymore!\n" +
		    Innkeeper_Name + " drops the " + item->short() + " on " +
		    "the counter.\n");
		item->move(TO);
	    }
	}
	break;
    default:
        NFN(Innkeeper_name + " says: That's not on the menu.\n");
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
        write("The innkeeper hands you "+coin_get_text+" back in change.\n");
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

void
enter_inv(object ob, object from)
{
    object task;
    string *places, tmp;
    int i;

    ::enter_inv(ob, from);

    if (task = present("I_do_quest_token.c", ob))
    {
	if (task->query_task() == DOL_Q_M_EXPLORE_TOWN)
	{
  	    tmp = task->query_visit();
	    places = explode(tmp, "::");
	    for (i = 0; i < sizeof(places); i++)
	    {
		if (places[i] == "tavern") return;
	    }
	    places += ({ "tavern" });
	    tmp = implode(places, "::");
	    task->set_visit(tmp);
	    task->set_part(task->query_part()+1);
	}
    }
}
