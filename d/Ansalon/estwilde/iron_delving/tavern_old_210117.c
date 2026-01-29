/* Navarre July 3rd 2006, fixed typo, changed meny to menu */


/* Inn in solace, coded by Nick */

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <stdproperties.h>
#include <macros.h>
#include <money.h>

inherit DWARF_IN;
inherit "/lib/trade";
inherit "/d/Ansalon/common/cheater";

#define NUM sizeof(MONEY_TYPES) /* How many types of money do we use? */

int test; /* to indicate that a test is going on, no money given. */
object ob;
object patron, scout;

int move_item(mixed arg);

void
reset_dwarf_room()
{
    if(!objectp(patron))
    {
	patron = clone_object(LIVING + "patron");
	patron->arm_me();
	patron->move(TO);
    }

    if(!objectp(scout))
    {
	scout = clone_object(LIVING + "vryl");
	scout->arm_me();
	scout->move(TO);
    }
}


/*
* Function name: create_room
* Description:   Set up default trade and cofigure it if wanted.
   */
void
create_dwarf_room()
{
    config_default_trade();
    set_short("A dwarven tavern in Iron Delving");
    set_long("@@long_descr");
    add_prop(ROOM_I_NO_CLEANUP, 1);

    add_item(({"roof","low roof"}),
      "This tavern has a low roof, most likely because most " +
      "its patrons are dwarves.\n");
    add_item(({"pipe smoke","smoke","bluey-grey pipe smoke"}),
      "Pipe smoke hangs thickly in this tavern, its earthy " +
      "aroma relaxing you somewhat.\n");
    add_item(({"stout bar","stout wooden bar","bar","wooden bar"}),
      "A stout bar made of wood. A menu stands on top of it.\n");
    add_item("menu","A simple menu. Why don't you try reading it?\n");
    add_item(({"small window","window","brewery"}),
      "Looking through the window to your east you see an " +
      "ajoining room of huge proportions, a dwarven brewery! Here, many " +
      "of the famously strong dwarven beverages are made.\n");
    add_item(({"eastern wall","wall"}),
      "In the eastern wall is a small window.\n");
    add_item(({"floor","trapdoor","closed trapdoor"}),
      "A closed trapdoor in the floor. It probably leads down to an " +
      "ajoining room to your east.\n");

    add_cmd_item(({"trapdoor","door"}),({"open","pull","lift"}),"@@open_door");

    add_cmd_item("menu", "read", "@@read");

    add_exit(IRON + "r12","west",0);


    reset_dwarf_room();
}

int
open_door()
{
    write("You pull at the trapdoor, but it is closed for the time " +
      "being. Come back later!\n");
    say(QCTNAME(TP)+ " pulls at the trapdoor, but " +
      "it is solidly closed.\n");
    return 1;
}

string
long_descr()
{
    return "You stand within a low roofed dwarven " +
    "tavern within the town of Iron Delving. Bluey-grey " +
    "pipe smoke hangs thickly in the air here, as pipe smoking " +
    "along with heavy drinking is a favourite past time of " +
    "most hill dwarves. In the eastern wall is a small window, " +
    "while on the floor just underneath it is a closed trapdoor. A stout " +
    "wooden bar stands at the " +
    "back of the room. A menu stands on top it.\n";
}

void
init()
{
    ::init(); /* Since it's a room this must be done. */
    add_action("order", "buy");
    add_action("order", "order");
    add_action("test", "test");
}

int
read(string str)
{
    write("" +
      " \n" +
      "   Dwarven ale                24 cc\n" +
      "   Dwarven spirit            220 cc\n" +
      "   Iron Rations               70 cc\n\n" +
      "   Dwarven tobacco            12 cc\n" +
      "\n" +
      "The barman will not let you buy more \n" +
      "than ten items at once. \n");
    return 1;
}

int
order(string str)
{
    string name, str1, str2, str3;
    int *arr, price, num;


    NF("buy what?\n");
    if (!str)
	return 0;

    if (check_cheater(TP, "the barman"))
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

    switch(str1)
    {
    case "ale":
    case "ales":
    case "dwarven ales":
    case "dwarven ale":
	name = "ale";
	price = num * 24;
	break;
    case "spirit":
    case "spirits":
    case "dwarven":
    case "dwarven spirit":
	name = "spirit";
	price = num * 220;
	break;
    case "rations":
    case "iron rations":
	name = "rations";
	price = num * 70;
	break;
    case "tobacco":
    case "tobaccos":
    case "dwarven tobacco":
    case "dwarven tobaccos":
	name = "tobacco";
	price = num * 12;
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
	file = EOBJ + name;
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

