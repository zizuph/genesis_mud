/*
 * 
 *  Potion store
 *
 *  Ckrik June 2014
 */
#pragma strict_types

inherit "/d/Earthsea/std/room";
inherit "/sys/global/money";
inherit "/lib/shop";
inherit "/sys/global/composite";

#include <defs.h>
#include <stdproperties.h>
#include "defs.h"
#include <cmdparse.h>
#include <macros.h>
#include <money.h>
#include <composite.h>
#include <ss_types.h>
#include <filter_funs.h>
#include <files.h>
//#include "debug.h"

#define POTION_OBJ "/d/Genesis/std/potions/"
#define ALCHEMIST THWIL+"monster/alchemist"
#define MORTAR POTION_OBJ+"mortar"
#define VIAL POTION_OBJ+"vial"
#define SATCHEL "/d/Gondor/common/potions/satchel"
#define POTION_SAVE_FILE "/d/Earthsea/roke/thwil/potion_save"
#define MORTAR_PRICE 60
#define VIAL_PRICE 24
#define SATCHEL_PRICE 100

int buy_equip(string str);
int read_sign(string str);
int list_items(string str);
int show_return(string str);


object          alchemist;

/* Of format <potion name>: (<number>, <value>, <file_path>) */
//mapping potions = (["dummy": ({1, 200, "/d/ckrik/dummy"})]);
mapping potions = ([]);
string save_file;
int max_potions = 300;
int id_level = 45;

public int remove_potions(string potion, int number)
{
	mixed *entry;
	entry = potions[potion];
	if (!entry)
	{
		return 0;
	}
	if (entry[0] >= number)
	{
		entry[0] -= number;
		potions[potion] = entry;
	}
	if (entry[0] <= 0)
	{
		potions = m_delete(potions, potion);
	}
	save_map(potions, save_file);
	return 1;
}

public int add_potion(object ob, int number)
{
	string name;
	mixed *entry;

	if (!living(ob) && stringp(ob->query_potion_name()))
	{
		name = implode(explode(ob->query_potion_name(), " "), "_");
		if (!potions[name])
		{
			entry = ({number, ob->query_potion_value(), MASTER_OB(ob)});
			potions += mkmapping(({name}), ({entry}));
		}
		else
		{
			entry = potions[name];
			entry[0] = MIN(max_potions, entry[0] + number);
			potions[name] = entry;
		}
		/* Have to remove this later because shop still needs it
		 */
		save_map(potions, save_file);
		return 1;
	}
	return 0;
}

public int query_potion_quantity(string potion)
{
	mixed *entry;
	if (!strlen(potion))
	{
		return 0;
	}
	entry = potions[potion];
	if (entry)
	{
		return entry[0];
	}
	return 0;
}

public int query_potion_value(string potion)
{
	mixed *entry;
	if (!strlen(potion))
	{
		return 0;
	}
	entry = potions[potion];
	if (entry)
	{
		return entry[1];
	}
	return 0;
}

public string query_potion_file(string potion)
{
	mixed *entry;
	if (!strlen(potion))
	{
		return "";
	}
	entry = potions[potion];
	if (entry)
	{
		return entry[2];
	}
	return "";
}

public string *query_potions()
{
	return m_indexes(potions);
}

public int query_number_potions()
{
	return m_sizeof(potions);
}

public void set_save_file(string file)
{
	//  debug("setting save file to " + file + "\n");
	save_file = file;
}

public void set_max_potion_quantity(int n)
{
	max_potions = n;
}

public void set_id_level(int n)
{
	id_level = n;
}

static int check_valid_potion(mixed *entry)
{
	if (file_size(entry[2]) <= 0)
	{
		return 0;
	}
	return 1;
}

/* Purge all potions that are no longer valid */
public void purge_invalid_potions()
{
	mapping selects;
	string *indices;
	int i, s;

	selects = filter(potions, check_valid_potion);
	indices = m_indexes(selects);

	for (i = 0, s = sizeof(indices); i < s; i++)
	{
		potions = m_delete(potions, indices[i]);
	}
	save_map(potions, save_file);
}

public void init_potion_store()
{
	potions = restore_map(save_file);
	purge_invalid_potions();
}

void
reset_room()
{
	if (!objectp(alchemist))
	{
		alchemist = clone_object(ALCHEMIST);
		alchemist->move(TO);
		alchemist->command("emote enters.");
	}
}

