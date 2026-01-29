/* Code from Solace's Inn, altered for use as the gnomish cafeteria */
/* Thanks, Nick, for doing all the hard stuff... :)                 */

inherit  "/std/room";
inherit "/lib/trade";

#include "/d/Krynn/common/defs.h"
#include "local.h"
#include <stdproperties.h>
#include <macros.h>
#include <money.h>

#define NUM sizeof(MONEY_TYPES) /* How many types of money do we use? */

int test; /* to indicate that a test is going on, no money given. */

/*
 * Prototypes
 */
int move_item(mixed arg);

/*
 * Function name: reset_room
 * Description:   Set up the objects at reset
 */
void
reset_room()
{
    object hammer;

    if (!present("hammer"))
    {
	hammer = clone_object(OBJ + "hammer");
	hammer->move(TO);
    }
}

/*
 * Function name: create_room
 * Description:   Set up default trade and configure it if wanted.
 */
void
create_room()
{
    config_default_trade();
    set_short("The Gnomes' Cafeteria");
    set_long("To keep their minds working without losing too much "+
      "time from their work, the gnomes have designed this fully "+
      "automatic cafeteria, a revolutionary concept in culinary " +
      "science. Perhaps one day all of Krynn will be filled with " +
      "these wonders. Just press your selection. A menu is hung on " +
      "the wall.\n");

    add_item("menu", "It hangs very neatly on the wall. Some words are " +
      "written on it.\n");
    add_item(({"chairs", "tables"}),
      "Sturdy wooden chairs and tables abound in the room. " +
      "Chattering gnomes eat and argue all around you.\n");
    add_cmd_item("menu", "read", "@@read");
    INSIDE;
    LIGHT;

    add_exit(TDIR + "cavern9", "south", 0);
    add_exit(TDIR + "living4", "northwest", 0);
    add_exit(TDIR + "living3", "west", 0);
    add_exit(TDIR + "living5", "east", 0);
    add_prop(ROOM_I_INSIDE,1);  /* This is a real room */
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
    add_action("order", "press");
    add_action("test", "test");
}

/*
 * Function name: read
 * Description:   Read the menu
 * Arguments:     str - hopefully the menu
 */
string
read(string str)
{
    write("" +
      "   Gnomish beer                10 cc\n" +
      "   Can of fruit juice           5 cc\n" +
      "   Gnomish roll                 6 cc\n" +
      "   Gnomish pudding             12 cc\n" +
      "   Emergency energy ration    110 cc\n" +
      "This marvelous device, a product of the Nutrition Guild, is " +
      "equipped with many modern conveniences. You can specify the " +
      "sort of coins you intend to put into the machine with 'buy " +
      "pudding with silver', for example. You can also buy several " +
      "items at once, such as 'buy 10 beers'.\n");
    return "\n";
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

    /* Has the player defined how payment will be done and what change to
     * get back?
     */  
    if (sscanf(str, "%s with %s and get %s", str1, str2, str3) != 3)
    {
	/* Well, maybe player has defined how payment will be done atleast?*/
	str3 = "";
	if (sscanf(str, "%s with %s", str1, str2) != 2)
	{
	    str2 = "";
	    str1 = str;
	}
    }

    if (sscanf(str1, "%d %s", num, str1) != 2)
	num = 1;

    name = "";
    switch(str1)
    {
    case "beer":
    case "beers":
    case "gnomish beer":
    case "gnomish beers":
	name = "beer";
	price = num * 10;
	break;
    case "juice":
    case "can":
    case "fruit juice":
    case "juices":
    case "cans":
    case "fruit juices":
	name = "juice";
	price = num * 5;
	break;
    case "roll":
    case "gnomish roll":
    case "rolls":
    case "gnomish rolls":
	name = "roll";
	price = num * 6;
	break;
    case "pudding":
    case "gnomish pudding":
    case "puddings":
    case "gnomish puddings":
	name = "pudding";
	price = num * 12;
	break;
    case "emergency":
    case "energy":
    case "ration":
    case "energy ration":
    case "emergency ration":
    case "emergency energy ration":
    case "rations":
    case "energy rations":
    case "emergency rations":
    case "emergency energy rations":
	name = "ration";
	price = num * 110;
	break;
    default:
	NF("The machine churns for a while, but does nothing.\n");
	return 0;
    }

    if (sizeof(arr = pay(price, this_player(), str2, test, 0, str3)) == 1)
	return 0;  /* pay() handles notify_fail() call */

    write("You pay " + text(exclude_array(arr, NUM, NUM*2-1)) + ".\n");
    if (text(exclude_array(arr, 0, NUM-1)))
	write("You get " + text(exclude_array(arr, 0, NUM-1)) + ".\n");
    write("Something starts to whir deep down in the machine.\n");

    return move_item(({name, num, TP}));
}

int
move_item(mixed arg)
{
    object drink, ob;
    string file, name2;
    int i, num;

    name2 = arg[0];
    num = arg[1];
    ob = arg[2];

    for (i = 0; i < 10; i++)
    {
	num--;
	file = FOOD + name2 + ".c";
	drink = clone_object(file);

	if (!test && (drink->move(ob)))
	{
	    ob->catch_msg("You drop the " + drink->short() +
	      " on the floor.\n");
	    say(QCTNAME(ob) + " drops a " + drink->short() +
	      " on the floor.\n", ob);
	    drink->move(TO);
	}
	else if (!test) 
	{
	    if (num == 0)
	    {
		if (arg[1] > 1)
		{
		    ob->catch_msg("The machine spits out some " +
		      drink->plural_short() + ".\n");
		    say(QCTNAME(ob) + " gets some " +
		      drink->plural_short() +
		      " from the gnomish vending machine.\n", ob);
		} 
		else 
		{
		    ob->catch_msg("The machine spits out a " +
		      drink->short() + ".\n");
		    say(QCTNAME(ob) + " gets " + drink->short() +
		      " from the gnomish vending machine.\n",	ob);
		}
	    }
	} 
	else 
	{
	    say(QCTNAME(ob) + " seems to be estimating something.\n", ob);
	    return 1;
	}
	if (num < 1)
	    break;
    }

    if (num > 0)
	set_alarm(1.0,0.0,"move_item", ({name2, num, ob}));
    return 1;
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

    if (sscanf(str, "buy %s", str1)) 
    {
	test = 1;
	write("This would be the result of a buy:\n");
	i = order(str1);
	test = 0;
	return i;
    }
}

wayout()
{
    return "northwest south east";
}

tohelp()
{
    return "east";
}

fromhelp()
{
    return "northwest";
}

area()
{
    return "Inthelivingquarters";
}
