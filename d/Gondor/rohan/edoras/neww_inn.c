/*
 *  The Sleeping Stallion
 *  
 *  copied from the Seven Stars Inn
 *
 *  created by unknown (Elessar?)
 *  modified for The Sleeping Stallion by Olorin on 6-jan-93
 *  April 30, 2004, Tigerlily: updated references for
 *      ranger recode
 */
#pragma strict_types

inherit "/d/Gondor/std/room.c";
inherit "/lib/trade";

#include <macros.h>
#include <money.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#ifndef NEW_RANGERS_OPEN
#define STAND_DIR   "/d/Gondor/common/guild/obj/"
#endif

#ifdef NEW_RANGERS_OPEN
#define  STAND_DIR  "/d/Gondor/guilds/rangers/obj/"
#endif

#define MY_PRICES ({ 9, 15, 40, 100, 10, 24, 50, 240, 550, 144})
#define NUM sizeof(MONEY_TYPES)

static int    can_afford(int price, string ware);
public int     check_combat();
static string price_long();
       void   reset_room();

static object  Funohed, 
	       Fastred, 
	       Citizen;

void
create_gondor()
{
   set_short("the Sleeping Stallion");
   set_long(BSN(
      "You are in the Sleeping Stallion, a local inn. Here you can eat and "
    + "drink to your heart's delight. Some of the tables here are occupied by "
    + "rohirrim farmers or by traders, who came to Edoras for business, and "
    + "now are feasting on the excellent meals offered in this inn. By the "
    + "north wall is a counter. In front of it several rohirrim men are "
    + "standing, drinking beer. Behind the counter, the innkeeper is working. "
    + "On the wooden floor lies a rug, which has seen better times. It is "
    + "worn out, covered with dirt, pipe ashes and holes. A few lamps are "
    + "hanging from the ceiling, creating a nice atmosphere. To the left of "
    + "the counter the are stairs leading upstairs to a room where one can "
    + "stay for the night. On the wall behind the counter is a pricelist and "
    + "menu. To the south an archway leads into a small dining area filled "
    + "with tables"));
   add_item("rug", "The rug was once beautiful and red, but now it is grey "
    + "and full of holes.\n");
   add_item(({"table","tables","chair","chairs"}),
      "Most of the tables are free, but some are occupied by the rohirrim\n" 
	+ "customers of this inn.\n");
   add_item("counter", BSN(
      "Above the wooden counter is a lamp and a shelf. On the shelf are "
    + "several brands of liquor. Behind the counter is the innkeeper of the "
    + "Sleeping Stallion. On the wall behind the counter there hangs a "
    + "pricelist and menu."));
   add_item(({"innkeeper","barkeeper","bartender"}), break_string(
      "The innkeeper is a very corpulent, almost fat, rohirrim man. He does "
	+ "not seem to work much, but surprisingly, everyone is served promptly "
	+ "in this inn. From the frequent glances that he keeps casting at you, "
	+ "you conclude that he expects you to order something.\n",70));
   add_item(({"pricelist","list","prices","menu"}), price_long());
   add_exit(EDORAS_DIR + "stairs2","west",0,1);
   add_exit(EDORAS_DIR + "hotelr","up", check_combat,2);
   add_prop(ROOM_I_INSIDE,1);  /* This is a real room */
   config_default_trade();
   set_money_give_max(2000);
   set_money_give_out(({ 2000, 700, 50, 4}));
   set_money_give_reduce(({1,1,1,1})); 
   clone_object(EDORAS_DIR + "rooms/inndoorin")->move(TO);
   reset_room();
}

public void
reset_room()
{
    Funohed = clone_npc(Funohed, EDORAS_DIR + "npc/funohed");
    Citizen = clone_npc(Citizen, EDORAS_DIR + "npc/inncitizen");
    Fastred = clone_npc(Fastred, EDORAS_DIR + "npc/fastred");

    if (objectp(present(Fastred, TO)))
	Fastred->command("unlock door with key");
}

public int
check_keeper()
{
    if (objectp(present("innkeeper")))
	return 1;
    else 
	return 0;
}

public int
no_keeper()
{
    NF("There is no innkeeper here, so you can't do that!\n");
    return 1;
}

static string
price_long() 
{
   return (
      "The pricelist reads:\n\n"
    + "DRINKS:\n"
    + "   Golden Ale            ...  " + MY_PRICES[0] + " copper coins\n"
    + "   Rohan Beer            ...  " + MY_PRICES[1] + " copper coins\n"
    + "   Wine from Ithilien    ...  " + MY_PRICES[2] + " copper coins\n"
    + "   Whiskey from Rohan    ...  " + MY_PRICES[3] + " copper coins\n\n"
    + "HOT MEALS:\n"
    + "   Porridge              ...  " + MY_PRICES[4] + " copper coins\n"
    + "   Vegetable stew        ...  " + MY_PRICES[5] + " copper coins\n"
    + "   Bacon and beans       ...  " + MY_PRICES[6] + " copper coins\n"
    + "   Pheasant              ...  " + MY_PRICES[7] + " copper coins\n"
    + "   Stag steak            ...  " + MY_PRICES[8] + " copper coins\n\n"
    + "ROOMS:\n"
    + "   Key for a room        ...  " + MY_PRICES[9] + " copper coins\n\n");
}

public int
do_read(string str) 
{
    if (!strlen(str))
	return 0;
    if (str == "pricelist" || str == "list" || str == "prices" || str == "menu")
    {
	write(price_long());
	return 1;
    }
    return 0;
}

