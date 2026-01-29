#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/common/brewcraft/brewcraft.h"
#include "../local.h"
#include <stdproperties.h>
#include <macros.h>
#include <money.h>

inherit KALAMAN_IN;
inherit "/lib/trade";
inherit "/d/Ansalon/common/cheater";

#define NUM sizeof(MONEY_TYPES) 

int test; 
object barkeeper, archer; 


int move_item(mixed arg);


void
reset_kalaman_room()
{
    if (!barkeeper)
    {
	barkeeper = clone_object(KNPC + "c_innkeeper");
	barkeeper->move_living("xxx", TO);
    }

    if(!archer)
    {
	archer = clone_object(KNPC + "half-elf");
	archer->arm_me();
	archer->move(TO);
    }
}



void
create_kalaman_room()
{
    config_default_trade();
    set_short("a spartan tavern outside the city of Kalaman");
    set_long("@@long_descr");


    add_item(({"sign","menu"}),"Its a menu... you think. Try " +
      "reading it? \n");
    add_item(({"skull","giant skull","plaque","copper plaque"}),
      "From the looks of it, the previous owner of this massive skull " +
      "did not give it away peacefully. A massive rent in the skullcap "+
      "looks like it was caused by a heavy blow from a large axe. A copper " +
      "plaque beneath the skull, tarnished with age, reads:\n\n" +
      "        The skull of Raargh the Younger, Storm Giant of Thunder Mountain.\n" +
      "        Generously donated by Dougan Redhammer and Arman Kharas.\n\n");
    add_item(({"open fireplace","fireplace","fire"}),
      "A large open fireplace burns to the western side of the room, sending " +
      "warmth and light throughout the room.\n");
    add_item(({"long bar","bar"}),
      "A long wooden bar that has seen much use, with a menu of sorts on it.\n");


    add_cmd_item(({"menu","sign"}), "read", "@@read");


    add_exit("/d/Ansalon/kalaman/caravan/outside","out",0);

    set_alarm(15.0,100.0,"stnoise");

    reset_kalaman_room();
}

string
long_descr()
{
    return "You stand within a large wooden structure that has been " +
    "set up outside the walls of Kalaman as a tavern of sorts for " +
    "merchants and their guards. While not the cosiest of places " +
    "you have been in, you are sure this is far more comfortable than " +
    "what is offered on the open road. A large open fireplace fills the " +
    "room with a comfortable glow. On the wall above it hangs the skull of " +
    "what can only be a giant of some sorts. To the back of the room is a " +
    "long bar, with a sign sitting at one end.\n";
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
      "   cHEAP dWARVEN aLE           24 cc\n" +
      "   iDB cRAFT bREW              24cc  \n" +
      "   ( "+BREWCRAFT_MENU+" ) \n" +
      "   bReDD n cHEeSE              75 cc\n" +
      "   pLAtE oF SmOked meAt       180 cc\n" +

      "\n" +
      "NOTE: cOOk part GuLLy dWaRf. Do NoT \n" +
      " OrDER ToO MaNy ItemS aT OncE! \n");
    return 1;
}


int
order(string str)
{
    string name, str1, str2, str3;
    int *arr, price, num;

    NF("The barmaid isn't here to answer your call.\n");
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
    case "cheap dwarven ale":
    case "dwarven ale":
    case "ale":
    case "cheap ale":
	name = "ale";
	price = num * 24;
	break;

    case "brew":
    case "brews":
    case "craft brew":
    case "craft brews":
    case "idb craft brew":
    case "idb craft brews":
    case "mug":
	name = "brewcraft_beermug";
	price = num * 24;
	break;

    case "bread":
    case "cheese":
    case "bread and cheese":
    case "bredd n cheese":
    case "bredd":
	name = "bread";
	price = num * 75;
	break;

    case "meat":
    case "smoked meat":
    case "plate":
    case "plate of smoked meat":
	name = "plate";
	price = num * 180;
	break;
    default:
	NF("I don't understand what you want to buy.\n");
	return 0;
    }
    if (num > 2)
    {
	NF("The cook is a gully dwarf, and cannot count higher than two!\n");
	return 0;
    }
    if (num < 1)
	cheater_log(this_player(), this_object(), "buy 0 units");

    if (sizeof(arr = pay(price, this_player(), str2, test, 0, str3)) == 1)
	return 0;  /* pay() handles notify_fail() call */

    write("You pay " + text(exclude_array(arr, NUM, NUM * 2 - 1)) + ".\n");
    if (text(exclude_array(arr, 0, NUM - 1)))
	write("You get " + text(exclude_array(arr, 0, NUM - 1)) + ".\n");
    write("The barmaid bounces into the kitchen to get your order.\n");

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
        if ( name != "brewcraft_beermug" )
            file = "/d/Ansalon/kalaman/obj/" + name;
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


void
stnoise()
{
    switch(random(4))
    {
    case 0:
	tell_room(this_object(),
	  "The fire pops loudly, sending an ember flying across the room.\n");
	break;

    case 1:
	tell_room(this_object(),
	  "You hear a shriek from the kitchen, followed by the sound of many " +
	  "pots loudly falling onto the ground.\n");
	break;

    case 2:
	tell_room(this_object(),
	  "The fire flares briefly, making the shadows dance throughout the room.\n");
	break;

    case 3:
	tell_room(this_object(),
	  "You hear someone curse from the kitchen: No more than two rats in the pot! " +
	  "No more than two!\n");
	break;

    }
} 