void
create_earthsea_room()
{
	config_default_trade();
	set_money_greed_sell(95);
	set_money_greed_buy(95);
	set_save_file(POTION_SAVE_FILE);
	set_max_potion_quantity(2000);
	set_id_level(85);
	init_potion_store();
	set_short("Alchemist's shop");
	set_long("You enter the alchemist's shop and see many vials " +
			"of liquids in a menangerie of colors, all carefully " +
			"curated by the apprentices assigned to work here. " +
			"On one shelf you see boxes of empty vials. On another " +
			"shelf you see mortars for making potions. " +
			"There is a sign here hanging on the wall. \n");

	add_item("wall", "Nothing spectacular about it.\n");
	add_item("sign", "Why don't you read it?\n");
	add_exit(THWIL + "t9", "south");
	reset_room();
	INSIDE;
}

void
init()
{
	::init();
	init_shop();
	add_action(&read_sign(), "read");
	add_action(&show_return(), "show");
	add_action(&buy_equip(), "buy");
	add_action(&list_items(), "list");
}

int
read_sign(string str)
{

	notify_fail("Read what?\n");
	if (str == "sign" || str == "poster")
	{
		TP->catch_msg("The sign reads:\n" +
				"------------------------------\n" +
				" Here you can - list potions \n" +
				"              - list equipment\n" +
				"              - sell potions    \n" +
				"              - buy equipment     \n" +
				"              - buy potions     \n");
		return 1;
	}
	return 0;
}

int
shop_hook_allow_sell(object ob)
{
	if (TO->filter_potion(ob))
		return 1;

	notify_fail("The store only buys potions.\n");
	return 0;
}

int
filter_potion(object ob)
{
	return IS_POTION_OBJECT(ob);
}

int
query_sell_price(object ob)
{
	object tp = this_player();

	return MAX((tp->query_skill(SS_TRADING) +
			tp->query_skill(SS_ALCHEMY)) / 2, 50) *
			ob->query_potion_value() / 100 * ob->num_heap();
}

int
query_potion_buy_price(int value)
{
	return value;
}
/*
 * Function name: redefining sell_it from the basic shop (just for potions)
 * Description:   Try to let the player sell the item array
 * Arguments:     ob - the object array
 *                check - wheather check for worn or wielded stuff
 *                str - string describing how the money should be paid
 * Returns:       An array with the objects sold
 */

object *
sell_it(object *ob, string str, int check) 
{
	int price, total, i, j, k, *null, *value_arr, *null_arr, err;
	object *sold;
	mixed tmp;

	null_arr = allocate(sizeof(query_money_types())) + ({});
	sold = allocate(sizeof(ob));
	total = 0;
	for (i = 0; i < sizeof(ob); i++)
	{
		if (!shop_hook_allow_sell(ob[i]))
			continue;

		if (ob[i]->query_potion_value == 0)
		{
			shop_hook_sell_no_value(ob[i]);
			continue;
		}

		if (check && (ob[i]->query_worn() ||
				ob[i]->query_wielded()))
		{
			shop_hook_sell_worn_or_wielded(ob[i]);
			continue;
		}

		if (tmp = ob[i]->query_prop(OBJ_M_NO_SELL))
		{
			shop_hook_sell_no_sell(ob[i], tmp);
			continue;
		}

		/* Save price if ob destructed in move */
		price = query_sell_price(ob[i]);

		if (price <= 0)
		{
			shop_hook_sell_no_value(ob[i]);
			continue;
		}

		if (!add_potion(ob[i], ob[i]->num_heap()))
		{
			shop_hook_sell_no_sell(ob[i], 1);
		}

		if (price > 0)
		{
			if (ob[i]->query_leave_behind() == 0)
			{
				sold[j] = ob[i];
				j++;
			}
			total += price;
			if (j >= 20)
				break;
			/*
			 * Only let people sell 20 objects at once and hopefully we wont get
			 * those too long evaluation problems.
			 */
		}
	}

	sold = sold - ({ 0 });

	if (sizeof(sold) > 0)
	{
		value_arr = split_values(total);
		value_arr[2] += value_arr[3] * 12;
		value_arr[3] = 0;
		//value_arr = calc_change(total, null, str);
		change_money(null_arr + value_arr, this_player());
		shop_hook_sell_get_money(text(value_arr));
	}

	return sold;
}


int
list_items(string str)
{
	string result = "";
	object tp = this_player();
	int i;

	if (!objectp(alchemist))
	{
		write("The alchemist is not here to do business with you.\n");
		return 1;
	}
	if (str == "equipment" || str == "equip" ||
			str == "potions" || !str)
	{
		result += "                           Alchemist's Brew\n";
		result += "                                ~~~~~~\n";
		result += "---------------------------------------------------------------------------\n";
		if (!str || str == "potions")
		{
			result += do_list("potions");
		}
		if (!str || str == "potions")
		{
			result += "---------------------------------------------------------------------------\n";
			if (str == "potions")
			{
				tp->more(result, 0);
				return 1;
			}
		}

		if (str == "equipment" || str == "equip" || !str)
		{
			if (str == "equipment" || str == "equip")
			{
				result +="                    Equipment and Specialty Items\n";
				result += "---------------------------------------------------------------------------\n";
			}
			result += "\n";
			result += "     ";
			result += "                 empty vial        50 cc\n";
			result += "     ";
			result += "                 leather satchel   100 cc\n";
			result += "     ";
			result += "                 mortar            200 cc\n";
			result += "---------------------------------------------------------------------------\n";
			tp->more(result, 0);
			return 1;
		}
		return 1;
	}
	write("List what? Equipment? Herbs?\n");
	return 1;
}

