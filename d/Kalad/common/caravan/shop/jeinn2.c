#include "../default.h"

inherit CVAN_ROOM;
inherit "/lib/trade";

#include <money.h>

#define NUM sizeof(MONEY_TYPES) /* How many types of money do we use? */

void
create_cvan_room()
{
    config_default_trade();

    set_short("Room within the Journey's End Inn");
    set_long("You find yourself within one of the bedrooms on the second "+
      "floor of the Journey's End Inn, where tired travellers may rent a "+
      "room to refresh themselves for the next time they venture out into "+
      "the cruel world. Several beds lie around the room. A small sign hangs "+
      "upon the wall.\n"+
      "An attendant stands here.\n");
    add_item(({"beds", "bed"}), "It looks quite comfortable.\n");
    add_item(({"sign", "@@sign"}), "It has lots of readable words.\n");
    add_item(({"attendant"}), "A small, helpful looking man that is here "+
      "to watch the room.\n");

    add_exit(CVAN + "shop/jeinn1", "west");

    add_prop(ROOM_I_INSIDE, 1);
}

string
sign()
{
    return "\n" +
    "                     ______________________\n"+
    "                    [                      ]\n"+
    "                    [   For the minor fee  ]\n"+
    "                    [ of but one gold coin ]\n"+
    "                    [  you may rent a room ]\n"+
    "                    [    and begin your    ]\n"+
    "                    [  journeys here when  ]\n"+
    "                    [   you wish to face   ]\n"+
    "                    [ the world once more. ]\n"+
    "                    [ (of course you will) ]\n"+
    "                    [ (have to pay once  ) ]\n"+
    "                    [ (again if you want ) ]\n"+
    "                    [ (to start here again)]\n"+
    "                    -----------------------\n";
}

/*
 * Function name: rent
 * Description:   rents the room and quits the player from the game.
 */
int
rent(string str)
{
    NF("Rent what?\n");
    if (str == "room")
    {
	if (!present("gold coin", TP))
	{
	    write("The attendant says: We only accept gold for renting a room.\n");
	    return 1;
	}

	if (!MONEY_MOVE(1, "gold", TP, 0))
	{
	    write("You pay 1 gold coin for the room.\n");
	    this_player()->set_temp_start_location(CVAN + "shop/jeinn2");
	    return 1;
	}
	return 0;
    }
    return 0;
}

void
init()
{
    ::init(); /* Since it's a room this must be done. */
    add_action(rent, "rent");
    add_action(read_sign, "read");
}
