/*
 * Ckrik June, 2014
 *
 */

#pragma strict_types
#pragma no_clone

#include "defs.h"
inherit THWIL_BASE_ROOM;
inherit "/lib/unique";
inherit "/lib/pub";
inherit "/sys/global/money";

#include <macros.h>
#include <stdproperties.h>

public void
create_thwil_room()
{
	set_short("The Wizard's Pub");
	set_long("The small pub is filled with locals and " +
			"serves as the informal gathering " +
			"place of the town folks in Thwil. You see shepherds, " +
			"shop keepers and wizards sitting down together at large " +
			"communal tables surrounding a hearth at the center of " +
			"room. You notice gnarled-wood staff resting " +
			"against the wall and a menu hanging next to it.\n");
	add_item("hearth", "A blazing fire burns in the" +
			" hearth, spreading light and a pleasant heat" +
			" across the large room.\n");
	add_item("tables", "This tavern is furnished with" +
			" long tables and benches, where the visitors can" +
			" sit and enjoy their meal or drink.\n");
	add_item(({"shepherds", "shepherd"}),
			"You see several shepherds in the pub. A middle-aged " +
			"unkempt shepherd obviously has had a little too much " +
			"to drink and slouched over a table in the corner.\n");
	add_item(({"unkempt shepherd", "middle-aged shepherd", "drunk shepherd"}),
			"The shepherd stammers about beating a boy if he loses " +
			"another sheep.");
	add_item(({"gnarled-wood staff", "staff"}),
			"One of patrons of the pub must have placed it here.\n");
	add_item("menu","@@read_menu");
	add_cmd_item("menu","read","@@read_menu");
	add_cmd_item("staff", ({"get", "take"}),
			"As you approach the staff you get an " +
			"uneasy feeling and decide against it. You turn back " +
			"and notice smiling wizard in a blue cloak looking at you. Whew! " +
			"Good thing you did not take the staff, the wizard probably " +
			"would have turned you into an otak or something worse.\n");
	add_exit(THWIL + "h8", "east", 0);
	add_drink(({"water","glass of water"}), ({"glass of water","water"}),
			({"refreshing", "ice-cold"}), 200, 0, 5, "glass of water",
			"glasses of water","A glass of water filled" +
			" to the brim with ice cold water, probably" +
			" fetched just recently from one of the" +
			" wells of Roke. Very refreshing!\n");
	add_drink(({"wine","imported sweet wine"}),"wine",
			({"light", "imported", "sweet"}), 20, 60, 80,
			"light imported sweet wine",
			"light imported sweet wines","The light imported sweet wine is" +
			" served in a fancy glass, with a full" +
			" fruity smell and a long finish.\n");
	add_drink(({"grog", "Gontish grog", "gontish grog"}),
			"grog", ({"gontish", "Gontish"}), 20, 20, 75, "Gontish grog",
			"Gontish grogs", "This is a deep-brown, strong drink " +
			"favoured by the seamen and pirates of Gont. The precise " +
			"ingredients are unknown, however, it smells strongly of " +
			"dark rum and whiskey.\n");
	add_drink(({"beer","roke beer"}), "beer",
			({"roke", "Roke"}), 5, 120, 200, "Roke beer",
			"Roke beers","A small mug filled with " +
			"strong beer made from malted barley and " +
			"smells of toasted hops. It smells stronger than spirits and " +
			"must have been brewed with the help of magic.\n");
	add_food(({"herring", "smoked herring"}), "herring",
			({"smoked"}), 30, 25, "smoked herring",
			"smoked herrings", "This is a smoked herring, which has " +
			"been lightly fried in butter.\n");
	add_food(({"codfish", "cod", "boiled cod", "fish"}),
			({"codfish", "cod", "boiled cod", "fish"}),
			({"boiled"}), 125, 120, "boiled cod", "boiled cods",
			"This is a large codfish which has been stewed for some time " +
			"in its own juices.\n");
	add_food(({"shepherd's pie","pie"}), "pie",
			({"shepherd's"}),80,79,"shepherd's pie",
			"shepherd's pies","A wooden plate filled" +
			" with mashed potatoes, gravy and mixed vegetables.\n");
	add_prop(ROOM_I_INSIDE, 1);
}

