// file name:        junk.c
// creator(s):       Grace
// revision history: Denis, May'97: Regular updates, corrected shopkeeper
//				    not wearing stuff.
// purpose:          
// note:             
// bug(s):           
// to-do:            

# pragma strict_types

inherit "/std/room";
inherit "/lib/trade";

# include "../bazaar.h"
# include <macros.h>
# include <money.h>
# include "/d/Avenir/include/relation.h"

# define NUM           sizeof(MONEY_TYPES)

/* Prototypes
 */
void reset_room();

/* Globals
 */
static object junker;

void
create_room()
{
    config_default_trade();

    set_short("A small three-sided tent");
    set_long("This is a dingy little tent with three sides. "+
        "It is little protection from the noise and bustle "+
        "of the Bazaar. It is cluttered with piles of junk, "+
        "most of which is so useless as to be unrecognizable. "+
        "There is a smudged, handwritten list tacked to a pole. "+
        "\n");

    add_item(({ "sign", "list", "handwritten list" }), "@@read_list");
    add_cmd_item(({ "sign", "list" }), "read", "@@read_list");
    add_item(({"pole","wood"}),"It looks like it was salvaged "+
        "from the deck of a sailboat. There is a note pinned to it.\n");
    add_item(({"wall","walls"}),"The walls are made of dingy canvas.\n");
    add_item(({"floor","ground"}),"Filty!\n");
	
	IN;       // Avenir is an undergound domain.
	IN_IN;    // Interior room, no flux msgs, steeds etc.

    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1); 
 
    reset_room();

    add_exit(EXTR + "str20", "out");
}

string
read_list()
{
    return "\n\nJunk in condition to be sold:\n\n"+
    "     A back scratcher --------------------------  100 cc\n"+
    "     A toothpick -------------------------------   15 cc\n"+
    "     A pair of bunny slippers ------------------  200 cc\n"+
    "     A pair of thumbscrews ---------------------  300 cc\n"+
    "\n";
}

void
reset_room()
{
    if (!junker)
    {
        junker = clone_object(NPC + "junker");
	junker->arm_me();
    }
    if (!present(junker))
        junker->move(this_object());
}

int
do_buy(string str) 
{
    object order;
    string str1, str2, str3;
    int *arr, price, silent, i;

    if (!str)
    {
	notify_fail("Buy 'item' with 'type of money' and get 'type of money'.\n");
	return 0;
    }
    if (!junker || (!present(junker)))
    {
	notify_fail("There is no-one here to buy anything from.\n"+
		    "The old junker has been killed!\n");
	return 0;
    }
    if (IS_INFIDEL(this_player()))
    {
        tell_object(this_player(), "The shopkeeper refuses to trade with "+
           "criminals.\n");
        return 1;
    }
    if (sscanf(str, "%s with %s and get %s", str1, str2, str3) != 3)
    {
        str3 = "";
        if (sscanf(str, "%s with %s", str1, str2) != 2)
	{
            str2 = "";
            str1 = str;
	}
  }

    switch (str1)
    {
    case "scratcher":
    case "back scratcher":
    case "backscratcher":
    case "1":
	order = clone_object(WIELD + "scratcher");
	price = 100;
	break;

    case "toothpick":
    case "pick":
    case "2":
	order = clone_object(BAZAAR + "Obj/misc/toothpick");
	price = 15;
	break;

    case "slippers":
    case "bunny slippers":
    case "pair of bunny slippers":
    case "3":
	order = clone_object(WORN + "bunnyslip");
	price = 200;
	break;

    case "screw":
    case "thumbscrews":
    case "pair of thumbscrews":
    case "4":
	order = clone_object(WORN + "thumbscrew");
	price = 300;
	break;

    default:
       notify_fail("Buy 'item' with 'type of money' and get "+
                   "'type of money'.\n");
       return 0;
    }

    arr = pay(price, 0, str2, 0, 0, str3, 0);

    if (sizeof(arr) == 1)
    {
        if (arr[0] == 1)
	    notify_fail("You have to give me more to choose from.\n");
        else
	    if (arr[0] == 2)
		notify_fail("You don't carry that kind of money!\n");
	    return 0;
    }

    write("You pay " + text(exclude_array(arr, NUM, NUM*2-1)) + ".\n");
    if (text(exclude_array(arr, 0, NUM-1)))
    {
	write("You get " + text(exclude_array(arr, 0, NUM-1)) + ".\n");
	say(QCTNAME(this_player())+" and " + QCTNAME(junker)+" exchange "+
	    "some coins.\n");
    }
    else
	say(QCTNAME(this_player())+" gives "+QCTNAME(junker)+" some money.\n");

    write("The shopkeeper hands you "+order->short()+".\n");
    say(QCTNAME(junker)+" hands "+QCTNAME(this_player())+" "+
	order->short()+".\n"); 

    if (order->move(this_player()))
    {
	write("You drop the " + order->short() + " on the floor.\n");
	say(QCTNAME(this_player())+" drops a " + order->short()+" on the "+
	    "floor.\n");
	order->move(this_object());
    }
    return 1;
}

public int
do_list(string str)
{
    write(read_list());
    return 1;
}

void
init()
{
    ::init();
    add_action(do_buy, "buy");
    add_action(do_buy, "order");
    add_action(do_list, "list");
}

/*
 * Function name: 
 * Description:   
 * Arguments:     
 * Returns:       
 */
