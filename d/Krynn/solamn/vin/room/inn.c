/* Inn in guild, coded by Nick */

/* Revision History:
 * /Rastlin, 950215, You can only by soup and drinks if you don't have
 *                   any teeth.
 * /Teth, 960329, Added a bard.
 * modified for the new Vingaard Keep, Dec. 6 1996, Teth
 */

#include "../local.h"
#include <macros.h>
#include <money.h>

inherit IN_BASE;
inherit "/lib/trade";

#define NUM sizeof(MONEY_TYPES) /* How many types of money do we use? */

object bard;

/*
 * Prototypes
 */
int move_item(mixed arg);
int get_price(object ob);

public void
reset_vin_room()
{

    if (bard)
     return;
    bard = clone_object(VNPC + "celeste");
    bard->move_living("xx", TO);
    bard->seq_new("do_thing");
    bard->seq_addfirst("do_thing","@@equip_me");

}
                
/*
 * Function name: create_room
 * Description:   Set up default trade and cofigure it if wanted.
 */
void
create_vin_room()
{
    config_default_trade();
    set_short("The Bronze Dragon Inn");
    set_long("Known for its tasty buffets, this is the Bronze " +
        "Dragon Inn. This Inn is a favourite resting place of " +
        "off duty militia and weary travellers. It has a " +
        "certain rustic charm about it, aiding the warm atmosphere. " +
        "A menu sits on the nearest table, and a sign can be read " +
        "nearby. An exit south leads back to the streets of " +
        "Vingaard Keep.\n");
    AI("menu","Scuffed and dirty, it proves the popularity of this " +
        "Inn. You are able to read the menu.\n");
    AI(({"table","nearest table"}),"It appears to be made of " +
        "pine wood, and it supports a menu.\n");
    AI("tables","There are many tables, for many travellers visit.\n");
    AI(({"ceiling","wall","floor"}),"Varnished hardwood, it adds " +
        "to the rustic charm.\n");
    AI("walls","They are made of varnished hardwood, and lend " +
        "charm.\n");
    AI(({"varnished hardwood","hardwood"}),"Perhaps birch... it is " +
        "difficult to be certain.\n");
    AI("sign","With burnt-in words, it is something you should " +
        "read.\n");

    ACI("menu","read","@@read");
    ACI("sign","read","@@sign");
    AE(VROOM + "ss4", "south", 0);

    add_prop(OBJ_I_LIGHT, 3);
    reset_room();
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
           write("Only gold coins are acceptable.\n");
		return 1;
	    }
	  
	  if (!MONEY_MOVE(1, "gold", TP, 0))
	    {
		write("You pay 1 gold coin for a room.\n");
           TP->set_temp_start_location(VROOM + "inn");
           TP->command("$quit");
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
    write("The Bronze Dragon Inn has many offers.\n"+
        "\n- Food and drink! Read the menu, please.\n"+
        "- Room rental, for one gold coin, but only gold accepted!\n" +
        "\n\nPlease note that by doing 'rent room', you will QUIT " +
        "from these realms, but re-enter them in this room when " +
        "next you return.\n\n");
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
    write("\n" +
    "Welcome to the Bronze Dragon Inn!\n"+
    "---------------------------------\n"+
    "Our kitchen offers the following:\n\n"+
    " - Crystal Clear Water          1 cc\n" +
    " - Crisp Refreshing Beer       12 cc\n" +
    " - Imported Solanthian Wine    72 cc\n" +
    "\n"+
    " - Ripe Grapefruit             25 cc\n" +
    " - Steaming Palanthian Soup    80 cc\n" +
    " - Venison Steak              210 cc\n\n" +
    "************************************\n" +
    "*   The Bronze Dragon Inn Buffet   *\n" +
    "*----------------------------------*\n" +
    "* Try the buffet! Eat and drink as *\n" +
    "* much as you want! Just 'offer'   *\n" +
    "* to see your personal price! Also *\n" +
    "* available now is a non-alcoholic *\n" +
    "* buffet! Little ones: half price! *\n" +
    "************************************\n" +
    "\n");
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
    int *arr, price, num, playeralign;

    NF("Buy what?\n");
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
    case "water":
    case "waters":
    case "crystal water":
    case "clear water":
    case "crystal clear water":
    case "crystal waters":
    case "clear waters":
    case "crystal clear waters":
      name = "water";
      price = num * 6;
      break;
    case "beer":
    case "beers":
    case "crisp beer":
    case "refreshing beer":
    case "crisp beers":
    case "refreshing beers":
    case "crisp refreshing beer":
    case "crisp refreshing beers":
      name = "beer";
      price = num * 12;
      break;
    case "wine":
    case "wines":
    case "imported wine":
    case "imported wines":
    case "solanthian wine":
    case "solanthian wines":
    case "imported solanthian wine":
    case "imported solanthian wines":
      name = "wine";
      price = num * 72;
      break;
    case "grapefruit":
    case "grapefruits":
    case "ripe grapefruit":
    case "ripe grapefruits":
    case "fruit":
    case "fruits":
      name = "fruit";
      price = num * 25;
      break;
    case "soup":
    case "soups":
    case "steaming soup":
    case "steaming soups":
    case "palanthian soup":
    case "palanthian soups":
    case "steaming palanthian soup":
    case "steaming palanthian soups":
      name = "soup";
      price = num * 80;
      break;
    case "steak":
    case "steaks":
    case "venison steak":
    case "venison steaks":
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
      NF("That is not available here.\n");
      return 0;
  }

    if (member_array(name, ({"buffetna","buffet", "steak", "fruit"})) &&
	present("cirath_broken_teeth",TP))
    {
        write("You are toothless, how do you plan to eat that?\n");
	return 1;
    }

    playeralign = TP->query_alignment();
    if (playeralign < 0)
    {
        write("For some reason, no one pays any attention to you when " +
            "you try ordering food.\n");
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
     file = VOBJ + name;
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
      set_alarm(0.2,0.0,"move_item", ({name, num, ob}));
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
    write("\nYour own personal price for the buffet is " +
        price + " copper coins!\n\n");
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

    /* I guess we'll also let Kender eat cheaper */
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













