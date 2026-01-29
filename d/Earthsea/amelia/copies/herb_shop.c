/*
 *  Herb Shop
 *
 *  Standard herb shop for Gondor
 *  Copied from Minas Morgul herb shop
 *
 *  Olorin, 15-nov-1994
 *
 *  Modification Log:
 */
#pragma save_binary
#pragma strict_types

inherit "/lib/shop.c";

#include <cmdparse.h>
#include <composite.h>
#include <files.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define HERBJAR         "/d/Gondor/common/guild/obj/herbjar"
#define HERBPOUCH       "/d/Gondor/common/guild/obj/herbpouch"
#define HERBGLOVES	"/d/Gondor/common/arm/herb_gloves"
#define HERBCORD	"/d/Gondor/common/obj/herb_cord"

object *clone_and_buy_it(string str1, string str2, string str3);
string  read_sign();

void
init_herb_shop()
{
   add_action("do_smell", "smell");
   init_shop();
}

string
read_sign()
{
   return "\t __________________________________________\n" +
          "\t/                                          \\\n" +
          "\t|             De Herbb Shoppe              |\n" +
          "\t|            ~~~~~~~~~~~~~~~~~             |\n" +
          "\t|         We sell and buy herbs.           |\n" +
          "\t|    From our large stock, we also sell    |\n" +
          "\t|    jars, pouches and cords, but we do    |\n" +
          "\t|          not buy these items!            |\n" +
          "\t|       You can list what we offer.        |\n" +
         "\t\\__________________________________________/\n";
}

int
do_read(string str)
{
    return 0;
}

/*    
 * Function name: query_buy_price
 * Description:   What price should the player pay
 * Arguments:     ob - The object to test
 * Returns: 	  The price
 */
int
query_buy_price(object ob)
{
    int seed;

    sscanf(OB_NUM(ob), "%d", seed);
    return 2 * ob->query_herb_value() * (query_money_greed_buy() +
	15 - this_player()->query_skill(SS_TRADING) / 4 +
	random(15, seed)) / 100;
}

int
query_buy_price_special(object ob)
{
    int seed;

    sscanf(OB_NUM(ob), "%d", seed);
    return 2 * ob->query_prop(OBJ_I_VALUE) * (query_money_greed_buy() +
	15 - this_player()->query_skill(SS_TRADING) / 4 +
	random(15, seed)) / 100;
}

/*    
 * Function name: query_sell_price
 * Description:   What price will the player get when selling an object?
 * Arguments:	  ob - The object
 * Returns:	  The price
 */
int
query_sell_price(object ob)
{
    int seed;

    sscanf(OB_NUM(ob), "%d", seed);
    return ob->query_herb_value() * 100 / (query_money_greed_sell() +
	15 - this_player()->query_skill(SS_TRADING) / 3 + 
	random(15, seed + 1)); /* Use another seed than on buying */
}

int
shop_hook_allow_sell(object ob)  /*If not an herb, don't take it*/
{
    if (function_exists("create_object", ob) != HERB_OBJECT)
        return 0;

    return 1;
}

/*
 * Function name: shop_hook_list_herb
 * Description:   List a herb
 * Arguments:	  no - number of herbs
 *                ob - The herb
 *                price - the price
 */
void
shop_hook_list_herb(int no, object ob, int price)
{
    string str, mess;

    str = sprintf("%4d %-17s - ", no, ob->query_herb_name());
    if (mess = text(split_values(price)))
	write(str + mess + ".\n");
    else
	write(str + "That herb wouldn't cost you much.\n");
}

