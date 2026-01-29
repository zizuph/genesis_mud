/* 
 *  I (Boromir) stole this file from : 
 *  The Tavern in Minas Tirith. 
 * 
 *
 * This is the Inn in Thornlin, "The Lost Pig"
 * Coded by: Boromir
 * Last edited: Apr. 28 1995
 * Mod log: minor fixes, Olorin, 5-may-1995
 */

#include "/d/Gondor/defs.h"
inherit (COMMON_DIR + "room");
inherit "/lib/trade";

#include <language.h>
#include <macros.h>
#include <money.h>
#include <stdproperties.h>

#include "locals.h"

#define PELAR_OBJ_DIR (PELAR_DIR + "obj/")
#define MY_PRICES ({ 12, 24, 72, 24, 48, 72 })
#define NUM sizeof(MONEY_TYPES)

string  price_long();
int     can_afford(int price, string ware);

string  pay_type,
get_type,
coin_pay_text,
coin_get_text;
int    *money_arr,
nr;

void
create_room()
{
    set_short("inside 'The Lost Pig'");
    set_long(BSN("This room is somewhat dark, with a thick and heavy air. "
	+ "The only light sources you can see are small lamps which "
	+ "have been placed upon tables around the room. Chairs "
	+ "surround the tables, and in the middle of the western wall "
	+ "is a counter, above which hangs both a pricelist and a menu."));

    add_item("air","You have a hard time breathing in here, due to "+
      "the smoky air in here.\n");
    add_item(({"lamps","small lamps","light sources"}), "On the tables "+
      "you see some small brass oil lamps which light up the room.\n");
    add_item("tables","These tables are made of oak and seem to be quite "+
      "durable.\n"+
      "All the tables are taken by other customers.\n"); 
    add_item("chairs","The chairs are made of cheap wood, and are rather "+
      "old.\n"+
      "All the chairs are taken by other customers.\n");
    add_item(({"wall","walls","western wall"}),"The walls are barren "+
      "and made out of stone.\n");
    add_item("counter","The counter is made of oak, and is rather small. "+ 
      "A number of glasses have been turned upside-down, and now "+ 
      "rest upon the counter surface.\n");
    add_item("glasses","The glasses has different sizes, some for ales "+
      "some for beers and others again for wine.\n");
    add_item(({"pricelist","list","prices","menu"}), "@@price_long");


    add_prop(ROOM_I_INSIDE,1);  /* This is a real room */
    config_default_trade();
    set_money_give_max(2000);
    set_money_give_out(({ 2000, 700, 50, 4}));
    set_money_give_reduce(({1,1,1,1})); 

    clone_object(OBJ_DIR + "inndoora")->move(TO);
}

void
init()
{
    ::init();
    add_action("do_read","read",0);
    add_action("do_buy","buy",0);
    add_action("do_buy","order",0);
}

int
do_read(string str) 
{
    if (!str || str == "")
	return 0;
    if (str == "pricelist" || str == "list" || str == "prices" || str == "menu")
    {
	write(price_long());
	return 1;
    }
    return 0;
}

string
price_long() 
{
    return (
      "The pricelist reads:\n\n"
      + "DRINKS:\n"
      + "   Golden Ale           ...  " + MY_PRICES[0] + " copper coins\n"
      + "   Home brew            ...  " + MY_PRICES[1] + " copper coins\n"
      + "   Lebennin wine        ...  " + MY_PRICES[2] + " copper coins\n"
      + "\n\nHOT MEALS:\n"
      + "   Ham                  ...  " + MY_PRICES[3] + " copper coins\n"
      + "   Bacon and beans      ...  " + MY_PRICES[4] + " copper coins\n"
      + "   Pork chops           ...  " + MY_PRICES[5] + " copper coins\n\n");
}

