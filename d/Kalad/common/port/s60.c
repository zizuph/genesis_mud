#include "default.h"
inherit PORT_ROOM;
inherit "/lib/trade";
#include "/sys/filter_funs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/money.h"
#define NUM 4 /* How many types of money do we use? */

int test; /* to indicate that a test is going on, no money given. */

/*
* Prototypes
*/
object make_drink(string name, string adj, string long, int weight,
  int volume, int soft, int alco);
/* void config_trade_date();

/*
* Function name: create_port_room
* Description:   Set up default trade and cofigure it if wanted.
   */
/* modified by Antharanos */
void
create_port_room()
{
    config_default_trade();
    set_short("The Liquid Booty Tavern");
    set_long(
      "The air is dark and smoky, and the bright white and blue striped shirts\n"+
      "of the hired sailors almost gleam out in the dim light. The bar is covered\n"+
      "in empty flagons, and the barmaids are overworked to the extreme. Yells\n"+
      "for more ale and mead resound off the sooty walls, and the large fire\n"+
      "burning in the hearth snaps and cracks with its fresh hardwood fuel.\n"+
      "   Imperial stout             70 cc\n" +
      "   Firstclass small beer      12 cc\n" +
      "   A special of the house     72 cc\n" +
      "   A hot vodka               260 cc\n\n"+
      "Try 'buy vodka with gold' if you wanna specify what to\n" +
      "pay with, or 'test buy beer' to see what would happen\n" +
      "if you typed 'buy beer'.\n\n" +
      "A swinging door leads back out into the air to the south.\n");

    add_exit(PORT + "s73", "south");
    add_item(({"hired sailors","sailors"}),"Hardy, rugged looking individuals "+
      "that look like they've had too much to drink.\n");
    add_item(({"bar"}),"It is sooty and covered with spilled drinks.\n");
    add_item(({"barmaids","barmaid"}),"Buxom brunettes that are working "+
      "hard to please the sailors.\n");

    add_prop(ROOM_I_INSIDE,1);  /* This is a real room */

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
    add_action("test", "test");
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
    object drink;
    string name, adj, long, str1, str2, str3, change;
    int *arr, price, alco, weight, volume, soft, silent, i;

    if (!str) {
	NF("buy what?\n");
	return 0;
    }

    /* Has the player defined how payment will be done and what
    * change to get back? */
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

    switch(str1)
    {
    case "stout":
	/* Stout, alco is 7% */
	name = "stout";
	adj = "imperial";
	long = "It's very dark but smells like beer.\n";
	weight = 540;
	volume = 540;
	soft = 540;
	alco = 38;
	price = 70;
	break;
    case "beer":
	/* Beer, alco is 4% */
	name = "beer";
	adj = "small";
	long = "It's a small but refreshing beer.\n";
	weight = 100;
	volume = 100;
	soft = 100;
	alco = 4;
	price = 12;
	break;
    case "special":
	/* Special, alco is 40% */
	name = "special";
	adj = "";
	long = "It's a very special special of the house.\n";
	weight = 62;
	volume = 62;
	soft = 62;
	alco = 25;
	price = 72;
	break;
    case "vodka":
	/* Vodka, alco is 60%, now that leaves 80% and 96% ;-/ */
	name = "vodka";
	adj = "hot";
	long = "It looks hot and strong indeed.\n";
	weight = 84;
	volume = 84;
	soft = 84;
	alco = 50;
	price = 260;
	break;
    default:
	NF("I don't understand what you want to buy.\n");
	return 0;
    }

    drink = make_drink(name, adj, long, weight, volume, soft, alco);
    /* No drink messege  */
    if (!drink)
    {
	NF("Error in creating drink.\n");
	return 0;
    }

    silent = 0;

    if (sizeof(arr = pay(price, this_player(), str2, test,
	  0, str3, silent)) == 1)
    {
	if (arr[0] == 1)
	    NF("You have to give me more to choose from, that isn't enough.\n");
	else if(arr[0] == 2)
	    NF("You don't carry that kind of money!!!!!!!!!\n");
	return 0;  /* pay() handles notify_fail() call */
    }

    /* This is how to detect if the player dropped some of the change. */
    /* Then if you had set the silent flag in the pay command you would */
    /* then say something about it here. */
    /*
    if (arr[sizeof(arr) -1])
       write("You couldn't hold all the change.\n");
    */

    write("You pay " + text(arr[0 .. NUM - 1]) + ".\n");
    if (change = text(arr[NUM .. NUM * 2 - 1]))
	write("You get " + change + ".\n");

    if (!test && (drink->move(this_player())))
    {
	write("You drop the " + name + " on the floor.\n");
	say(QCTNAME(this_player()) + " drops one " + name + " on the floor.\n");
	drink->move(this_object());
    }

    else if (!test)
    {
	write("You get your " + name + ".\n");
	say(QCTNAME(this_player()) + " buys a " + name + ".\n");
    }

    else
	say(break_string(QCTNAME(this_player()) +
	    " seems to be estimating something.\n", 78));

    return 1;
}

/*
* Function name: make_drink
* Description:   Set up the drinks
* Arguments:     A lot of drink data to be set
*/
object
make_drink(string name, string adj, string long, int weight,
  int volume, int soft, int alco)
{
    object drink;

    drink = clone_object("/std/drink");

    drink->set_name(name);

    if (strlen(adj) > 0)
	drink->set_adj(adj);

    drink->set_long(long);
    drink->set_soft_amount(soft);
    drink->set_alco_amount(alco);
    drink->add_prop(OBJ_I_WEIGHT, weight);
    drink->add_prop(OBJ_I_VOLUME, volume);

    return drink;
}

/*
* Function name: test
* Description:   To allow the buyer to see what would happen with change and
*                payment depending on how the buyer chooses to pay.
* Arguments:     str - name of drink an possibly description on how to pay and
*                      get the change
*/
int
test(string str)
{
    int i;
    string str1;

    NF("Test what?\n");
    if (!str)
	return 0;

    if (sscanf(str, "buy %s", str1))
    {
	test = 1;
	write("This would be the result of a buy:\n");
	i = order(str1);
	test = 0;
	return i;
    }

}

