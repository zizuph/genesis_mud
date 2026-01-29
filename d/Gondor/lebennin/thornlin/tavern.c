/*
 *  The Tavern in Thornlin, based on the MT tavern. 
 *  Original author uncertain
 *  Modification history:
 *	28-Feb-98, Gnadnar:	inherit Gondor's inn, not /lib/trade
 *				conform to domain.rules
 *      31-Dec-00  Auberon:     Changed food and drink, npcs, and descs
 *                              to be suitable for Thornlin.
 */

/*
 * The code that follows is the work of more than one person.
 * Without commenting on the rights of any other authors, this
 * is in significant part copyright (c) 2000 by Scott A. Hardy,
 * whose intellectual property rights are in  no way forfeited
 * or transferred.  The portions coded by Scott Hardy are on
 * loan to Genesis (a game run by Chalmers University), who by
 * using and storing it on their system, acknowledge and agree
 * to all of the above.
 */

#include "/d/Gondor/defs.h"
inherit (STD_DIR + "room");
inherit (LIB_DIR + "inn");

#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include <language.h>

#define	MY_PRICES	({ 8, 12, 32, 70, 10, 21, 45, 210, 530 })

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
    set_short("The Man in the Moon Public House");
    set_long(
      "The Man in the Moon pub has been the place where the citizens "
      + "of Lossarnach have come on all social occasions for generations.  "
      + "A clear part of the room looks as if few couples might dance there "
      + "occasionally, and the rest of the time those who cannot get "
      + "one of the few tables may stand and enjoy the fare.  Oil lamps "
      + "light the room -- considering the price of oil, business must "
      + "be good.  Straw covers the floor, but you see wood rather than "
      + "dirt beneath, another testimony to the popularity of the pub.  "
      + "Against one wall is a counter, with the tavern keeper and a "
      + "pricelist right behind it.\n");

    add_exit(THORN_DIR+"bank", "south", 0, 0);

    add_item(({"straw"}), 
      "The straw is fresh and clean, and has a few herbs mixed in to "
      + "repel fleas.\n");
    add_item(({"floor", "wooden floor"}), 
      "The floor consists of old and stained, but very thick pine.  "
      + "It's nothing special to look at, but should last a century, "
      + "termites willing.\n");
    add_item(({"ceiling", "lamps"}), 
      "Hanging from the ceiling are some oil-lamps, providing both "
      + "light and a place to warm one's hands.\n");
    add_item(({"table","tables","chair","chairs"}),
      "The few tables and chairs are in use.\n");
    add_item("counter", 
      "Above the wooden counter is a lamp and a shelf. On the shelf " 
      + "are several types of beverage. Behind the counter stands "
      + "the owner of the tavern.\n");
    add_item(({"innkeeper","tavern keeper","bartender","owner","keeper"}),
      "The tavern keeper is a typical resident of the area, "
      + "looking like he has some Dunadan blood, but probobly not "
      + "a whole lot.  He is middle-aged, plump, but looks like he "
      + "can still fend for himself quite well.  He "
      + "looks at you, waiting for you to order something.\n");
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
    set_alarm(15.0 + rnd()*30.0, 0.0, &clone_npcs(Citizens, THORN_DIR + "npc/citizen", 60.0));
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
    if (!strlen(str))
    {
	return 0;
    }

    if (!parse_command(str, ({}), "'pricelist' / 'list' / 'prices' / 'menu'"))
    {
	return 0;
    }
    else
    {
	write(price_long());
	return 1;          
    }
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
      + "   Lemonade             ...  " + MY_PRICES[0] + " copper coins\n"
      + "   Red Ale              ...  " + MY_PRICES[1] + " copper coins\n"
      + "   Wine from Lebennin   ...  " + MY_PRICES[2] + " copper coins\n"
      + "   Wrath of the Gods    ...  " + MY_PRICES[3] + " copper coins\n\n"
      + "HOT MEALS:\n"
      + "   A Roll               ...  " + MY_PRICES[4] + " copper coins\n"
      + "   Vegetable Stew       ...  " + MY_PRICES[5] + " copper coins\n"
      + "   Bread and Cheese     ...  " + MY_PRICES[6] + " copper coins\n"
      + "   Half a Chicken       ...  " + MY_PRICES[7] + " copper coins\n"
      + "   Lobster Dinner       ...  " + MY_PRICES[8] + " copper coins\n\n");
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
    case "lemonade":
	  price = MY_PRICES[0];
	  file = THORN_DIR + "obj/lemonade";
	  ware = "lemonade";
	  break;
    case "ale":
	  price = MY_PRICES[1];
	  file = THORN_DIR + "obj/red_ale";
	  ware = "red ale";
	break;
      case "wine":
	  price = MY_PRICES[2];
	  file = THORN_DIR + "obj/wine_from_lebennin";
	  ware = "red wine";
	  break;
    case "wrath":
	  price = MY_PRICES[3];
	  file = THORN_DIR + "obj/wrath_of_the_gods";
	  ware = "wrath of the gods";
	  break;
    case "roll":
    case "a roll":
	  price = MY_PRICES[4];
	  file = THORN_DIR + "obj/roll";
      ware = "roll";
	  break;
    case "stew":
    case "vegetable stew":
    case "vegetable":
	  price = MY_PRICES[5];
	  file = STD_DIR + "food/stew";
	  ware = "vegetable stew";
	  break;
    case "bread":
    case "cheese":
    case "bread and cheese":
	  price = MY_PRICES[6];
	  file = THORN_DIR + "obj/bread_and_cheese";
	  ware = "bread and cheese";
	  break;
    case "half a chicken":
    case "half":
    case "chicken":
	  price = MY_PRICES[7];
	  file = THORN_DIR + "obj/chicken";
	  ware = "half a roast chicken";
	  break;
    case "lobster dinner":
    case "lobster":
    case "dinner":
	  price = MY_PRICES[8];
	  file = THORN_DIR + "obj/lobster";
	  ware = "4-course lobster dinner";
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