int
do_buy(string str) 
{
    object item;
    string item_name;
    if (!str || str == "")
	return 0;
    if (sscanf(str,"%s for %s and get %s",item_name,pay_type,get_type) != 3)
    {
	get_type = "";
	if (sscanf(str,"%s for %s",item_name,pay_type) != 2)
	{
	    pay_type = "";
	    item_name = str;
	}
    }
    if (str == "golden" || str == "ale" || str == "golden ale")
    {
	if (can_afford(MY_PRICES[0],"ale"))
	{
	    item = clone_object(PELAR_OBJ_DIR + "ale");
	    if(item->move(TP))
	    {
		write("You cannot carry that much!\n");
		return 1;
	    }
	    say(QCTNAME(TP) + " orders a mug of golden ale.\n");
	}
	return 1;
    }
    if (str == "beer" || str == "brew" || str == "home brew")
    {
	if(can_afford(MY_PRICES[1],"beer"))
	{
	    item = clone_object(OBJ_DIR + "beer");
	    if(item->move(TP))
	    {
		write("You cannot carry that much!\n");
		return 1;
	    }
	    say(QCTNAME(TP) + " orders home brew.\n");
	}
	return 1;
    }
    if (str == "wine")
    {
	if(can_afford(MY_PRICES[2],"wine"))
	{
	    item = clone_object(PELAR_OBJ_DIR + "wine");
	    if(item->move(TP))
	    {
		write("You cannot carry that much!\n");
		return 1;
	    }
	    say(QCTNAME(TP) + " orders some wine.\n");
	}
	return 1;
    }
    if (str == "ham")
    {
	if(can_afford(MY_PRICES[3],"ham"))
	{
	    item = clone_object(OBJ_DIR + "ham");
	    if(item->move(TP))
	    {
		write("You cannot carry that much!\n");
		return 1;
	    }
	    say(QCTNAME(TP)+" orders some ham.\n");
	}
	return 1;
    }
    if (str == "beans" || str == "bacon" || str == "beans and bacon")
    {
	if(can_afford(MY_PRICES[4],"beans and bacon"))
	{
	    item = clone_object(PELAR_OBJ_DIR + "beans");
	    if(item->move(TP))
	    {
		write("You cannot carry that much!\n");
		return 1;
	    }
	    say(QCTNAME(TP)+" buys a hot meal of bacon and beans.\n");
	}
	return 1;
    }
    if (str == "pork chops" || str == "chops")
    {
	if(can_afford(MY_PRICES[5],"pork chops"))
	{
	    item = clone_object(OBJ_DIR + "porkchops");
	    if(item->move(TP))
	    {
		write("You cannot carry that much!\n");
		return 1;
	    }
	    say(QCTNAME(TP)+" orders pork chops.\n");
	}
	return 1;
    }
    notify_fail("The innkeeper says: We don't have that on the menu.\n");
    return 0;
}

/* Test if TP has more money on him than the price */
int
can_afford(int price, string ware) 
{
    if (sizeof(money_arr = pay(price, TP,pay_type,0,0,get_type)) == 1)
    {
	if (money_arr[0] == 2)
	{
	    tell_room(this_object(),break_string(
		"The innkeeper says: You haven't got any "+pay_type+       
		" coins, honoured "+QNAME(TP)+".\n",75));       
	    return 0;
	}
	if (money_arr[0] == 1)
	{
	    tell_room(this_object(),break_string(
		"The innkeeper says: You haven't got enough "+pay_type+
		" coins to pay for the "+ware+", honoured "+QNAME(TP)+".\n",75));
	    return 0;
	}
	else
	{
	    tell_room(this_object(),break_string(
		"The innkeeper says: When you have enough money for it, I would "+
		"be glad to serve you "+ware+".\n",75));
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

int
chk_time()
{
    write("You ask the keeper what time it is.\n");
    say(QCTNAME(TP)+" asks the keeper what time it is.\n",TP);
    tell_room(TO,"The keeper says: It is about "+qhour()+" o'clock in the "+tod()+".\n");
    return 1;
}

