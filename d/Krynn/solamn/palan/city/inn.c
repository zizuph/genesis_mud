/* Inn in guild, coded by Nick */

/* Revision History:
 * /Rastlin, 950215, You can only by soup and drinks if you don't have
 *                   any teeth.
 * /Teth, 960329, Added a bard.
 */

#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include "../local.h"

inherit ROOM_BASE
inherit "/lib/trade";

#define NUM sizeof(MONEY_TYPES) /* How many types of money do we use? */
#define VDIR "/d/Krynn/solamn/vkeep/"
#define MNSTR "/d/Krynn/solamn/vkeep/mnstrs/"

string
query_to_jail()
{
    return "south";
}

/*
object bard;
*/

/*
 * Prototypes
 */
int move_item(mixed arg);
int get_price(object ob);

void
reset_palan_room()
{
/*

    if (bard)
     return;
    bard = clone_object(MNSTR + "bard");
    bard->move_living("xx", TO);
    bard->seq_new("do_thing");
    bard->seq_addfirst("do_thing","@@equip_me");
*/

}
                
/*
 * Function name: create_room
 * Description:   Set up default trade and cofigure it if wanted.
 */
void
create_palan_room()
{
    config_default_trade();
    set_short("The Bronze Dragon Inn");
    set_long("You find yourself standing in the middle of the Bronze Dragon " +
	     "Inn, an inn for the tired and weary traveller. The inn has a " +
	     "certain rustic charm about it and is warm and cosy. There is " +
	     "a sign here and a menu sitting on a table.\n");
    
    add_item("menu", "It has a lot of readable words on it.\n");
    add_item("table", "It has a nice looking menu on it.\n");
    add_item("tables", "In one corner are many tables with a lot of food " +
	     "on them.\n");
    
    add_cmd_item("menu", "read", "@@read");
    add_cmd_item("sign", "read", "@@sign");
    add_item("sign", "It looks important.\n");
    add_exit(ROOM + "street20","south",0,1);

    reset_room();
    set_alarm(1.0,0.0,"reset_room");
}

/*
 * Function name: init
 * Description:   Initalize the pub actions
 */
void
init()
{
    ::init(); /* Since it's a room this must be done. */
    add_action("order", "buy");
    add_action("order", "order");
    add_action("offer", "offer");
    add_action("rent", "rent");
}

/*
 * Function name: rent
 * Description:   rents the room and quits the player from the game.
 */
int
rent(string str)
{
    NF("Rent what?\n");
    if (str == "room")
      {
	  if (!present("gold coin", TP))
	    {
		write("The innkeeper says: I only take gold for my rooms.\n");
		return 1;
	    }
	  
	  if (!MONEY_MOVE(1, "gold", TP, 0))
	    {
		write("You pay 1 gold coin for a room.\n");
        this_player()->set_temp_start_location(ROOM + "inn");
		this_player()->command("quit");
		return 1;
	    }
	  return 0;
      }
    return 0;
}

/*
 * Function name: sign
 * Description:   Read the sign
 * Arguments:     str - hopefully the sign
 */
int
sign(string str)
{
    write("Here you can order food and drink from the menu or you\n" + 
	  "can rent a room for the night at the price of 1 gold.\n" +
	  "Please note that the innkeeper here will only accept gold\n" +
	  "when you go to pay for your room.\n" +
	  "Typing 'rent room' here will QUIT you from the game and you\n" +
	  "will start off here the next time you enter the game.\n");
    return 1;
}

/*
 * Function name: read
 * Description:   Read the menu
 * Arguments:     str - hopefully the menu
 */
int
read(string str)
{
    write("" +
	  "This is what we have to offer at the Smiling Knight:\n\n" +
	  "   Small beer                 12 cc\n" +
	  "   Newly imported wine        72 cc\n" +
	  "   A grapefruit               25 cc\n" +
	  "   Soup of the house          80 cc\n" +
	  "   Big beef steak            210 cc\n\n" +
	  "********** TODAYS SPECIAL *********\n" +
	  "***** Try our buffet, eat and *****\n" +
	  "**** drink as much as you want ****\n" +
	  "** NEW: Our non-alcoholic buffet **\n" +
	  "**        is available now.      **\n" +
	  "****                           ****\n" +
	  "******       Children         *****\n" +
	  "**********  HALF PRICE!   *********\n\n" +
	  "Try 'offer' to see what price you have to pay for a buffet.\n" +
	  "");
    return 1;
}

/*
 * Function name: order
 * Description:   The buyer orders a drink
 * Arguments:     str - name of drink an possibly description on how to pay and
 *                      get the change
 */
