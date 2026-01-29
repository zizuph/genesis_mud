/* Modified copy of inn in solace, coded by Nick */
/* Improved (?) by Ged & Gresolle */
/* Modified for Athas by Anton */

inherit  "/std/room";
inherit "/lib/trade";

#include "/d/Roke/common/defs.h"
#include <macros.h>
#include <money.h>

#define NUM sizeof(MONEY_TYPES) /* How many types of money do we use? */

int test; /* to indicate that a test is going on, no money given. */
object tika; /* reseptionist */

int move_item(mixed arg);
                  
/*
 * Function name: reset_room
 * Description:   Set up the objects at reset
 */
void
reset_room()
{
    if (!tika)
    {
	tika = clone_object(A_NPC_D+"innkeeper");
	tika->move_living("xxx", TO);
    }
    
}

/*
 * Function name: create_room
 * Description:   Set up default trade and cofigure it if wanted.
 */
void
create_room()
{
    config_default_trade();
	set_short("The Elfstone Inn");
	set_long(BSS("You have entered the reception of the Elfstone "+
		"Tavern and Inn. Here you can rent a room, where you "+
		"could stay until the next time you arrive. The price is "+
		"only 110 copper coins and the rooms are upstairs.\n"));

	add_exit(INNS_D+"inn1","east",0);
	add_exit(INNS_D+"inn1c","up","@@block");

    add_prop(ROOM_I_INSIDE,1);  /* This is a real room */
    reset_room();
}

block()
{
  if(!(present("tjop_dej_rom",TP)))
    {
      write("You don't have a key to a room here!!!\n");
      return 1;
    }
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
    add_action("order", "rent");
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

    NF("The receptionist isn't here to answer your call.\n");
    if (!tika || !P(tika, TO))
	return 0;

    NF("Rent what?\n");
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

    if (num > 10) num = 10;

    switch(str1)
    {
    case "room":
    case "hotel room":
      name = "key";
	price = 110;
	break;
    default:
        NF("I don't understand what you want to rent.\n");
        return 0;
    }

    if (sizeof(arr = pay(price, this_player(), str2, test, 0, str3)) == 1)
        return 0;  /* pay() handles notify_fail() call */
    
    write("You pay " + text(exclude_array(arr, NUM, NUM*2-1)) + ".\n");
    if (text(exclude_array(arr, 0, NUM-1)))
        write("You get " + text(exclude_array(arr, 0, NUM-1)) + ".\n");
    write("The receptionist starts to look for something.\n");

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
    	file = A_OBJ_D + name;
    	drink = clone_object(file);

    	if (!test && (drink->move(ob)))
    	{
	    ob->catch_msg("You drop the " + drink->short() +
	    	" on the floor.\n");
	    say(QCTNAME(ob) + " drops a " + drink->short() +
	    	" on the floor.\n", ob);
            drink->move(TO);
    	} else if (!test) {
	    if (num == 0)
	    {
		if (arg[1] > 1)
		{
		    ob->catch_msg("You get some " + drink->plural_short() +
			".\n");
		    say(QCTNAME(ob) + " buys some " + drink->plural_short() +
			".\n", ob);
		} else {
              	    ob->catch_msg("You get a " + drink->short() + ".\n");
       		    say(QCTNAME(ob) + " buys " + drink->short() + ".\n",
			ob);
		}
	    }
    	} else {
            say(QCTNAME(ob) + " seems to be estimating something.\n",
		ob);
	return 1;
    	}
	if (num < 1)
	    break;
    }

    if (num > 0)
	call_out("move_item", 1, ({name, num, ob}));
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
    
    if (sscanf(str, "buy %s", str1)) {
        test = 1;
        write("This would be the result of a buy:\n");
        i = order(str1);
        test = 0;
        return i;
    }
}


