/*
 *  The Tavern in Minas Tirith. 
 * /d/Gondor/minas/rooms/mttavern.c
 *  Modification history:
 *	28-Feb-98, Gnadnar:	inherit Gondor's inn, not /lib/trade
 *				conform to domain.rules
 *  30-April-2004, Tigerlily: Updated for ranger recode
 */

inherit "/d/Gondor/std/room";
inherit "/d/Gondor/common/lib/inn";

#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include <language.h>
#include "/d/Gondor/defs.h"

#ifndef NEW_RANGERS_OPEN
#define STAND_DIR   "/d/Gondor/common/guild/obj/"
#endif

#ifdef NEW_RANGERS_OPEN
#define  STAND_DIR  "/d/Gondor/guilds/rangers/obj/"
#endif

#define	MY_PRICES	({ 8, 12, 32, 70, 10, 21, 45, 210, 530 })
#define	CITIZEN		"/d/Gondor/minas/npc/citizen"

object *Citizens;


public void	create_gondor();
public void	reset_room();
public void	init();
public int	do_read(string str) ;
public string	price_long();
public int      buy_it(string item_name, int number, string pay_type,
                       string get_type);


/*
 * Function name:	create_gondor
 * Description	:	set up the room
 */
public void
create_gondor()
{
    set_short("The Sword and Shield Tavern");
    set_long(BSN(
	"You are in the Sword and Shield Tavern. This is the place the "
      + "citizens of Minas Tirith come to forget their sorrows over a beer, "
      + "and fill their empty stomachs with a nice, hot meal. The inn is "
      + "decorated with oak panels, and you can smell the odour of beer and "
      + "sweaty people from the walls. There are several tables here with "
      + "chairs beside them.  On the wooden floor lies the remains of a "
      + "rug, which is now worn out, covered with dirt, pipe ashes and "
      + "holes. A few lamps are hanging from the ceiling, creating a nice "
      + "atmosphere. By the north wall is a counter, behind which the "
      + "tavern keeper is standing.  Behind him is a pricelist and menu."));

    add_exit("/d/Gondor/minas/e1crc2", "west", 0, 0);

    add_item(({"rug", "remains of rug"}), BSN(
	"The rug was once beautiful and red, but now it is grey and full "
      + "of holes."));
    add_item(({"floor", "wooden floor"}), BSN(
	"The floor is covered with wooden tiles, now rather worn down "
      + "after serving their purpose for years. A hardly recognizable "
      + "rug lies over most of the floor, but years of use have caused "
      + "many holes to appear in it."));
    add_item(({"tiles", "wooden tiles"}), BSN(
	"The floor is covered with numerous wooden tiles, partially "
      + "covered by a decomposed rug."));
    add_item(({"ceiling", "lamps"}), BSN(
	"Hanging from the ceiling are some oil-lamps, providing both "
      + "light and a little warmth."));
    add_item(({"table","tables","chair","chairs"}),
	"All the tables and chairs are occupied.\n");
    add_item(({"oak panels", "panels", "wooden panels"}),
	"The scarred oak panels appear quite old.\n");
    add_item("counter", BSN(
	"Above the wooden counter is a lamp and a shelf. On the shelf " 
      + "are several brands of liquor. Behind the counter stands "
      + "Grimbold, the owner of the tavern."));
    add_item(({"innkeeper","tavern keeper","bartender","owner", "grimbold"}),
	BSN(
	"The tavern keeper, Grimbold, is a typical Dunadan, with a stern "
      + "face. He seldom takes a break, but runs between the kitchen "
      + "and the bar serving his customers, trying to keep the glasses as "
      + "shiny as possible, and the meals hot and delicious. Grimbold "
      + "looks at you, waiting for you to order something."));
    add_item(({"pricelist","list","prices","menu"}), price_long);

    add_prop(ROOM_I_INSIDE,1);
    config_default_trade();
    set_money_give_max(2000);
    set_money_give_out(({ 2000, 700, 50, 4}));
    set_money_give_reduce(({1,1,1,1}));
    set_innkeeper_name("the tavern keeper");

    Citizens = allocate(1 + random(2));
    reset_room();
}


/*
 * Function name:	reset_room
 * Description	:	clone up some citizens
 */
public void
reset_room()
{
    set_alarm(15.0 + rnd()*30.0, 0.0, &clone_npcs(Citizens, CITIZEN, 60.0));
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
 * Function name:	do_read
 * Description	:	handle attempts to read menu
 * Arguments	:	string str -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
public int
do_read(string str) 
{
    if (str == "pricelist" ||
	str == "list" ||
	str == "prices" ||
	str == "menu")
    {
	write(price_long());
	return 1;
    }
    return 0;
}

/*
 * Function name:	price_long
 * Description	:	describe the pricelist
 * Returns	:	string -- the description
 */
public string
price_long()
{
    return (
	"The pricelist reads:\n\n"
    + "DRINKS:\n"
    + "   Golden Ale           ...  " + MY_PRICES[0] + " copper coins\n"
    + "   Beer of the house    ...  " + MY_PRICES[1] + " copper coins\n"
    + "   Wine from Ithilien   ...  " + MY_PRICES[2] + " copper coins\n"
    + "   Whiskey from Rohan   ...  " + MY_PRICES[3] + " copper coins\n\n"
    + "HOT MEALS:\n"
    + "   Porridge             ...  " + MY_PRICES[4] + " copper coins\n"
    + "   Vegetable stew       ...  " + MY_PRICES[5] + " copper coins\n"
    + "   Bacon and beans      ...  " + MY_PRICES[6] + " copper coins\n"
    + "   Pheasant             ...  " + MY_PRICES[7] + " copper coins\n"
    + "   Stag steak           ...  " + MY_PRICES[8] + " copper coins\n\n");
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
	price = MY_PRICES[0];
	file = STAND_DIR + "ale";
	ware = "golden ale";
	break;
    case "beer":
	price = MY_PRICES[1];
	file = STAND_DIR + "tbeer";
	ware = "house beer";
	break;
    case "wine":
	price = MY_PRICES[2];
	file = STAND_DIR + "wine";
	ware = "white wine";
	break;
    case "whiskey":
	price = MY_PRICES[3];
	file = STAND_DIR + "whiskey";
	ware = "dry whiskey";
	break;
    case "porridge":
	price = MY_PRICES[4];
	file = STAND_DIR + "porridge";
	ware = "hot porridge";
	break;
    case "stew":
    case "vegetable stew":
    case "vegetable":
	price = MY_PRICES[5];
	file = STAND_DIR + "stew";
	ware = "vegetable stew";
	break;
    case "beans":
    case "bacon":
    case "beans and bacon":
	price = MY_PRICES[6];
	file = STAND_DIR + "beans";
	ware = "bacon and beans";
	break;
    case "pheasant":
	price = MY_PRICES[7];
	file = STAND_DIR + "pheasant";
	ware = "fried pheasant";
	break;
    case "stag":
    case "steak":
    case "stag steak":
	price = MY_PRICES[8];
	file = STAND_DIR + "steak";
	ware = "stag steak";
	break;
    default:
    	notify_fail("The tavern keeper says: "
		  + "We don't have that on the menu.\n");
	return 0;
    }
    if (can_afford(price, number, ware, pay_type, get_type))
                buy_item(file, number);
    return 1;
}
