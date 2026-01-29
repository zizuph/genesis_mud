/* 
 * An example shop coded by Nick, some Ideas and part of code taken from 
 * Tricky's shop in hobbitown solamnian modifications by percy
 * thief fence modifications by Aridor
 */

#include "guild.h"

inherit ROOM_BASE
inherit "/lib/shop";

#include <macros.h>
#include <composite.h>
#define OTHER           CAVERN + "pass4"
#define STORE_ROOM	GUILDR + "store"

object fence;

/*
 * Function name:   create_room
 * Description:     Initialize this room
 */
void
create_thief_room()
{
    config_default_trade();
    set_money_greed_buy(80);
    set_money_greed_sell(99);
    set_short("The Fence");
    set_long("You are in the undercover shop of the Cabal of Hiddukel. " +
	     "Here a Thief can fence things for a fair price. There is " +
	     "a small sign to read with instructions on how to use " +
	     "this institution. There is also a small bell on the counter. " +
	     "A door leads northeast outside the guild.\n");

    add_cmd_item("sign", "read", "@@do_read");
    add_item("sign", "A nice looking sign, perhaps you should read it.\n");
    add_item(({"bell", "small bell"}),
	     "It's a crude brass bell, perhaps you could ring it?\n");
    add_item(({"door"}),"It's a metal door set into the rock leading out " +
	     "of the guild.\n");
    add_exit(GUILDR + "train", "southwest");
    add_exit(GUILDR + "start", "west");
    add_exit(OTHER, "northeast","@@open_the_door");
    add_exit(STORE_ROOM, "down", "@@wiz_check");
    
    
    INSIDE;  /* This is a real room */
    LIGHT;
    
    set_store_room(STORE_ROOM);

}



/*
 * Function name:   init
 * Description:     Is called for each living that enters this room
 * Returns:
 */
void
init()
{
    	::init();   /* You MUST do this in a room-init */
    	init_shop(); /* Get the commands from the shop */
	add_action("do_ring", "ring");
}

/*
 * Function name:	reset_room
 * Description:		Is called to reset the shopkeeper and room.
 * Returns:
 */
void
reset_thief_room()
{
	if (!fence)
	{
		fence = clone_object(TOBJ + "shopkeeper.c");
		fence->move(TO);
	}
}

int
do_buy(string str)
{
	if (!(present("almath", this_object())))
	{
		write("The fence isn't here to deal with you.\n");
		return 1;
	}
	return ::do_buy(str);
}

int
do_sell(string str)
{
	if (!(present("almath", this_object())))
	{
		write("The fence isn't here to deal with you.\n");
		return 1;
	}
	return ::do_sell(str);
}

do_value(string str)
{
	if (!(present("almath", this_object())))
	{
		write("The fence isn't here to deal with you.\n");
		return 1;
	}
	return ::do_value(str);
}

void
init_shop()
{    	
    add_action(do_read, "read");
    add_action(do_list, "list");
    add_action(do_buy, "buy");
    add_action(do_sell, "fence");
    add_action(do_value, "value");
    add_action(do_show,  "show");
    add_action(do_store, "store");
}

int
do_ring(string str)
{
    notify_fail("Ring what?\n");
    if ((str == "bell") || (str == "brass bell"))
      {
	  write("You ring the bell. The bell clanks surprisingly soft.\n");
	  say(QCTNAME(TP) + " clanks the bell on the counter.\n");
	  
	  if (!fence)
	    {
		reset_room();
		tell_room(this_object(), "The fence appears out of nowhere " +
			  "to serve you.\n");
		return 1;
	    }
	  
	  fence->command("say You there! Leave that bell alone.");
	  return 1;
      }
    
    return 0;
}

int
open_the_door()
{
    SAY(" opens the door.");
    tell_room(OTHER,"The door opens.\n");
    write("You open the door, walk through, and close the door again.\n");
    set_alarm(1.0,0.0,"close_again",TP);
    return 0;
}

void
close_again(object who)
{
    tell_room(TO,"The door closes again.\n");
    TELL_ROOM(OTHER, who, " closes the door.\n", who);
}

/*
 * Function name: shop_hook_sold_items
 * Description:   Hook that is called when player sold something
 * Arguments:	  item - The item array player sold
 * Returns:	  1
 */
int
shop_hook_sold_items(object *item)
{
    write(break_string("You fenced " + COMPOSITE_DEAD(item) + ".\n", 75));
    say(QCTNAME(this_player()) + " fenced " + QCOMPDEAD + ".\n");
    return 1;
}
/*
 * Function name: shop_hook_sold_nothing
 * Description:   Function called if player sold nothing with sell all
 * Returns:	  0
 */
int
shop_hook_sold_nothing()
{
    notify_fail("You didn't fence anything.\n");
    return 0;
}
/*
 * Function name: do_read
 * Description:   If a player wants to know what instuctions can be
 *                used
 * Arguments:     str - string, hopefully "sign"
 * Returns:       1/0
 */
int
do_read(string str)
{
    notify_fail("Read what?\n");
    if (str != "sign")
	return 0;

    write("" +
	  "You can try these instructions: \n" +
	  "    buy knife for gold and get copper back\n" +
	  "    buy knife for gold coins\n" +
	  "    fence knife for copper coins\n" +
	  "    fence all  - will let you sell all items except for\n" +
	  "                items you wield or wear.\n" +
	  "    fence all! - will let you sell ALL items you have, well\n" +
	  "                at least the dropable, and no coins.\n" +
	  "    fence knife, fence second knife, fence knife 2, fence two knife\n" +
	  "                also works. You might want to change the verb to\n" +
	  "                'value' or 'buy' too. Beware, you will never buy\n"+
	  "                more than one item at a time. So if you really\n" +
	  "                those three expensive knives, you have to repeat\n" +
	  "                yourself three times.\n" +
	  "    show knife - will let you examine the knife in the store.\n" +
	  "    If you want a list of all knives available in the store, the\n" +
	  "    correct syntax is: list knives\n" +
	  "                'list weapons', 'list armours' also works\n" +
	  "");
    return 1;
}
