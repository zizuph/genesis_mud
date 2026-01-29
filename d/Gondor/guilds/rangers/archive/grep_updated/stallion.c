/*
 *  The Sleeping Stallion
 *  
 *  copied from the Seven Stars Inn
 *
 *  created by unknown (Elessar?)
 *  modified for The Sleeping Stallion by Olorin on 6-jan-93
 *
 * Gnadnar 2-Dec-1997:
 *	check combat on both exits 
 *	don't block exit if only opponents are players
 *	vary descriptions so this isn't a duplicate of the seven stars
 *	conform to coding standards
 * Gnadnar 15-Feb-1998:
 *	inherit /d/gondor/common/lib/inn, rather than /lib/trade
 * Tigerlily, April 24, 2004:
 *   modified for ranger recode
 */
#pragma strict_types

inherit "/d/Gondor/std/room.c";
inherit "/d/Gondor/common/lib/inn.c";

#include <macros.h>
#include <money.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#ifndef NEW_RANGERS_OPEN
#define STAND_DIR   "/d/Gondor/common/guild/obj/"
#endif

#ifdef NEW_RANGERS_OPEN
#define STAND_DIR  "/d/Gondor/guilds/rangers/obj/"
#endif

#define MY_PRICES   ({ 9, 15, 40, 100, 10, 24, 50, 240, 550, 144})
#define NUM         sizeof(MONEY_TYPES)
#define HOTEL_KEY   (EDORAS_DIR + "obj/hotel_key")

static object	Funohed, 
		Fastred, 
		Citizen;

public void	create_gondor();
public void	reset_room();
public void	init();
static string	price_long();
public int	do_read(string str);
public void     buy_item(string item, int number, string desc);
public int	check_combat();

/*
 * Function name:	create_gondor
 * Description	:	create the room
 */
public void
create_gondor()
{
    set_short("The Sleeping Stallion");
    set_long(BSN(
	"The Sleeping Stallion is the local inn; it gets its custom from "
      + "Rohirrim farmers and from traders visiting Edoras.  There are "
      + "plenty of tables and chairs, and oil lamps suspended from the "
      + "walls cast a warm light over the room.  The bill of fare is "
      + "posted above a wooden counter; beyond the counter, stairs lead "
      + "to the upper floor of the inn."));

    add_item( ({ "sleeping stallion", "room", "inn" }), long);
    add_item(({"table","tables"}),
	"The tables show signs of long use, but are quite clean.\n");
    add_item(({"chair", "chairs"}),
	"The chairs look comfortable.\n");
    add_item( ({ "counter", "wooden counter", "bar" }), BSN(
	"The chest-high counter is built of dark, polished wood; "
      + "it appears to serve as the bar. "
      + "The inn's bill of fare hangs on the wall above the counter."));
    add_item( ({ "wooden floor", "floor" }), BSN(
	"The wooden floor appears recently swept."));
    add_item( ({ "plaster wall", "plaster walls", "plaster", 
	"wall", "walls" }), BSN(
	"The smooth plaster walls gleam with the light "
      + "from the oil lamps."));
    add_item( ({ "oil lamp", "oil lamps", "light", "lamp", "lamps" }),
	"The lamps provide a warm, cheerful light.\n");
    add_item("ceiling",
	"The ceiling is not far overhead.\n");
    add_item( ({ "upper floor", "stair", "stairs" }),
	"Narrow wooden stairs lead to the upper floor.\n");

    add_item(({"pricelist","list","prices","menu","bill","bill of fare"}),
	price_long());
    add_exit(EDORAS_DIR + "stairs2", "west", check_combat, 1);
    add_exit(EDORAS_DIR + "hotelr", "up", check_combat, 2);
    add_prop(ROOM_I_INSIDE,1);
    config_default_trade();
    set_money_give_max(2000);
    set_money_give_out(({ 2000, 700, 50, 4}));
    set_money_give_reduce(({1,1,1,1})); 
    clone_object(EDORAS_DIR + "rooms/inndoorin")->move(TO);
    reset_room();
}

/*
 * Function name:	reset_room
 * Description	:	restore npcs as needed
 */
public void
reset_room()
{
    Funohed = clone_npc(Funohed, EDORAS_DIR + "npc/funohed");
    Citizen = clone_npc(Citizen, EDORAS_DIR + "npc/inncitizen");
    Fastred = clone_npc(Fastred, EDORAS_DIR + "npc/fastred");

    if ( objectp(present(Fastred, TO)) )
    {
	Fastred->command("unlock door with key");
	set_innkeeper_npc(Fastred);
    }
}


/*
 * Function name:	init
 * Description	:	add player verbs
 */
public void
init()
{
    ::init();
    ::init_inn();
    add_action(do_read, "read");
}


/*
 * Function name:	price_long
 * Description	:	describe the bill of fare
 * Returns	:	string -- the description
 */