/* Function name:  buy_equip()
 * for selling jars and pouches
 * Returns: 1 if successful
 */

int
buy_equip(string str)
{
	object tp = this_player();
	object stuff;
	int price;

	setuid();
	seteuid(getuid(TO));

	if (!objectp(alchemist))
		if (!present("ariel", TO))
		{
			tp->catch_msg("The alchemist is not here for business.\n");
			return 1;
		}

	switch (str)
	{
	case "mortar":
		stuff = clone_object(MORTAR);
		price = MORTAR_PRICE;
		break;
	case "vial":
	case "empty vial":
		stuff = clone_object(VIAL);
		price = VIAL_PRICE;
		break;
	case "satchel":
		stuff = clone_object(SATCHEL);
		price = SATCHEL_PRICE;
		break;
	default:
		return 0;
	}

	if (!take_money(tp, price))
	{
		alchemist->command("say " +
				" Sorry but you can't afford it right now!");
		stuff->remove_object();
	}

	tp->catch_msg("You pay the price and get "+
			LANG_ASHORT(stuff) + ".\n");
	if (stuff->move(tp))
	{
		stuff->move(TO);
		tell_room(TO, QCTNAME(alchemist) + " sets "+
				LANG_ASHORT(stuff) + " on the counter.\n", ({}));
	}
	return 1;
}


/*
 * Function name: shop_hook_list_object
 * Description:   List an object
 * Arguments:     ob - The object 
 * Slight redefinition of newinal function from 
 * the /lib/shop.c == Amelia 4/5/98
 * 
 */
string
shop_hook_list_potion(string potion, int no, int price)
{
	string str, num, mess;
	int platinum, gold, silver, copper;
	int *values;

	platinum = gold = silver = copper = 0;
	values = split_values(price);
	if (sizeof(values))
	{
		copper = values[0];
		silver = values[1];
		gold = values[2];
		platinum = values[3];
	}

	str = sprintf("| %-3d | %-30s | %#3d pc | %#3d gc | %#3d sc | %#3d cc |",
			no, potion, platinum,
			gold, silver, copper);
	/*
	if (mess = text(split_values(price)))
	    write(break_string(num + str + mess + ".\n", 70));
	else
	    write(str + "That item wouldn't cost you much.\n");
	 */
	str += "\n";
	return str;
} 


string
shop_hook_list_empty_store(string str)
{
	string result = "";
	result += "          ";
	result += "     ***** The store is currently out of potions ***** \n";
	return result;
}

int shop_hook_buy_no_match(string str)
{
	alchemist->command("say " +
			" Sorry I don't have " + str + " in stock " +
			"now.");
	return 1;
}

/*
 * Function name: do_buy
 * Description:   Try to let the player buy an item
 * Arguments:     string - describing how to pay and get change
 * Returns:       1 on sucess
 */
int
do_buy(string str)
{
	object potions;
	object tp = this_player();
	string str1, str2, str3, str4;
	int quantity, num, i, flag;
	int price;

	if (!objectp(alchemist))
	{
		notify_fail("The alchemist is not here to do business with you.\n");
		return 1;
	}

	if (!str || str =="")
	{
		notify_fail("Buy what?\n");
		return 1;
	}

	/*  Did the player specify payment and change? */
	if (sscanf(str, "%s for %s and get %s", str1, str2, str3) != 3)
	{
		/* Well, maybe player has defined how payment will be done atleast? */
		str3 = "";
		if (sscanf(str, "%s for %s", str1, str2) != 2)
		{
			str2 = "";
			str1 = str;
		}
	}
	str4 = str1;
	if (sscanf(str1, "%d %s", num, str1) != 2)
	{
		num = 1;
		str1 = str4;
	}
	str1 = implode(explode(str1, " "), "_");
	quantity = query_potion_quantity(str1);

	if (quantity <= 0)
		return shop_hook_buy_no_match(str4);
	if (quantity < num)
	{
		alchemist->command("say " +
				" Sorry but I do not have " +
				str + " right now.");
		return 1;
	}
	if (num > 20)
	{
		alchemist->command("say " +
				" Sorry but I can only handle 20 items at a time.");
		return 1;
	}
	price = query_potion_value(str1) * num;

	if (!take_money(this_player(), price))
	{
		alchemist->command("say " +
				" Sorry but you can't afford it right now!");
		return 1;
	}
	setuid();
	seteuid(getuid(TO));
	/* remove the potion */
	potions = clone_object(query_potion_file(str1));
	potions->set_heap_size(num);
	remove_potions(str1, num);
	/* clone it */
	tell_room(environment(tp), QCTNAME(tp) + " bought " + str4 + ".\n",
			tp);
	tp->catch_msg("You pay the price and get "+
			str4 + ".\n");
	flag = 0;
	potions->move(tp);
	if (flag)
	{
		tell_room(this_object(), QCTNAME(alchemist) + " sets "+
				str4 + " on the counter.\n", ({}));
	}

	return 1;
}