int
order(string str)
{
    string name, str1, str2, str3;
    int *arr, price, num;

    NF("buy what?\n");
    if (!str)
        return 0;

    /* Has the player defined how payment will be done and what change to get back? */  
    if (sscanf(str, "%s with %s and get %s", str1, str2, str3) != 3)
    {
    /* Well, maybe player has defined how payment will be done atleast? */
        str3 = "";
        if (sscanf(str, "%s with %s", str1, str2) != 2)
        {
            str2 = "";
            str1 = str;
        }
    }

    if (sscanf(str1, "%d %s", num, str1) != 2)
      num = 1;

    switch(str1)
    {
    case "beer":
    case "beers":
    case "small":
    case "small beer":
      name = "beer";
      price = num * 12;
      break;
    case "wine":
    case "wines":
    case "imported":
      name = "wine";
      price = num * 72;
      break;
    case "grape":
    case "grapes":
    case "grape fruit":
    case "grape fruits":
    case "grapefruit":
    case "grapefruits":
    case "fruit":
    case "fruits":
      name = "fruit";
      price = num * 25;
      break;
    case "soup of the house":
    case "soups of the house":
    case "soup":
    case "soups":
      name = "soup";
      price = num * 80;
      break;
    case "beef":
    case "big beef":
    case "steak":
    case "steaks":
    case "beef steak":
    case "beef steaks":
    case "big beef steak":
    case "big beef steaks":
      name = "steak";
      price = num * 210;
      break;
    case "buffet":
      name = "buffet";
      price = get_price(TP);
      break;
    case "buffet without alcohol":
    case "non-alcoholic buffet":
    case "non alcoholic buffet":
      name = "buffetna";
      price = get_price(TP);
      break;
    default:
      NF("I don't understand what you want to buy.\n");
      return 0;
  }

    if (member_array(name, ({"buffet", "steak", "fruit"})) &&
	present("cirath_broken_teeth",TP))
    {
        write("You are toothless, how do you plan to eat that?\n");
	return 1;
    }

    if (sizeof(arr = pay(price, this_player(), str2, 0, 0, str3)) == 1)
      return 0;  /* pay() handles notify_fail() call */
    
    write("You pay " + text(exclude_array(arr, NUM, NUM*2-1)) + ".\n");
    if (text(exclude_array(arr, 0, NUM-1)))
      write("You get " + text(exclude_array(arr, 0, NUM-1)) + ".\n");
    
    return move_item(({name, num, TP}));
}

int
move_item(mixed arg)
{
    object drink, ob;
    string file, name;
    int i, num;

    name = arg[0];
    num = arg[1];
    ob = arg[2];

    if (num <= 0)
      return 1;

    for (i = 0; i < 10; i++)
      {
	  num--;
	  file = STAND_DIR + "solamn/guild/obj/" + name;
	  drink = clone_object(file);
	  
	  if (drink->move(ob))
	    {
		ob->catch_msg("You drop " + drink->short() +
			      " on the floor.\n");
		say(QCTNAME(ob) + " drops " + drink->short() +
		    " on the floor.\n", ob);
		drink->move(TO);
	  } else if (num == 0) {
	      if (arg[1] > 1)
		{
		    ob->catch_msg("You get some " + drink->plural_short() +
				  ".\n");
		    say(QCTNAME(ob) + " buys some " + drink->plural_short() +
			".\n", ob);
	      } else {
		  ob->catch_msg("You get " + drink->short() + ".\n");
		  say(QCTNAME(ob) + " buys " + drink->short() + ".\n",
		      ob);
	      }
	  }
	  
	  if (num < 1)
	    break;
      }
    
    if (num > 0)
      set_alarm(1.0,0.0,"move_item", ({name, num, ob}));
    return 1;
}

/*
 * Function name: offer
 * Description:   Will tell the player the price to dine here
 */
int
offer()
{
    int price;

    price = get_price(TP);
    write("Let's see, I'll get you a very special price.....\n");
    write("..................... only for you, " + price + " cc.\n");
    say(QCTNAME(TP) + " asks for the price of the buffet.\n");
    return 1;
}

/*
 * Function name: get_price
 * Description:   Find out what price a player should pay
 * Arguments:     ob - the object who wants to eat.
 * Returns:  the price
 */
int
get_price(object ob)
{
    int max_eat, max_alc, max_soft, price, my_eat, 
        my_alc, current_eat, current_alc;

    max_eat = ob->query_prop(LIVE_I_MAX_EAT);
    max_alc = ob->query_prop(LIVE_I_MAX_INTOX);
    max_soft = ob->query_prop(LIVE_I_MAX_DRINK);
    current_eat = ob->query_stuffed() / 20;
    current_alc = ob->query_intoxicated() / 2;
    /*  We assume we don't really know if the player is stuffed or not.
     *  Well, we take a look and if s/he is filled the price 
     *  will go down very slightly.
     */

    my_eat = (max_eat - current_eat);
    my_alc = (max_alc - (current_alc > 0 ? current_alc : 0));

    /* my_eat / 3 is derived from this calculation:
     *  - assume the players eats in pieces of 180 grams (MAX is 250)
     *  - the player can eat my_eat amount of food
     *  - my_eat / 180 is the number of pieces to eat
     *  - food with amount 180 costs 59 cc (5 + 180*180/600 = 59)
     *  - my_eat / 180 * 59 is approximated with my_eat / 3
     *
     * my_alc * 5 / 2 is derived from this calculation:
     *  - assume the players drink in amounts of 20 grams (MAX is 30)
     *  - the player can drink my_alc amount of alcohol
     *  - my_alc / 20 is the number of drinks to get intoxicated
     *  - drinks with amout 20 alcohol cost 50 cc (10 + 20*20/10 = 50)
     *  - my_alc / 20 * 50 is approximated with my_alc * 5 / 2
     *
     * Note these two calculations are not the minimum, but due to
     * the fact that you can't leave the room while eating it's not
     * the maximum price either that is used.
     */
    price = (my_eat / 3) + (my_alc * 5 / 2) + 200;

    /* 200 cc is the base price to pay for the buffet, except for hobbits */

    if (ob->query_race() == "hobbit")
      price -= 200;

    /* mininum is 50 cc, even for hobbits :) */
    return (price > 50 ? price : 50);
}

/*
 * Function name: leave_inv
 * Description:  Called when somebody leaves the inn.
 * Arguments:  ob - leaving object
 *  dest - to where it's going
 */
void
leave_inv(object ob, object dest)
{
    object *obj;
    int i;

    ::leave_inv(ob, dest);

    obj = deep_inventory(ob);
    for (i = 0; i < sizeof(obj); i++)
      if (obj[i]->id("buffet"))
	obj[i]->remove_object();
}



