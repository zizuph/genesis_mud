/* Taken from Inn in Solace, by Nick */
/* Pig and Whistle Inn in Port Balifor */

#include "/d/Ansalon/common/brewcraft/brewcraft.h"
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/port_balifor/local.h"
#include <stdproperties.h>
#include <macros.h>
#include <money.h>

inherit BALIFOR_IN; 
inherit "/lib/trade";
inherit "/d/Ansalon/common/cheater";

#define NUM sizeof(MONEY_TYPES) /* How many types of money do we use? */

/*
* Prototypes
*/
int move_item(mixed arg);

int test; /* to indicate that a test is going on, no money given. */

/*
* Prototypes
*/
int move_item(mixed arg);

object innkeeper;

void
reset_balifor_room()
{
    if (!objectp(innkeeper)) {
	innkeeper = clone_object(BNPC + "william");
	innkeeper->move(TO);
    }
}

/*
 * Function name: create_room
 * Description:   Set up default trade and cofigure it if wanted.
 */
void
create_balifor_room()
{
    config_default_trade();
    set_short("The Pig and Whistle Inn");
    set_long("@@long_descr");

    add_item(({"bar","short bar"}),"A short, ale stained bar. " +
      "On it sits a menu. \n");
    add_item("stairway","A sagging, wooden stairway, that " +
      "leads to the bedrooms on the next level. \n");
    add_item(({"sign","menu"}),"Has words on it. How about " +
      "reading it? \n");
    add_item(({"door","kitchen"}),"A door leading to the rear "+
      "room, which serves as the kitchen. You cannot go "+
      "there.\n");   
    add_item(({"table","tables"}),"This is where the patrons "+
      "of the Inn are served. Almost all of the tables are "+
      "occupied, but you spot one in the corner that " +
      "looks empty.\n");   
    add_cmd_item("menu", "read", "@@read");
    add_cmd_item("sign", "read", "@@read_sign");

    set_tell_time(100);
    add_tell("The sea breeze off the Bay of Balifor makes "+
      "a shrill whistling sound as it blows through the "+
      "front windows.\n");

    add_exit(BROOM+"city01","out","@@out",0);
    add_exit(BROOM+"inn_upstairs","up","@@up",0);

    reset_balifor_room();

    add_npc(BNPC + "sailor");
    add_npc(BNPC + "kid");
    add_npc(KNPC + "bozak");
    add_npc(KNPC + "mercenary");
    add_npc(KNPC + "kender");
    add_npc(KNPC + "goblin", 2);
}

string
long_descr()
{
    return "You enter the Pig and Whistle Inn of Balifor.\n" +
    "The place seems jovial enough, you look around at the "+
    "varied group of patrons here. A few tables are spread "+
    "throughout the room. You spot the jovial barkeeper, "+
    "smiling from behind the small bar. The door to the kitchen "+
    "is behind the bar. A menu hangs above the bar. In the "+
    "corner, you see a staircase leading to the rooms rented "+
    "out. A sign has been nailed to the wall near the stairway.\n";
}

int
out()
{
    write("You open the door and leave the noisy Inn behind.\n");
    return 0;
}

int
up()
{
    write("You climb the stairs. \n");
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
    add_action("order", "buy");
    add_action("order", "order");
    add_action("test", "test");
    add_action("rent","rent");
}

int
rent(string str)
{
    NF("Rent what?\n");
    if (str == "room")
    {
	write("There are no rooms to rent here unfortunately.\n");
	return 1;
    }
    return 0;
}


int
read_sign(string str)
{
    write("     Due to the dragonarmy invasion, there\n" +
      "     are no rooms to rent. Sorry.\n" +
      "\n                   -William.\n\n");
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
      " \n" +
      "           Pig and Whistle Inn        " +
      "\n" +
      "   -----------------------------------" +
      "\n" +
      "   Fresh Muffins               20 cc\n" +
      "   Bread and Cheese            75 cc\n" +
      "   Plate of Smoked Meat       180 cc\n" +
      "\n" +
      "   Sugar Water from Goodlund   10 cc\n" +
      "   Iron Delving Export Brew    24 cc\n" +
      "    ("+ BREWCRAFT_MENU +")        \n"+ 
      "   Wine from Silvanesti        80 cc\n" +
      "   William's Finest Brandy    100 cc\n" +
      "\n" +
      "NOTE: The cook will not prepare \n" +
      "      more than ten items at once. \n");
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
    object william = present("William");

    NF("You look everywhere, but cannot find the barkeeper.\n");
    if (!william || !P(william, TO))
	return 0;

    NF("Buy what?\n");
    if (!str)
	return 0;
    if (check_cheater(TP, william))
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
    case "water":
    case "waters":
    case "sugar":
    case "sugar waters":
	name = "water";
	price = num * 10;
	break;
    case "brew":
    case "brews":
    case "export brew":
    case "export brews":
    case "iron delving export brew":
    case "iron delving export brews":
        name = "brewcraft_beermug";
	price = num * 24;
	break;
    case "wine":
    case "wines":
	name = "wine";
	price = num * 80;
	break;
    case "brandy":
    case "brandies":
    case "brandys":
    case "finest":
    case "finest brandy":
    case "william's brandy":
    case "william's finest brandy":
	name = "brandy";
	price = num * 100;
	break;
    case "muffin":
    case "muffins":
    case "fresh":
    case "fresh muffin":
	name = "muffin";
	price = num * 20;
	break;
    case "bread":
    case "breadss":
    case "cheese":
    case "bread and cheese":
	name = "bread";
	price = num * 75;
	break;
    case "plate":
    case "plates":
    case "meat":
    case "smoked meat":
    case "plate of smoked meat":
    case "plate of meat":
	name = "plate";
	price = num * 180;
	break;
    default:
	NF("I don't understand what you want to buy.\n");
	return 0;
    }
    if (num > 10)
    {
	NF("The cook screams from the kitchen: No more than 10 items! " +
	  "Can you not read the sign? \n");
	return 0;
    }
    if (num < 1)
        cheater_log(this_player(), this_object(), "buy 0 units");

    if (sizeof(arr = pay(price, this_player(), str2, test, 0, str3)) == 1)
	return 0;  /* pay() handles notify_fail() call */

    write("You pay " + text(exclude_array(arr, NUM, NUM * 2 - 1)) + ".\n");
    if (text(exclude_array(arr, 0, NUM - 1)))
	write("You get " + text(exclude_array(arr, 0, NUM - 1)) + ".\n");
    write("The Innkeeper gets to work.\n");

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
  	    file = "/d/Ansalon/balifor/port_balifor/obj/" + name;
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

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    
    if (interactive(ob))
        start_room_tells();
}
