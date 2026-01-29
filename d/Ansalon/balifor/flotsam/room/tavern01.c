/* Based on Inn in solace (coded by Nick) */
/* Installed by Arman (probably) */
/* Iron Delving Export brew added by Vitwitch 2021 */

#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"
#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include "/d/Ansalon/common/brewcraft/brewcraft.h"

inherit FLOTSAM_IN;
inherit "/lib/trade";
inherit "/d/Ansalon/common/cheater";

#define NUM sizeof(MONEY_TYPES) /* How many types of money do we use? */

int test; /* to indicate that a test is going on, no money given. */
object barkeeper; /* object tika; */
object sailor;
object dwarf;
object ob;

/*
* Prototypes
*/
int move_item(mixed arg);

/*
* Function name: reset_room
* Description:   Set up the objects at reset
*/
void
reset_flotsam_room()
{
    if (!barkeeper)
    {
	barkeeper = clone_object(FNPC + "barkeeper");
	barkeeper->move_living("xxx", TO);
    }
	if(!objectp(dwarf))
	{
	    dwarf = clone_object(FNPC + "dougan");
	    dwarf->move(TO);
	    dwarf->arm_me();
	}
    if(!objectp(sailor))
    {
	sailor = clone_object(FNPC + "sailor");
	sailor->arm_me();
	sailor->move(TO);
    }
}


/*
* Function name: create_room
* Description:   Set up default trade and cofigure it if wanted.
   */
void
create_flotsam_room()
{
    config_default_trade();
    set_short("Hawkstones Taproom");
    set_long("@@long_descr");
    add_prop(ROOM_I_NO_CLEANUP, 1);

    add_item("smoke","A haze of smoke hangs heavily in Hawkstones " +
      "Taproom. \n");
    add_item("fireplace","A small fireplace smoulders " +
      "at the back of the room. \n");
    add_item(({"bar","wall","southern wall","corner"}),"A long " +
      "bar positioned defensively in " +
      "the corner of the tavern. A portly barman stands behind " +
      "it, pouring drinks for the rowdy clientele. A menu is tacked " +
      "on the wall behind the bar. \n");
    add_item(({"hawkstones taproom","tavern"}),"You stand " +
      "within Hawkstones Taproom, a busy tavern in the occupied town " +
      "of Flotsam.\n");
    add_item("patrons","Consisting mainly of weathered " +
      "sailors and soldiers of the dragonarmies, it is no wonder " +
      "that this place is nothing short of lively.\n");
    add_item("door","To the north the tavern door leads out " +
      "into the town.\n");
    add_item("menu","A menu with words. Read it. \n");

    add_cmd_item("menu", "read", "@@read");

    add_exit(FROOM + "street34","north","@@out_bar",0);

    add_prop("_minstrel_performance_location", ({ "Hawkstones Taproom", 1 }) );


    reset_flotsam_room();
}

string
long_descr()
{
    return "You stand in the busy tavern known as 'Hawkstones " +
    "Taproom'. From the looks of things, this tavern is " +
    "nothing more than one filthy, lawless, ongoing drunken " +
    "brawl, where the only patrons who are not fighting or " +
    "roaring curses or bawdy songs are those who have already " +
    "passed out. Pipe smoke as well as a small, poorly " +
    "stoked fireplace on the southern wall work together " +
    "to create a hazy and somewhat seedy atmosphere. A " +
    "large bar is defensively positioned in the corner of " +
    "the rear wall, directly across from the door. \n";
}


int
out_bar()
{
    write("You step out of Hawkstones Taproom...\n");
    return 0;
}

/*
* Function name: init
* Description:   Initalize the pub actions
*/
void
init()
{
    ::init(); /* Since it's a room this must be done. */
    if (ob = present("tour7",TP))
	ob->set_arr("flotsam");
    add_action("order", "buy");
    add_action("order", "order");
    add_action("test", "test");
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
      " \n" +
      "   Small beer                 12 cc\n" +
      "   IDB Export brew            24 cc\n" +
      "    ("+ BREWCRAFT_MENU +")\n" +
      "   Some really sweet wine     72 cc\n" +
      "   Dwarven spirit            220 cc\n" +
      "\n" +
      "Take note that the barman does not like \n" +
      "strangers. He will not let you buy more \n" +
      "than ten items at once. \n");
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

    NF("The barkeeper isn't here to answer your call.\n");
    if (!barkeeper || !P(barkeeper, TO))
	return 0;

    NF("buy what?\n");
    if (!str)
	return 0;

    if (check_cheater(TP, barkeeper))
        return 1;
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

    switch(lower_case(str1))
    {
    case "beer":
    case "beers":
    case "small":
    case "small beer":
	name = "beer";
	price = num * 12;
	break;
    case "brew":
    case "brews":
    case "export brew":
    case "export brews":
    case "idb export brew":
    case "idb export brews":
        name = "brewcraft_beermug";
	price = num * 24;
	break;
    case "wine":
    case "wines":
    case "sweet":
    case "sweet wine":
	name = "wine";
	price = num * 72;
	break;
    case "spirit":
    case "spirits":
    case "dwarven":
    case "dwarven spirit":
	name = "d_spirit";
	price = num * 220;
	break;
    default:
	NF("I don't understand what you want to buy.\n");
	return 0;
    }
    if (num > 10)
    {
	NF("The barkeeper says: I aint carrying more than 10 items!\n");
	return 0;
    }
    if (num < 1)
        cheater_log(this_player(), this_object(), "buy 0 units");

    if (sizeof(arr = pay(price, this_player(), str2, test, 0, str3)) == 1)
	return 0;  /* pay() handles notify_fail() call */

    write("You pay " + text(exclude_array(arr, NUM, NUM * 2 - 1)) + ".\n");
    if (text(exclude_array(arr, 0, NUM - 1)))
	write("You get " + text(exclude_array(arr, 0, NUM - 1)) + ".\n");
    write("The barkeeper gets to work.\n");

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

    for (i = 0; i < 10; i++)
    {
	num--;
        if (name != "brewcraft_beermug")
	    file = FOBJ + "drink/" + name;
        else
            file = "/d/Ansalon/estwilde/obj/" + name;
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
		    ob->catch_msg("You get some " + drink->plural_short() +
		      ".\n");
		    say(QCTNAME(ob) + " buys some " + drink->plural_short() +
		      ".\n", ob);
		}
		else 
		{
		    ob->catch_msg("You get " + drink->short() + ".\n");
		    say(QCTNAME(ob) + " buys " + drink->short() + ".\n",
		      ob);
		}
	    }
	}
	else 
	{
	    say(QCTNAME(ob) + " seems to be estimating something.\n",
	      ob);
	    return 1;
	}
	if (num < 1)
	    break;
    }

    if (num > 0)
	set_alarm(1.0, 0.0, &move_item(({name, num, ob})));
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
    if (!str || !stringp(str))
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

