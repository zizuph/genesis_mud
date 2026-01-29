inherit "/std/room";
inherit "/lib/trade";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/money.h"
#include "../defs.h"

#define NUM 4 /* How many types of money do we use? */

int test; /* to indicate that a test is going on, no money given. */

/*
 * Prototypes
 */
object make_drink(string name, string aname, string adj, string long,
    int weight, int volume, int soft, int alco);
void config_trade_data();
		  
/*
 * Function name: create_room
 * Description:   Set up default trade and cofigure it if wanted.
 */

void
reset_room()
{
    if (!present("bartender"))
        room_add_object(G_MON + "bartender", 1, 
            "The bartender arrives.  'The bar is open!' he shouts.\n");
}

void
create_room()
{
    config_default_trade();
    set_short("The Liquid Booty Tavern");
    set_long( break_string(
"This is the Bloody Raven, home to scoundrels in the off-hours (daylight)." +
"Many a thief have come here to escape their throubles.  There are blood-" +
"stained tables lying around, along with other broken furniture.  There " +
"is a menu on the wall, and an evil-looking bartender will take your order " +
"(If he hasn't been killed by the patrons), when he has the time.  Stairs " +
"in the southwest corner lead down to the basement.\n", 78));
    
    add_exit(G_ROOMS + "guard_room", "west");
    add_exit(G_ROOMS + "wine_cellar", "down", "@@block");

    add_item(({"table", "tables", "furniture"}), break_string(
"Some tables and chairs are broken, while others pass as slighty " +
"functionalble.  The tables are stained with blood and beer, and are " +
"littered with half empty glasses.  It looks like the bartender doesn't " +
"clean up very often.\n", 78));

    add_item(({"menu", "sign"}), "I'll bet it lists some pretty yummy " +
        "drinks.  Why don't you read it?\n");

    add_prop(ROOM_I_INSIDE,1);  /* This is a real room */

    reset_room();
}

int
block()
{
    if (!present("bartender")) return 0;
    write ("The bartender says: Get away from there!\n" +
           "He moves to block your path.\n");
    return 1;
}

/*
 * Function name: init
 * Description:   Initalize the pub actions
 */
void
init()
{
    ::init(); /* Since it's a room this must be done. */
    add_action("read_menu", "read");
    add_action("order", "buy");
    add_action("order", "order");
    add_action("test", "test");
}

int
read_menu(string str)
{
    NF ("Read what?\n");
    if (str == "menu" || str == "sign")
    {
        say (QCTNAME(this_player()) + " reads the menu.\n");
        write (
"     +-----------------------------------------------------+\n" +
"     |                                                     |\n" +
"     |  A cheap draft                               12 cc  |\n" +
"     |  An Imperial stout                           70 cc  |\n" +
"     |  A tumbler of Sake                           72 cc  |\n" +
"     |  A shot of Tequlia                          260 cc  |\n" +
"     |                                                     |\n" +
"     +-----------------------------------------------------+\n");
       return 1;
    }
    return 0;
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
    string name, aname, adj, long, str1, str2, str3, change;
    int *arr, price, alco, weight, volume, soft, silent, i;

    if (!str) 
    {
	NF("buy what?\n");
	return 0;
    }
    if (!present("bartender"))
    {
        write("Since the bartender isn't here, the bar is closed.\n");
        return 1;
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
        aname = "beer";
	adj = "imperial";
	long = "It's very dark but smells like beer.\n";
	weight = 540;
	volume = 540;
	soft = 540;
	alco = 38;
	price = 70;
	break;
    case "draft":
	/* Beer, alco is 4% */
	name = "draft";
        aname = "beer";
	adj = "cheap";
	long = "It's a nasty-looking draft, but beer is beer, right?\n";
	weight = 100;
	volume = 100;
	soft = 100;
	alco = 4;
	price = 12;
	break;
    case "sake":
	/* Sake, alco is 40% */
	name = "sake";
        aname = "tumbler";
	adj = "tumbler of";
	long = "A powerful wine made from rice.  Its obviously imported.\n";
	weight = 62;
	volume = 62;
	soft = 62;
	alco = 25;
	price = 72;
	break;
    case "tequila":
	/* Tequlia, alco is 60%, now that leaves 80% and 96% ;-/ */
	name = "tequila";
        aname = "shot";
	adj = "shot of";
	long = "The perfect drink for the perpetually deranged.\n";
	weight = 84;
	volume = 84;
	soft = 84;
	alco = 50;
	price = 260;
	break;
    case "shot":
	/* Tequlia, alco is 60%, now that leaves 80% and 96% ;-/ */
	name = "tequila";
        aname = "shot";
	adj = "shot of";
	long = "The perfect drink for the perpetually deranged.\n";
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
  
    drink = make_drink(name, aname, adj, long, weight, volume, soft, alco);
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
    if (arr[sizeof(arr) - 1] 
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
	write("The bartender hands you your " + name + ".\n");
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
make_drink(string name, string aname, string adj, string long, int weight,
	   int volume, int soft, int alco)
{
    object drink;
    
    drink = clone_object("/std/drink");
    drink->set_name(name);
    if (strlen(aname) > 0)
        drink->add_name(aname);
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
