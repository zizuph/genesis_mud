#include "defs.h"

inherit PARTY_BASE;
inherit "/lib/trade";

#include <money.h>

#define NUM sizeof(MONEY_TYPES) /* How many types of money do we use? */

object lily;

void
create_party_room()
{
    add_prop(ROOM_S_MAP_FILE, "party.txt");

    set_short("An enormous outdoor kitchen");
    set_long("You are standing before a grand outdoor kitchen, which "+
      "has been named the Breezy Field Inn. Dozens of hobbits can be seen "+
      "preparing (and eating) vast quantities of food. There is a lone hobbit "+
      "sitting at a table from which a menu hangs. To the east you see a "+
      "grand pavilion and to the southeast there is a small tent "+
      "serving as a post office.\n");
    add_item(({"kitchen","large kitchen","outdoor kitchen"}),
      "A multitude of pots and pans litter stoves and open fires, from "+
      "which the smell of roast mutton wafts to your nose.  "+
      "Hobbits are running about perparing food for the party goers.\n");
    add_item("menu","There are some readable words on it.\n");
    add_item("table",
      "This is a small ash table from which a hobbit sits at taking "+
      "peoples food orders.\n");

    add_exit(PARTY_DIR+"podium","east");
    add_exit(PARTY_DIR+"post","southeast");

    config_default_trade();  /* Set up the trading system */
    /* Copper Silver Gold Platinum  */
    set_money_give_out(   ({ 10000,    32,   2,    1 })); /* Max_pay   */
    set_money_give_reduce(({     0,     4,   2,    1 })); /* Threshold */

    reset_shire_room();
}

void
reset_shire_room()
{
    if (!lily)
    {
        lily = clone_object(PARTY_NPC+"lily");
        tell_room(TO,"A hoobit arrives at her kitchen.\n");
        lily->move(TO);
    }
}

void
init()
{
    ::init();
    add_action("do_order","order");
    add_action("do_order","buy");
    add_action("do_read","read");
}

int
do_read(string str)
{
    if (str != "menu" && str != "pricelist")
    {
        notify_fail("Read what? The menu maybe?\n");
        return 0;
    }

    setuid();  seteuid(getuid());
    READ(PARTY_DIR+"menu");
    return 1;
}

int
do_order(string str)
{
    object order, player;
    string player_name, item_name, coin_pay_text, coin_get_text;
    string *words;
    int *money_arr, amount, price;

    if (!str)
    {
        notify_fail(query_verb()+" what?\n");
        return 0;
    }

    if (sscanf(str, "%s for %s", item_name, player_name) != 2)
    {
        player_name = TP->query_real_name();
        item_name = str;
    }

    words = explode(item_name, " ");

    if (sizeof(words) > 1)
    {
        sscanf(words[0], "%d", amount);
        if (amount > 0)
        {
    	    item_name = implode(words[1..sizeof(words)], " ");
        }
        else
        {    
            amount = 1;
        }
    }
    else
    {
    	amount = 1;
    }

    if (amount > 10)
    {
        notify_fail("You can't buy more than 10 items here!\n");
        return 0;
    }
    if (!interactive(player = present(player_name,TO)))
    {
        player_name = lower_case(player_name);
        player = find_player(player_name);
    	if (!player || file_name(ENV(player)) != PARTY_DIR+"podium")
    	{
	        write("There is no "+CAP(player_name)+" around to give things to.\n");
	        return 1;
	    }
    }

    switch(item_name)
    {
        setuid(); seteuid(getuid());
        case "a honey ham": case "honey ham": case "ham":
            price = 15;
            order = clone_object(PARTY_OBJ+"ham");
            break;
        case "a roast mutton": case "roast mutton": case "mutton":
            price = 36;
            order = clone_object(PARTY_OBJ+"mutton");
            break;
        case "a juicy steak": case "juicy steak": case "steak":
            price = 60;
            order = clone_object(PARTY_OBJ+"steak");
            break;
        case "a roast chicken": case "roast chicken": case "chicken":
            price = 144;
            order = clone_object(PARTY_OBJ+"chicken");
            break;
        case "a blueberry muffin": case "blueberry muffin": case "muffin":
            price = 10;
            order = clone_object(PARTY_OBJ+"muffin");
            break;
        case "a raspberry tart": case "raspberry tart": case "tart":
            price = 15;
            order = clone_object(PARTY_OBJ+"tart");
            break;
        case "a stawberry shortcake": case "stawberry shortcake": 
        case "shortcake": case "cake":
            price = 50;
            order = clone_object(PARTY_OBJ+"shortcake");
            break;
        case "an apple pie": case "apple pie": case "pie":
            price = 100;
            order = clone_object(PARTY_OBJ+"pie");
            break;
        case "a glass of water": case "glass of water": case "water":
            price = 5;
            order = clone_object(PARTY_OBJ+"water");
            break;
        case "a glass of milk": case "glass of milk": case "milk":
            price = 12;
            order = clone_object(PARTY_OBJ+"milk");
            break;
        case "a frosty beer": case "frosty beer": case "beer":
            price = 12;
            order = clone_object(PARTY_OBJ+"beer");
            break;
        case "a pint of ale": case "pint of ale": case "ale":
            price = 30;
            order = clone_object(PARTY_OBJ+"ale");
            break;
        case "a fine white wine": case "fine white wine": case "white wine": 
        case "fine wine": case "wine":
            price = 70;
            order = clone_object(PARTY_OBJ+"wine");
            break;
        case "a brandywine brandy": case "brandywine brandy": case "brandy":
            price = 120;
            order = clone_object(PARTY_OBJ+"brandy");
            break;
        default:
            write("There is no "+item_name+" sold here.\n");
            return 1;
    }

    if (PARTY_MASTER->query_free_food())
    {
	    price = 0;
    }
    else
    {
	    price = price * amount;
    }

    order->set_heap_size(amount);

    if (sizeof(money_arr = pay(price)) == 1)
    {
    	write("You are unable to pay for the "+item_name+".\n");
	    return 1;
    }

    coin_pay_text = text(exclude_array(money_arr, NUM, NUM*2-1));
    coin_get_text = text(exclude_array(money_arr, 0, NUM-1));     

    if (!price)
    {
    	if (player == TP)
        {
	        write("Your order of "+order->short()+" is on the house!\n");
        }
    	else
	    {
	        write("Your order "+order->short()+" for "+CAP(player_name)+
                " is on the house!\n");
	        player->catch_tell("A hobbit walks up to you and says:  I have "+
	            order->short()+" for you, compliments of " + 
                CAP(TP->query_real_name())+".");
	    }
    }
    else
    {
	    if (player == TP)
        {
	        write("You pay "+coin_pay_text+" and order yourself "+
	            order->short()+".\n");
        }
	    else
	    {
	        write("You pay "+coin_pay_text+" and order "+
	            order->short()+" for "+CAP(player_name)+".\n");
    	    player->catch_msg("A hobbit walks up to you and says:  I have "+
	            order->short()+" for you, compliments of "+
	            CAP(TP->query_real_name()) + ".\n");
	    }

	    if (coin_get_text)
        {        
	        write("You get " + coin_get_text + " back.\n");
        }
    }

    tell_room(ENV(player),"A hobbit arrives and hands "+QTNAME(player)+
      " "+order->short()+".\n",player);

    if(order->move(player))
    {
    	write("You cannot carry that much!\n");
	    order->move(ENV(player));
    }

    return 1;   
}