public int
do_buy(string str) 
{
    object item;
    string item_name;
    string  pay_type, get_type;

    if (!strlen(str))
	return 0;
    if (!check_keeper())
    {
	no_keeper();
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
    case "golden":
    case "ale":
    case "golden ale":
	if (can_afford(MY_PRICES[0], "ale"))
	{
	    item = clone_object(STAND_DIR + "ale");
	    say(QCTNAME(TP) + " orders a mug of golden ale.\n");
	    if (item->move(TP))
	    {
		write("You cannot carry that much!\n" +
		      "The innkeeper drops the " + item->short() + " on a table.\n");
		item->move(TO);
	    }
	}
	break;
    case "beer":
	if (can_afford(MY_PRICES[1],"beer"))
	{
	    item = clone_object(STAND_DIR + "beer");
	    say(QCTNAME(TP) + " orders a mug of Rohan beer.\n");
	    if (item->move(TP))
	    {
		write("You cannot carry that much!\n" +
		      "The innkeeper drops the " + item->short() + " on a table.\n");
		item->move(TO);
	    }
	}
	break;
    case "wine":
	if (can_afford(MY_PRICES[2],"wine"))
	{
	    item = clone_object(STAND_DIR + "wine");
	    say(QCTNAME(TP) + " orders some wine.\n");
	    if (item->move(TP))
	    {
		write("You cannot carry that much!\n" +
		    "The innkeeper drops the " + item->short() + " on a table.\n");
		item->move(TO);
	    }
	}
	break;
    case "whiskey":
	if (can_afford(MY_PRICES[3],"whiskey"))
	{
	    item = clone_object(STAND_DIR + "whiskey");
	    say(QCTNAME(TP) + " orders a whiskey.\n");
	    if(item->move(TP))
	    {
		write("You cannot carry that much!\n" +
		    "The innkeeper drops the " + item->short() + " on a table.\n");
		item->move(TO);
	    }
	}
	break;
    case "porridge":
	if (can_afford(MY_PRICES[4],"porridge"))
	{
	    item = clone_object(STAND_DIR + "porridge");
	    say(QCTNAME(TP)+" buys a bowl of hot porridge.\n");
	    if(item->move(TP))
	    {
		write("You cannot carry that much!\n" +
		    "The innkeeper drops the " + item->short() + " on a table.\n");
		item->move(TO);
	    }
	}
	break;
    case "stew":
    case "vegetable stew":
    case "vegetable":
	if (can_afford(MY_PRICES[5],"vegetable stew"))
	{
	    item = clone_object(STAND_DIR + "stew");
	    say(QCTNAME(TP)+" orders a hot stew of vegetables.\n");
	    if(item->move(TP))
	    {
		write("You cannot carry that much!\n" +
		    "The innkeeper drops the " + item->short() + " on a table.\n");
		item->move(TO);
	    }
	}
	break;
    case "beans":
    case "bacon":
    case "beans and bacon":
	if (can_afford(MY_PRICES[6],"beans and bacon"))
	{
	    item = clone_object(STAND_DIR + "beans");
	    say(QCTNAME(TP)+" buys a hot meal of bacon and beans.\n");
	    if(item->move(TP))
	    {
		write("You cannot carry that much!\n" +
		    "The innkeeper drops the " + item->short() + " on a table.\n");
		item->move(TO);
	    }
	}
	break;
    case "pheasant":
	if (can_afford(MY_PRICES[7],"pheasant"))
	{
	    item = clone_object(STAND_DIR + "pheasant");
	    say(QCTNAME(TP)+" buys a hot meal of fried pheasant.\n");
	    if(item->move(TP))
	    {
		write("You cannot carry that much!\n" +
		    "The innkeeper drops the " + item->short() + " on a table.\n");
		item->move(TO);
	    }
	}
	break;
    case "stag":
    case "steak":
    case "stag steak":
	if (can_afford(MY_PRICES[8],"stag steak"))
	{
	    item = clone_object(STAND_DIR + "steak");
	    say(QCTNAME(TP)+" orders a large hot meal of stag steak.\n");
	    if(item->move(TP))
	    {
		write("You cannot carry that much!\n" +
		    "The innkeeper drops the " + item->short() + " on a table.\n");
		item->move(TO);
	    }
	}
	break;
	case "room":
    case "key":
    case "single room":
    case "night":
	if (can_afford(MY_PRICES[9],"room"))
	{
	    item = clone_object(EDORAS_DIR + "obj/hotel_key");
	    say(QCTNAME(TP)+" orders a single room to spend the night "
		+ "in Edoras.\n");
	    if (item->move(TP))
		item->move(TP, 1);
	    write("The innkeeper gives you the key to the room. Don't lose it!\n");
	}
	break;
    default:
	NFN("The innkeeper says: We don't have that on the menu.");
	return 0;
	break;
    }
    return 1;
}

/* Test if TPas more money on him than the price */
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
check_time(string str)
{
    if (!check_keeper())
	return ::check_time(str);
    write("You ask the innkeeper what time it is.\n");
    say(QCTNAME(TP)+" asks the innkeeper what time it is.\n",TP);
//    tell_room(TO,"The innkeeper says: It is about "+qhour()+" o'clock in the "+tod()+".\n");
    tell_room(TO,"The innkeeper says: It is about "+qstime()+".\n");
    return 1;
}

public void
init()
{
    ::init();
    add_action(do_read, "read");
    add_action(do_buy,  "buy");
    add_action(do_buy,  "order");
}

public int
check_combat()
{
    object  enemy;

    if (objectp(enemy = TP->query_attack()))
    {
	write(enemy->query_The_name(TP) + " stops you!\n");
	return 1;
    }
    return 0;
}

