/*
 * Component Shop
 *
 * by Rastlin 
 */


/* SEARCH FOR 'FIX' */
/* Strange prices when selling, listing and buying.. Might be right */
/* Can't value potions and herbs */

#pragma save_binary
#pragma strict_types

#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include "../guild/local.h"
#include "component_list.h"
#include <macros.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include <composite.h>
#include <ss_types.h>


inherit "/lib/shop.c";
inherit TOWERROOM;

#define MAXLIST         30
#define HERB_FILE       "/std/herb"
#define POTION_FILE     "/std/potion"
#define LEFTOVER_FILE   "/std/leftover"

int gGlobal_seed;

void
create_tower_room()
{
    set_short("Component shop");
    set_long("This is the component shop located in the Tower " +
        "of High Sorcery. Here, Magi can purchase items necessary " +
        "for spell-casting, spell components. Herbs, potions, and " +
        "other useful items are often in stock.\n");

    AI(({"wall","walls"}), "The walls of this component shop " +
        "are kept clean. It seems that all the components are " +
        "kept behind the counter.\n");
    AI("counter","The counter is a marble white, made of a " +
        "finely polished substance.\n");
    AI("ceiling","The ceiling is plain, with no distinguishing " +
        "features.\n");
    AI("floor","The floor is of little interest. The only thing " +
        "noteworthy is its cleanliness.\n");

    add_exit(WTOWER + "lobby", "north", 0);

    /* this line needed to created default trade configuration */
    config_default_trade();

    set_money_greed_buy(60);
    set_money_greed_sell(150);
    set_money_give_out(   ({ 10000,   700,  50,   10 }));
    set_money_give_reduce(({     0,     2,   4,    6 }));

    /* set the room to be used as storage room for this shop */
    set_store_room(WTOWER + "component_storage");
    store_room->load_me();
    gGlobal_seed = SECURITY->query_start_time() % 30;
}

/*
 * Function name: query_item_value
 * Description:   Get the value of the item
 * Arguments:     item - The item to value
 * Returns:       The value
 */
static int
query_item_value(object item)
{
    switch (function_exists("create_leftover", item))
      {
      case LEFTOVER_FILE:
	if(item->query_prop(OBJ_M_NO_SELL) == "Food is not to be resold.\n")
		item->remove_prop(OBJ_M_NO_SELL);
	return (item->query_prop(OBJ_I_VALUE) + 5);
	break;
      default:
	break;

      }

    switch (function_exists("create_object", item))
    {
        case HERB_FILE:
	    return item->query_herb_value();
	    break;
        case POTION_FILE:
            return item->query_potion_value();
            break;
        default:
	    return item->query_prop(OBJ_I_VALUE);
	    break;
    }
}

/*
 * Function name: query_buy_price
 * Description:   What price should the player pay
 * Arguments:     ob - The object to test
 * Returns:       The price
 */
public int
query_buy_price(object ob)
{
    int seed, value;

    sscanf(OB_NUM(ob), "%d", seed);

    if (!seed)
        seed = file_size(file_name(ob)) + gGlobal_seed;

    return 2 * query_item_value(ob) * (query_money_greed_buy() +
        15 - this_player()->query_skill(SS_TRADING) / 4 +
        random(15, seed)) / 100;
}

/*    
 * Function name: query_sell_price
 * Description:   What price will the player get when selling an object?
 * Arguments:	  ob - The object
 * Returns:	  The price
 */
public int
query_sell_price(object ob)
{
    int seed;

    sscanf(OB_NUM(ob), "%d", seed);

    if (!seed)
        seed = file_size(file_name(ob)) + gGlobal_seed;

    return query_item_value(ob) * 100 / (query_money_greed_sell() +
	15 - this_player()->query_skill(SS_TRADING) / 3 + 
	random(15, seed + 1)); /* Use another seed than on buying */
}

int
shop_hook_allow_sell(object ob)  /*If not an herb, don't take it*/
{
    string func = function_exists("create_object", ob);
    string func2 = function_exists("create_leftover", ob);

    if ((func != HERB_FILE) && (func != POTION_FILE) &&
	 (func2 != LEFTOVER_FILE) && (!sizeof(ob->query_names()
	 & COMPONENT_LIST)))
        return NF("That is an unknown spell-component to me.\n");

    return 1;
}

/*
 * Function name: shop_hook_list_file
 * Description:   List a file item
 * Arguments:	  arr - Array describing the item
 */
static void
shop_hook_list_file(int count, string name, int value)
{
    string str, mess;

    str = sprintf("%5d %-20s - ", count, (count > 1 ? LANG_PWORD(C(name)) :
					  C(name)));
    if (mess = text(split_values(value)))
	write(str + mess + ".\n");
    else
	write(str + "It wouldn't cost you much.\n");
}