static string
price_long() 
{
    return (
	"The pricelist reads:\n\n"
      + "DRINKS:\n"
      + "   Golden Ale            ...  " + MY_PRICES[0] + " copper coins\n"
      + "   Rohan Beer            ...  " + MY_PRICES[1] + " copper coins\n"
      + "   Wine from Ithilien    ...  " + MY_PRICES[2] + " copper coins\n"
      + "   Whiskey from Rohan    ...  " + MY_PRICES[3] + " copper coins\n\n"
      + "HOT MEALS:\n"
      + "   Porridge              ...  " + MY_PRICES[4] + " copper coins\n"
      + "   Vegetable stew        ...  " + MY_PRICES[5] + " copper coins\n"
      + "   Bacon and beans       ...  " + MY_PRICES[6] + " copper coins\n"
      + "   Pheasant              ...  " + MY_PRICES[7] + " copper coins\n"
      + "   Stag steak            ...  " + MY_PRICES[8] + " copper coins\n\n"
      + "ROOMS:\n"
      + "   Key for a room        ...  " + MY_PRICES[9] + " copper coins\n\n");
}


/*
 * Function name:	do_read
 * Description	:	handle attempts to read bill of fare
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
public int
do_read(string arg) 
{
    if (!strlen(arg))
	return 0;
    if (arg == "bill of fare" || arg == "pricelist" ||
    arg == "list" || arg == "prices" || arg == "menu")
    {
	write(price_long());
	return 1;
    }
    return 0;
}



/*
 * Function name: buy_it
 * Description:   identify the item the player tries to buy
 * Arguments:     item_name - the name
 *                number    - the amount
 *                pay_type  - coins to pay with
 *                get_type  - coins for change
 * Returns:       0/1 - failure/success
 */
public int
buy_it(string item_name, int number, string pay_type, string get_type)
{
    string	file,
		ware;
    int		price;


    switch (item_name)
    {
    case "golden":
    case "ale":
    case "golden ale":
	    file = STAND_DIR + "ale";
	    ware = "golden ale";
	    price = MY_PRICES[0];
	break;
    case "beer":
	    file = STAND_DIR + "beer";
	    ware = "Rohan beer";
	    price = MY_PRICES[1];
	break;
    case "wine":
	    file = STAND_DIR + "wine";
	    ware = "white wine";
	    price = MY_PRICES[2];
	break;
    case "whiskey":
	    file = STAND_DIR + "whiskey";
	    ware = "dry whiskey";
	    price = MY_PRICES[3];
	break;
    case "porridge":
	    file = STAND_DIR + "porridge";
	    ware = "hot porridge";
	    price = MY_PRICES[4];
	break;
    case "stew":
    case "vegetable stew":
    case "vegetable":
	    file = STAND_DIR + "stew";
	    ware = "vegetable stew";
	    price = MY_PRICES[5];
	break;
    case "beans":
    case "bacon":
    case "beans and bacon":
	    file = STAND_DIR + "beans";
	    ware = "bacon and beans";
	    price = MY_PRICES[6];
	break;
    case "pheasant":
	    file = STAND_DIR + "pheasant";
	    ware = "fried pheasant";
	    price = MY_PRICES[7];
	break;
    case "stag":
    case "steak":
    case "stag steak":
	    file = STAND_DIR + "steak";
	    ware = "stag steak";
	    price = MY_PRICES[8];
	break;
    case "room":
    case "key":
    case "single room":
    case "night":
	    if (number > 1 )
	    {
		write(Fastred->query_The_name(TP)+" stares at you.\n"+
		    Fastred->query_The_name(TP)+
		    " says: I only rent one room per person.\n");
		return 1;
	    }
	    file = HOTEL_KEY;
	    ware = "a single room to spend the night in Edoras";
	    price = MY_PRICES[9];
	break;
    default:
	NF0(Fastred->query_The_name(TP)+
	    " says: We don't have that on the menu.\n");
    }
    if (can_afford(price, number, ware, pay_type, get_type))
	buy_item(file, number, ware);
    return 1;
}


/*
 * Function name: buy_item
 * Description:   clone and move the bought item
 *		  mask parent to handle room keys.
 * Arguments:     item   - filename of item to clone
 *                number - heap size of item
 *                desc   - description for item
 */
void
buy_item(string item, int number = 1, string desc = 0)
{

    object	ob,
		tp = TP;

    if (item == HOTEL_KEY)
    {
	SAY(" bespeaks a room for the night.");
	ob = clone_object(item);
	if (!ob->move(tp))
	{
	    write(Fastred->query_The_name(tp)
	        + " gives you the key to the room. Don't lose it!\n");
	    say(QCTNAME(Fastred) + " gives a key to "+QTNAME(tp)+".\n");
	}
	else
	{
            WRITE("Since you cannot carry the key, "
	        + Fastred->query_the_name(tp) + " puts it down on a table.");
            if (ob->move(TO))
                ob->move(TO, 1);
	}
	return;
    }
    ::buy_item(item, number, desc);
}



/*
 * Function name:	check_combat
 * Description	:	if player is fighting any npcs, block exit
 * Returns	:	0 if player may leave, 1 if not
 */
public int
check_combat()
{
    object	*enemy;
    int		s;
    
    enemy = TP->query_enemy(-1);
    s = sizeof(enemy);
    while ( s-- > 0 )
    {
        if ( objectp(enemy[s]) &&
             enemy[s]->query_npc() &&
             ENV(enemy[s]) == TO )
	{
	    write(enemy[s]->query_The_name(TP) + " stops you!\n");
	    say(QCTNAME(enemy[s])+" stops "+QTNAME(TP)+"!\n", TP);
	    return 1;
	}
    }
    return 0;
}