/*
 * Function name: do_sell
 * Description:   Try to let the player sell the_item
 *                Observe there is no message written when sold item
 *                has a value higher than the shop gives out.
 * Returns:       1 on sucess
 * Arguments:     str - string holding name of item, hopefully
 */
int
do_sell(string str)
{
	object *item, store;
	int i, value, check;
	string str1, str2;

	if (!objectp(alchemist))
	{
		notify_fail("The alchemist is not here to do business with you.\n");
		return 1;
	}
	if (!str || str =="")
	{
		notify_fail("Sell what?\n");
		return 0;
	}

	/*  Did player specify how to get the money? */
	if (sscanf(str, "%s for %s", str1, str2) != 2)
	{
		str1 = str;
		str2 = "";
	}

	if (str1 == "all!")
	{
		str1 = "all";
		check = 0; /* Sell worn or wielded objects. */
	}
	else
	{
		check = 1; /* Don't sell worn or wielded objects. */
	}

	item = FIND_STR_IN_OBJECT(str1, this_player());
	if (!sizeof(item))
	{
		return shop_hook_sell_no_match(str1);
	}

	item = sell_it(item, str2, check);
	if (sizeof(item))
	{
		shop_hook_sold_items(item);
		for (i = 0; i < sizeof(item); i++)
		{
			if (item[i]->num_heap() == 0)
			{
				item[i]->remove_object();
			}
			else
			{
				item[i]->remove_split_heap();
			}
		}
		return 1;
	}

	if (str1 == "all")
	{
		return shop_hook_sold_nothing();
	}

	return 0; /* Player tried to sell a non sellable object. */
}

/*
 * Function name:   do_list
 * Description:     Provide a list of objects in the store room
 * Returns:         0 if not recognised
 *                  1 otherwise
 * Arguments:       str - the name of the objects to search for
 */
string
do_list(string str)
{
	int i, s;
	int *prices, *num;
	string *potions;
	string result = "";

	if (query_number_potions() <= 0)
	{
		result += shop_hook_list_empty_store(str);
	}
	potions = query_potions();
	potions = sort_array(potions);
	for (i = 0, s = sizeof(potions); i < s; i++)
	{
		result += shop_hook_list_potion(implode(explode(potions[i], "_"), " "),
				query_potion_quantity(potions[i]),
				query_potion_value(potions[i]));
	}
	return result;
}


int
show_return(string str)
{
	if (!str)
		return 0;

	if (str == "potions" || str == "equipment" || str == "equip")
		return 0;


}


int
do_show(string str)
{
	object tp = this_player();
	object *item;

	if (!objectp(alchemist))
	{
		notify_fail("The alchemist is not here to examine your potion.\n");
		return 1;
	}

	item = FIND_STR_IN_OBJECT(str, this_player());

	if (sizeof(item) <= 0)
	{
		tp->catch_msg("You cannot find a " + str + " to show to " +
				QCTNAME(alchemist) + ".\n");
		return 1;
	}
	if (sizeof(item) > 1)
	{
		alchemist->command("say Please show me only one thing at a time.");
		return 1;
	}
	tell_room(tp, QCTNAME(tp) + " shows a " + item[0]->query_name() +
			" to " + QCTNAME(alchemist) + ".\n");
	if (!filter_potion(item[0]))
	{
		alchemist->command("chuckle");
		alchemist->command("say That is not an potion.");
		return 1;
	}
	if (item[0]->query_id_diff() > id_level)
	{
		alchemist->command("hmm");
		alchemist->command("say It is called a " + item[0]->query_potion_name() + ", but I am afraid I do not know anything about this potion.");
		return 1;
	}
	alchemist->command("brighten");
	set_alarm(2.0, 0.0, &alchemist->command("say Oh! That is a " +
			item[0]->query_potion_name() + ". " +
			item[0]->query_id_long()));

	return 1;
}


/*
 * Function name:   do_value
 * Description:     Let the player value an item, carry or in shop
 * Returns:         1 on success
 */
int
do_value(string str)
{
	return 0;
}


