#include "../default.h"

inherit CVAN_ROOM;
inherit "/lib/trade";

#include <money.h>

#define NUM    sizeof(MONEY_TYPES)

int    move_item(mixed arg);

int    test;
object jenn;
object stranger;
object gossiper;

void
create_cvan_room()
{
    set_short("The Journey's End Inn");
    set_long("\nYou are within the stone building.\n"+
      "Here you can see a common area, where travellers may rest from "+
      "their journeys and perhaps grab a bite to eat or drink. In the "+
      "far corner is a polished wooden counter. Behind and above the "+
      "counter is a large menu. In the corner a flight of stairs leads "+
      "up.\n\n");

    add_item(({ "polished counter", "counter", "wooden counter" }),
      "This countertop looks like it has been lovingly polished and "+
      "shined by caring hands. It is so clean you can see your image "+
      "clearly reflected.\n");
    add_item(({ "image", "my image", "your image", "reflection" }),
      "\nEEEEEEEKS!!!\nWhat the hell is that?!\n\n");
    add_item(({ "wooden stairs", "stairs", "flight", "flight of stairs" }),
      "A wooden staircase that winds its way up to the second floor of "+
      "the inn.\n");
    add_item(({ "dark corner", "corner" }),
      "It is dark and filled with many shadows.\n");
    add_item("shadows", "Dark and spooky, there seems to be something "+
      "moving in them.\n");
    add_item(({ "large menu", "menu" }),
      "It has a lot of readable words on it.\n");

    add_cmd_item(({ "large menu", "menu" }), "read", "@@read");

    config_default_trade();

    set_hear_bell(1);

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(CVAN + "caravan/s1", "west", "@@leave_msg");
    add_exit(CVAN + "shop/jeinn1", "up", "@@leave_msg");

    reset_room();
}

void
reset_room()
{
    if(!jenn)
    {
	jenn =  clone_object(CVAN + "shop/jeik");
	jenn -> move_living("M", TO);
    }

    if(!stranger)
    {
	stranger =  clone_object(NPC + "stranger");
	stranger -> arm_me();
	stranger -> move_living("M", TO);
    }

    if(!gossiper)
    {
	gossiper =  clone_object(NPC + "gossiper");
	gossiper -> move_living("M", TO);
	jenn -> team_join(gossiper);
    }
}

void
init()
{
    ::init();

    add_action("order", "buy");
    add_action("order", "order");
}

int
read(string str)
{
    write("\n"+
      "\tKabal beer   \t 24 copper\n"+
      "\tRuby wine    \t120 copper\n"+
      "\tFresh orange \t 30 copper\n"+
      "\tJuicy steak  \t180 copper\n"+
      "\tRoast chicken\t150 copper\n\n"+
      "Try 'buy beer with gold' if you want to specify what to pay "+
      "with.\nYou can also do 'buy 10 beer' to get yourself ten beers "+
      "from the bar, but it takes a little while to give them all to " +
      "you.\nYou cannot buy more than 10 at a time.\n\n");

    return 1;
}

int
order(string str)
{
    string name,
    str1,
    str2,
    str3;

    int    *arr,
    price,
    num;

    notify_fail("The innkeeper isn't here to answer your call.\n");
    if (!jenn || !present(jenn, TO))
	return 0;

    notify_fail("Buy what?\n");
    if (!str)
	return 0;

    if (sscanf(str, "%s with %s and get %s", str1, str2, str3) != 3)
    {
	str3 = "";
	if (sscanf(str, "%s with %s", str1, str2) != 2)
	{
	    str2 = "";
	    str1 = str;
	}

    }

    if (sscanf(str1, "%d %s", num, str1) != 2)
    {
	num = 1;
	if(sscanf(str1, "%s", str1) != 1)
	    return 0;
    }

    if(num == 0)
    {
	jenn->command("say Are you an idiot? Only an idiot would come "+
	  "here and order 0 of something!");
	notify_fail("You didn't get anything.\n");
	return 0;
    }

    if (num > 10) num = 10;
    switch(str1)
    {
    case "beer":
    case "beers":
    case "kabal beer":
    case "kabal beers":
	name = "jei_beer";
	price = num * 24;
	break;

    case "wine":
    case "wines":
    case "ruby wine":
    case "ruby wines":
	name = "jei_wine";
	price = num * 120;
	break;

    case "orange":
    case "oranges":
    case "fresh orange":
    case "fresh oranges":
	name = "jei_orange";
	price = num * 30;
	break;

    case "steak":
    case "steaks":
    case "juicy steak":
    case "juicy steaks":
	name = "jei_steak";
	price = num * 180;
	break;

    case "chicken":
    case "chickens":
    case "roast chicken":
    case "roast chickens":
	name = "jei_chicken";
	price = num * 150;
	break;

    default: notify_fail("I don't understand what you want to buy.\n");
	return 0;
    }

    if (sizeof(arr = pay(price, this_player(), str2, test, 0, str3)) == 1)
	return 0;  /* pay() handles notify_fail() call */

    write("You pay " + text(exclude_array(arr, NUM, NUM*2-1)) + ".\n");
    if (text(exclude_array(arr, 0, NUM-1)))
	write("You get " + text(exclude_array(arr, 0, NUM-1)) + ".\n");
    write("The innkeeper gets to work.\n");

    return move_item(({name, num, TP}));
}

int
move_item(mixed arg)
{
    object drink,
    ob;

    string file,
    name;

    int    i,
    num;

    name = arg[0];
    num  = arg[1];
    ob   = arg[2];
    for (i = 0; i < 10; i++)
    {
	num--;
	file  = OBJ + name;
	drink = clone_object(file);

	if (!test && (drink->move(ob)))
	{
	    ob->catch_msg("You drop the " + drink->short()+
	      " on the floor.\n");
	    say(QCTNAME(ob) + " drops a " + drink->short()+
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
		    say(QCTNAME(ob) + " buys " + drink->short() + ".\n", ob);
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
	set_alarm(1.0, 0.0, "move_item", ({name, num, ob}));
    return 1;
}

int
test(string str)
{
    int    i;

    string str1;

    notify_fail("Test what?\n");

    if (sscanf(str, "buy %s", str1))
    {
	test = 1;
	write("This would be the result of a buy:\n\t");
	i = order(str1);
	test = 0;

	return i;
    }
}

leave_msg()
{
    TP->catch_msg("The sounds of drinking and merriment fade away.\n");
    return 0;
}