int
herb_filter(object ob)
{
    return (function_exists("create_object", ob) == HERB_OBJECT);
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
    notify_fail("There are currently no herbs for sale.\n");
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
 * Function name: query_shop_hook_restricted_herb
 * Description: Test if this player may buy this particular herb.
 * Arguments: pl - this_player(), str - the herb name.
 */
int
query_shop_hook_restricted_herb(object pl, string str)
{
    return 0;
}

/*
 * Function name:   do_list
 * Description:     Provide a list of herbs in the store room
 * Arguments:       str - dummy, not used
 * Returns:         0 if not recognised
 *                  1 otherwise
 */
int
do_list(string str)
{
    int     i,
            price,
           *arr;
    mapping herbs;
    object  herb;
    string *herb_files;

    seteuid(getuid());
    call_other(store_room, "load_me");

    herbs = store_room->query_herbs();
    herb_files = sort_array(m_indexes(herbs));

    write("----- We sell the following herbs: -----------------------------------\n");
    if (!m_sizeof(herbs))
        shop_hook_list_empty_store(str);

    for (i = 0; i < sizeof(herb_files); i++)
    {
        if (file_size(herb_files[i]+".c") > 0)
        {
            call_other(herb_files[i], "load_me");
            if (objectp(herb = find_object(herb_files[i])))
            {
                price = query_buy_price(herb);
                shop_hook_list_herb(herbs[herb_files[i]],herb, price);
            }
        }
    }

    if (str != "herbs" && str != "herb")
    {
        write("\n----- We also sell: --------------------------------------------------\n");
        call_other(HERBJAR, "load_me");
        shop_hook_list_other(find_object(HERBJAR),
            HERBJAR->query_prop(OBJ_I_VALUE));
        call_other(HERBPOUCH, "load_me");
        shop_hook_list_other(find_object(HERBPOUCH),
            HERBPOUCH->query_prop(OBJ_I_VALUE));
        call_other(HERBGLOVES, "load_me");
        shop_hook_list_other(find_object(HERBGLOVES),
            HERBGLOVES->query_prop(OBJ_I_VALUE));
        call_other(HERBCORD, "load_me");
        shop_hook_list_other(find_object(HERBCORD),
            HERBCORD->query_prop(OBJ_I_VALUE));
    }
    write("----------------------------------------------------------------------\n");

    return 1;
}

static int
filter_herb_name(string herb_file, string name)
{
    if (file_size(herb_file + ".c") > 0)
	return (herb_file->query_herb_name() == name);
    return 0;
}

int
query_shop_no_business(mixed pl)
{
    return 0;
}

void
shop_hook_no_business(object pl)
{
    NF("");
    tell_room(TO, "The herbalist says: I do not want your business, " +
        (pl->query_gender() ? "Lady" : "Mister") + "!\n");
    write("The herbalist spits at you.\n");
    say("The herbalist spits at " + QTNAME(pl) + ".\n");
    tell_room(TO, "The herbalist says: Leave before I call the guards!\n");
}

int
shop_hook_restricted_herb(object pl, string str)
{
    notify_fail("That particular herb is restricted from sale.\n");
}

/*
 * Function name: do_buy
 * Description:   Try to let the player buy a herb
 * Arguments:     string - describing how to pay and get change
 * Returns:       1 on sucess
 */
int
do_buy(string str)
{
    int     i, j,
            number = 0,
            max_num;
    object *item = ({}),
           *bought_item,
            store;
    string  str1,
            str2,
            str3,
           *herb_files;
    mapping herbs;

    if (query_shop_no_business(this_player()))
    {
        shop_hook_no_business(this_player());
        return 0;
    }

    if (!str || str =="")
    {
	notify_fail("Buy what?\n");
	return 0;
    }
 
    call_other(store_room, "load_me"); /* Make sure storeroom is loaded */

    /*  Did the player specify payment and change? */
    if ((sscanf(str,"%d %s for %s and get %s", number, str1, str2, str3) != 4) &&
        (sscanf(str, "%s for %s and get %s", str1, str2, str3) != 3))
    {
    /* Well, maybe player has defined how payment will be done atleast? */
        str3 = "";
        if ((sscanf(str,"%d %s for %s", number, str1, str2) != 3) &&
            (sscanf(str, "%s for %s", str1, str2) != 2))
        {
            str2 = "";
            if (sscanf(str, "%d %s", number, str1) != 2)
                str1 = str;
        }
    }

    if (number <= 0)
        number = 1;
    if (number > 20)
        number = 20;

    /* besides herbs, we also sell herb jars and herb bags, but they *
     * are not kept in the storage, but cloned on demand             */
    if (str1 == "glass jar" || str1 == "jar" ||
        str1 == "leather pouch" || str1 == "pouch" ||
        str1 == "gloves" || str1 == "pair of gloves" ||
	str1 == "cord" || str1 == "leather cord" || str1 == "herbcord")
    {
        item = clone_and_buy_it(str1, str2, str3);
        if (sizeof(item))
            return shop_hook_bought_items(item);
        return 0;
    }

    store = find_object(store_room);
    herbs = store->query_herbs();
    herb_files = filter(m_indexes(herbs), &filter_herb_name(,str1));

    if (sizeof(herb_files) > 0)
    {
	//    for (i = 0; i < sizeof(herb_files); i++)
	//    {
        max_num = 1;
        if (number > 1)
        {
            max_num = store->query_herb_number(herb_files[0]);
            if (number > max_num)
                number = max_num;
        }
        for (j = 0; j < number; j++)
            item += ({ clone_object(herb_files[0]) });
    }

    if (!sizeof(item))
	return shop_hook_buy_no_match(str1);

    if (query_shop_hook_restricted_herb(this_player(), str1))
        return shop_hook_restricted_herb(this_player(), str1);
    bought_item = buy_it(item, str2, str3);
    item -= bought_item;
    // remove herbs that were not bought
    if (sizeof(item))
        item->remove_object();

    if (sizeof(bought_item))
    {
        store->reduce_herb_number(bought_item);
	return shop_hook_bought_items(bought_item);
    }

    return 0; /* Player tried to buy a non buyable object. */
}

/*
 * Function name: shop_hook_value_held
 * Description:   Player values an object he's holding
 * Arguments:     ob   - The object
 *                text - The price in text form
 */
void
shop_hook_value_held(object ob, string text)
{
    string  desc = ob->query_id_long();

    write("You ask the shop keeper about the "
      + ob->query_short() + ".\n"
      + "You would get " + text + " for the "
      + ob->query_herb_name() + ".\n");
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
    int *arr, price, i, j, num;

    if (query_shop_no_business(this_player()))
    {
        shop_hook_no_business(this_player());
        return 0;
    }

    if (!str || str =="")
    {
        notify_fail("Value what?");
        return 0;
    }

    num = sizeof(query_money_types());
    item = FIND_STR_IN_OBJECT(str, this_player());
    if (!sizeof(item))
        return shop_hook_value_no_match(str);

    for (i = 0; i < sizeof(item); i++)
    {
        if (!shop_hook_allow_sell(item[i]) ||
                item[i]->query_prop(OBJ_M_NO_SELL)) 
        {
            shop_hook_value_not_interesting(item[i]);
            continue;
        }

        if (!(price = query_sell_price(item[i])))
        {
            shop_hook_value_not_interesting(item[i]);
            continue;
        }
        arr = calc_change(price, 0, "");
        shop_hook_value_held(item[i], text(arr));
        j++;
    }

    shop_hook_value_asking(str);
    if (j > 0)
        return 1;
    return 0;
}

int
do_sell(string args)
{
    if (query_shop_no_business(this_player()))
    {
        shop_hook_no_business(this_player());
        return 0;
    }
    return ::do_sell(args);
}

/*
 * Function name: clone_and_buy_it
 * Description:   Try to clone and let the player buy the item
 * Arguments:     str1 - the name of the object
 *                str2 - string describing how the money should be paid
 *                str3 - what coin types to get chainge back in
 * Returns:       the bought object
 */
object *
clone_and_buy_it(string str1, string str2, string str3) 
{
    int     price,
            i, j, k,
            num = sizeof(query_money_types()),
           *value_arr = allocate(2 * num),
           *arr,
            error,
            err;
    object  ob;
    mixed   tmp;

    seteuid(getuid());
    if (HERBJAR->id(str1))
        ob = clone_object(HERBJAR);
    else if (HERBPOUCH->id(str1))
        ob = clone_object(HERBPOUCH);
    else if (HERBGLOVES->id(str1))
        ob = clone_object(HERBGLOVES);
    else if (HERBCORD->id(str1))
        ob = clone_object(HERBCORD);
    else
        return 0;

    price = query_buy_price_special(ob);

    if (err = ob->move(this_player()))
    {
        shop_hook_buy_cant_carry(ob, err);
        ob->remove_object();
        return 0;
    }

    if (sizeof(arr = pay(price, this_player(), str2, 0, 0, str3)) == 1)
    {
        shop_hook_buy_cant_pay(ob, arr);
        ob->remove_object();
        return 0;
    }

    /* Detect if there was a move error. */
    if (error = arr[sizeof(arr) - 1])
    {
        if (error < -1)
        {
        /* Couldn't take the money from player, the coins were stuck */
            shop_hook_buy_magic_money(ob);
            ob->remove_object();
        }
    /* We don't want the money so no move error to us, if there was one
       it was because the player couldn't hold all coins, and if so the
       drop text is already written, but the deal is still on :) */
    }

    for (k = 0; k < 2 * num; k++)
        value_arr[k] += arr[k];

    if (objectp(ob))
	shop_hook_buy_pay_money(
		text(arr[0 .. num - 1]), text(arr[num .. 2 * num - 1]));

    return ({ ob });
}

/*
 * Function name: sell_it
 * Description:   Try to let the player sell the item array
 * Arguments:     ob - the object array
 *                check - wheather check for worn or wielded stuff
 *                str - string describing how the money should be paid
 * Returns:	  An array with the objects sold
 */
object *
sell_it(object *ob, string str, int check) 
{
    int price, i, j, k, *tmp_arr, *null, *value_arr, *null_arr, err;
    object *sold;
    mixed tmp;

    call_other(store_room, "load_me"); /* Make sure store room is loaded */

    value_arr = allocate(sizeof(query_money_types()));
    null_arr = value_arr + ({});
    sold = allocate(sizeof(ob));

    for (i = 0; i < sizeof(ob); i++)
    {
	if (!shop_hook_allow_sell(ob[i]))
	    continue;

        if (ob[i]->query_herb_value() == 0)
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

void
smell_herbs()
{
    write(BSN("You cannot smell the herbs themselves since " +
        "they are hanging far out of your reach under the " +
        "ceiling, but their smell pervades the whole room."));
    return;
}

void
smell_air()
{
    write(BSN("The air is filled by the smell of the herbs " +
        "hanging under the ceiling. But they cannot completely " +
        "cover the sickly sweet smell of decay that drifts " +
        "through all the rooms here."));
    return;
}

int
do_smell(string str)
{
    NF("Smell what?\n");

    if (str == "herb" || str == "herbs")
    {
        smell_herbs();
        return 1;
    }
    if (str == "air")
    {
        smell_air();
        return 1;
    }
    return 0;
}

int
shop_hook_bought_items(object *arr)
{
    write(break_string("You bought " + COMPOSITE_DEAD(arr) + ".\n", 75));
    say(QCTNAME(this_player()) + " bought " + QCOMPDEAD + ".\n");
    arr->force_dry();
    return 1;
}

/*
 * Function name: buy_it
 * Description:   Try to let the player buy the item array
 *                The function in /lib/shop permits buying of only one item at a time.
 * Arguments:     ob - the object array
 *                str2 - string describing how the money should be paid
 *                str3 - what coin types to get chainge back in
 * Returns:       1 on sucess
 */
object *
buy_it(object *ob, string str2, string str3) 
{
    int price, i, j, k, *value_arr, *arr, error, num, err;
    object *bought;
    mixed tmp;

    num = sizeof(query_money_types());
    value_arr = allocate(2 * num);
    bought = allocate(sizeof(ob));

    for (i = 0; i < sizeof(ob); i++)
    {
        if (!shop_hook_allow_buy(ob[i]))
            continue;

        if (tmp = ob[i]->query_prop(OBJ_M_NO_BUY))
        {
            shop_hook_buy_no_buy(ob[i], tmp);
            continue;
        }

        price = query_buy_price(ob[i]);

        /* If you don't feel greedy you can shorten the calculation above. */

        if (err = ob[i]->move(this_player()))
        {
            shop_hook_buy_cant_carry(ob[i], err);
            break;
        }

        if (sizeof(arr = pay(price, this_player(), str2, 0, 0, str3)) == 1)
        {
            shop_hook_buy_cant_pay(ob[i], arr);
            break;  /* pay() can handle notify_fail() call */
        }

        /* Detect if there was a move error. */
        if (error = arr[sizeof(arr) - 1])
        {
            if (error < -1)
            {
            /* Couldn't take the money from player, the coins were stuck */
                shop_hook_buy_magic_money(ob[i]);
                continue;
            }
            /* We don't want the money so no move error to us, if there was one
               it was because the player couldn't hold all coins, and if so the
               drop text is already written, but the deal is still on :) */
        }

        for (k = 0; k < 2 * num; k++)
            value_arr[k] += arr[k];

        bought[j] = ob[i];
        j++;
    }

    bought = bought - ({ 0 });

    if (sizeof(bought) > 0)
        shop_hook_buy_pay_money(
                text(value_arr[0 .. num - 1]), text(value_arr[num .. 2 * num - 1]));

    return bought;
}