public int
outfun()
{
	write("You step out of the small pub.\n");
	return 0;
}

public string
read_menu()
{
	say(QCTNAME(this_player()) + " reads the menu on the wall.\n");
	return "The menu reads: \n" +
			"  ********************************************\n" +
			"  *                                          *\n" +
			"  *      Welcome to the Seaside Tavern!      *\n" +
			"  *                                          *\n" +
			"  *          Drinks:       Water    5 cc     *\n" +
			"  *    Light Imported Sweet Wine   80 cc     *\n" +
			"  *                 Gontish grog   75 cc     *\n" +
			"  *                    Roke Beer  200 cc     *\n" +
			"  *                                          *\n" +
			"  *          For the road:                   *\n" +
			"  *                                          *\n" +
			"  *         Large bottle of grog  800 cc     *\n" +
			"  *               Bottle refills  varies     *\n" +
			"  *                                          *\n" +
			"  *          Food:                           *\n" +
			"  *               Shepherd's pie   79 cc     *\n" +
			"  *                   Boiled cod  120 cc     *\n" +
			"  *               Smoked herring   25 cc     *\n" +
			"  *                                          *\n" +
			"  ********************************************\n\n";
}

public int
buy_special(string str)
{
	object tp = this_player(), to = this_object(), bottle, key;

	if(!str)
	{
		return 0;
	}

	setuid();
	seteuid(getuid());

	switch(str)
	{
	case "big bottle":
	case "big bottle of grog":
	case "big bottle of gontish grog":
	case "big bottle of Gontish grog":
	case "bottle of grog":
	case "large bottle of grog":
	case "large bottle of Gontish grog":
	case "bottle of Gontish grog":
		if(!take_money(tp, 800))
		{
			write("You can't afford the large bottle of grog.\n");
			return 1;
		}

		bottle = clone_object("/d/Calia/gelan/objects/bottle");
		bottle->set_max(3500);
		bottle->set_adj("big");
		bottle->set_soft(bottle->query_max());
		bottle->set_filled_short(({"Gontish grog"}));
		bottle->set_short("big bottle");
		bottle->set_pshort("big bottles");
		bottle->set_alco(40 * bottle->query_max() / 100);

		if(bottle->move(tp))
		{
			bottle->move(to);
			write("You are too loaded and the bottle drops " +
					"on the floor.\n");
			return 1;
		}

		write("You pay the price and get your " +
				"big bottle of Gontish grog.\n");
		return 1;
		break;
	}

	return 0;
}

public int
refill_bottle(string str)
{
    object tp = this_player(), to = this_object(), bottle;
    string drink;
    int price;

    if(!str)
    {
    	write("Refill which container with what drink?\n");
        return 1;
    }

    setuid();
    seteuid(getuid());
    if (!parse_command(str, tp, " %o [with] %s ", bottle, drink))
    {
        write("Refill which container with what drink?\n");
        return 1;
    }
    if (drink == "")
    {
    	write("Refill which container with what drink?\n");
    	return 1;
    }
    if (bottle->query_soft() != 0)
    {
        write("The " + bottle->query_short() + " is not empty!\n");
        return 1;
    }
    switch (drink)
    {
    case "grog":
    case "Gontish grog":
    case "gontish grog":
        price = bottle->query_max() / 5;
        if (!take_money(tp, price))
        {
            write("You cannot afford the price to refill the " +
            		bottle->query_short() + ".\n");
            return 1;
        }
        bottle->set_soft(bottle->query_max());
        bottle->set_filled_short(({"Gontish grog"}));
        bottle->set_alco(40 * bottle->query_max() / 100);
        write("You pay " + price + " cc and refill your " +
        		bottle->query_short() + " with " +
        		"Gontish grog.\n");
        return 1;
    default:
        write("You cannot refill the " + bottle->query_short() + " with " +
        		drink + " at this pub.\n");
        return 1;
    }
}

public void
init()
{
	::init();
	init_pub();
	add_action(buy_special, "buy");
	add_action(refill_bottle, "refill");
}