public int
filter_files(string file, string str)
{
    object item;

    if (file_size(file + ".c") > 0)
        if (objectp((item = find_object(file))))
	    switch (function_exists("create_object", item))
	    {
	        case HERB_FILE:
	            return (item->query_herb_name() == str);
                    break;

		case POTION_FILE:
		    return (item->query_potion_name() == str);
		    break;

	        case LEFTOVER_FILE:
		    return (item->query_organ() == str);
		    break;
	    }
    return 0;
}

/*
 * Function name: shop_hook_list_empty_store
 * Description:   If the storeroom is empty when the player wants a list
 *		  of its items
 * Arguments:	  str - If player specified string
 */
void
shop_hook_list_empty_store(string str)
{
    notify_fail("There are currently no components for sale.\n");
}

/*
 * Function name: shop_hook_list_other
 * Description:   List an object other than a herb
 * Arguments:	  ob - The object
 */
void
shop_hook_list_other(object ob, int price)
{
    string str, mess;

    str = sprintf("  %-20s - ", capitalize(ob->short()));
    if (mess = text(split_values(price)))
	write(str + mess + ".\n");
    else
	write(str + "That item wouldn't cost you much.\n");
}

/*
 * Function name:   do_list
 * Description:     Provide a list of all items in the store room
 * Arguments:       str - The name of the item to search for.
 * Returns:         0 if not recognised
 *                  1 otherwise
 */
public int
do_list(string str)
{
    mixed items;
    string *item_files, *fresh_out = ({});
    int size, price, tmp;
    object item;
    
    setuid();
    seteuid(getuid());

    store_room->load_me();

    /* The items comes in an array with two elements, 
     * the first element contains two mappings, which
     * holds herbs in the first mapping and potions in
     * the second, the second element is an array of objects.
     */
    items = store_room->query_items();

    if (!m_sizeof(items[0][0]) && !m_sizeof(items[0][1]) && !sizeof(items[1]))
    {
        shop_hook_list_empty_store(str);
	return 0;
    }

    if (!str || !strlen(str) || (L(str) == "herb") || (L(str) == "herbs"))
    {
        if (!m_sizeof(items[0][0]))
            fresh_out += ({ "herbs" });
	else
	{
	    /* List the herbs */
	    write("---- I'm selling the following herbs: ----\n");

	    item_files = sort_array(m_indexes(items[0][0]));
	    size = sizeof(item_files);

	    while(size--)
                if (file_size(item_files[size] + ".c") > 0)
                    if (objectp((item = find_object(item_files[size]))) ||
			 (!item_files[size]->aaa() && (objectp((item = 
			  find_object(item_files[size]))))))
		    {   
		        price = query_buy_price(item);
			shop_hook_list_file(items[0][0][item_files[size]],
					    item->query_herb_name(),
					    price);
		    }
        }
    }

    if (!str || !strlen(str) || (L(str) == "potion") || (L(str) == "potions"))
    {
        if (!m_sizeof(items[0][1]))
            fresh_out += ({ "potions" });
	else
	{
	    /* List the potions */
	    write("\n---- I'm selling the following potions: ----\n");
	    
	    item_files = sort_array(m_indexes(items[0][1]));
	    size = sizeof(item_files);

            while(size--)
                if (file_size(item_files[size] + ".c") > 0)
		  {
		  item_files[size]->foo_bar_me();
                    if (objectp((item = find_object(item_files[size]))))
                    {
                        price = query_buy_price(item);
                        shop_hook_list_file(items[0][1][item_files[size]],
                                            item->query_potion_name(),
                                            price);
		    }
		  }
	}
    }

    if ((L(str) != "potion") && (L(str) != "potions") && (L(str) != "herb") &&
	(L(str) != "herbs"))
    {
        if (str)
            items = FIND_STR_IN_ARR(str, items[1]);
        else
            items = items[1];

	if (sizeof(items) < 1)
        {
            if (str)
                return shop_hook_list_no_match(str);
	    else
	        fresh_out += ({ "other components" });
        }

	if (sizeof(items))
	{
	    write("\n---- I'm selling the following other components: ----\n");
	    size = tmp = MIN(MAXLIST, sizeof(items));
	    while (size--)
	    {
	        price = query_buy_price(items[size]);
		shop_hook_list_object(items[size], price);
	    }

	    if (tmp < sizeof(items))
	    {
		write("Truncated...\n");
	    }
	}
    }
    size = sizeof(fresh_out);
    if (size > 1)
    {
        write("\nI'm fresh out of " + implode(fresh_out[0..size - 2], ", ") +
	      " and " + fresh_out[size - 1] + ".\n");
    }
    else
        if (size == 1)
	   write("\nI'm fresh out of " + fresh_out[0] + ".\n");

    return 1;
}

/*
 * Function name: do_buy
 * Description:   Try to let the player buy a component
 * Arguments:     str - Describing how to pay and get change
 * Returns:       1 on sucess
 */
int
do_buy(string str)
{
    int size;
    object *objs, *obj_files = ({}),
           *bought_items,
            store;
    string str1, str2, str3;
    mixed items;
    string *item_files;

    if (!str || !strlen(str))
    {
	NF("Buy what?\n");
	return 0;
    }
 
    store_room->load_me();

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

    store = find_object(store_room);
    items = store->query_items();

    item_files = filter(m_indexes(items[0][0]) + m_indexes(items[0][1]),
			&filter_files(, L(str1)));

    size = sizeof(item_files);
    while (size--)
        obj_files += ({ clone_object(item_files[size]) });

    objs = FIND_STR_IN_ARR(str1, items[1]) + obj_files;

    if (!sizeof(objs))
	return shop_hook_buy_no_match(str1);

    bought_items = buy_it(objs, str2, str3);

    if (sizeof(objs) != sizeof(bought_items))
        (obj_files - (bought_items & obj_files))->remove_object();

    if (sizeof(bought_items))
    {
        store->remove_components((bought_items & obj_files));
	return shop_hook_bought_items(bought_items);
    }

    return 0; /* Player tried to buy a non buyable object. */
}

/*
 * Function name:   do_value
 * Description:     Let the player value an item, carry or in shop
 * Returns:         1 on success
 */
int
do_value(string str)
{
    object *item, store;
    int *arr, price, i, j, num, no_inv;

    if (!str || str =="")
        return NF("Value what?");

    num = sizeof(query_money_types());
    item = FIND_STR_IN_OBJECT(str, this_player());
    if (!sizeof(item))
	no_inv = 1;

    for (i = 0; i < sizeof(item); i++)
    {
	if (!shop_hook_allow_sell(item[i])) 
	{
	    shop_hook_value_not_interesting(item[i]);
	    continue;
	}

	price = query_sell_price(item[i]);
        arr = give(price, this_player(), "", 1);
	shop_hook_value_held(item[i], text(arr[num .. 2 * num - 1]));
	j++;
    }

    call_other(store_room, "load_me");
    store = find_object(store_room);
    item = FIND_STR_IN_OBJECT(str, store);
    if (!sizeof(item) && no_inv)
	return shop_hook_value_no_match(str);

    for (i = 0; i < sizeof(item); i++)
    {
	price = query_buy_price(item[i]);
	arr = split_values(price); /* A price with few coins possible */
	shop_hook_value_store(item[i], text(arr));
	j++;
    }	

    shop_hook_value_asking(str);
    if (j > 0)
	return 1;

    return 0;
}

/*
 * Function name: sell_it
 * Description:   Try to let the player sell the item array
 * Arguments:     ob - the object array
 *                check - wheather check for worn or wielded stuff
 *                str - string describing how the money should be paid
 * Returns:       An array with the objects sold
 */
public object *
sell_it(object *ob, string str, int check)
{
    int price, i, j, k, *tmp_arr, *null, *value_arr, *null_arr, err;
    object *sold;
    mixed tmp;

    store_room->load_me(); /* Make sure store room is loaded */

    value_arr = allocate(sizeof(query_money_types()));
    null_arr = value_arr + ({});
    sold = allocate(sizeof(ob));

    for (i = 0; i < sizeof(ob); i++)
    {
        if (!shop_hook_allow_sell(ob[i]))
            continue;

        if (query_item_value(ob[i]) == 0)
	{
	    //if (function_exists("create_leftover", ob[i]))
		//continue;
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

        if (err = ob[i]->move(store_room))
	{
            shop_hook_sell_object_stuck(ob[i], err);
            continue;
	}

        if (price > 0)
	{
            tmp_arr = calc_change(price, null, str);
            for (k = 0; k < sizeof(value_arr); k++)
                value_arr[k] += tmp_arr[k];

            sold[j] = ob[i];
            j++;
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
        change_money(null_arr + value_arr, this_player());
        shop_hook_sell_get_money(text(value_arr));
    }

    return sold;
}

public int
shop_hook_bought_items(object *arr)
{
    write(break_string("You bought " + COMPOSITE_DEAD(arr) + ".\n", 75));
    say(QCTNAME(this_player()) + " bought " + QCOMPDEAD + ".\n");
    arr->force_dry();
    return 1;
}

public void
init()
{
   init_shop();
   ::init();
}





