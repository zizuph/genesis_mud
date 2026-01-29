/*
 * /d/Gondor/common/lib/potion_shop.c
 *
 *  Potion Shop
 *
 *  Originally coded by Falke@Angalon as herb shop
 *  Modified for Minas Morgul in Gondor@Genesis by Olorin, July 1994
 *  Split into /d/Gondor/common/lib/potion_shop and room file,
 *  Olorin, 15-nov-1994
 *
 *  Modification Log:
 *	24-Feb-98, Gnadnar:	check strength_adj() before query_strength()
 *	    to detect strong or powerful potions.  some strong or powerful 
 *	    potions will have str < POTION_MIN_STRENGTH (e.g., avarywalme).
 *
 *  28-Apr-08, Toby: Changed the listing of potions.  
 */
#pragma save_binary
#pragma strict_types

inherit "/lib/shop.c";

#include <cmdparse.h>
#include <composite.h>
#include <files.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

// use gondor mortar so we get 'engrave' command
#define MORTAR          (POTION_DIR + "mortar")
#define SATCHEL		(POTION_DIR + "satchel")

#define POTION_NUM	0
#define POTION_SOFT	1
#define POTION_ALCO	2

#define POTION_MIN_STRENGTH	 80

#define NUM                   sizeof(MONEY_TYPES)
#define COIN_TYPES            ({ "cc", "sc", "gc", "pc" })


static string  mortar_file = MORTAR,
               satchel_file = SATCHEL,
               vial_file = POTION_VIAL_OBJECT;

object *clone_and_buy_it(string str1, string str2, string str3);

void    set_mortar_file(string str) { mortar_file = str; }
string  query_mortar_file() { return mortar_file; }

void    set_satchel_file(string str) { satchel_file = str; }
string  query_satchel_file() { return satchel_file; }

void    set_vial_file(string str) { vial_file = str; }
string  query_vial_file() { return vial_file; }

public  int     do_smell(string str);
public  int     do_value(string args);

void
init_potion_shop()
{
   add_action(do_smell, "smell");
   add_action(do_value, "value");
   init_shop();
}

public string
read_sign()
{
   return "\t ___________________________________________\n" +
          "\t/                                           \\\n" +
          "\t|         The Alchemist's Provider          |\n" +
          "\t|        ~~~~~~~~~~~~~~~~~~~~~~~~~~         |\n" +
          "\t|         We sell and buy potions.          |\n" +
          "\t|     From our large stock, we also sell    |\n" +
          "\t|       vials, satchels, and mortars,       |\n" +
          "\t|           but we do not buy them!         |\n" +
          "\t|         We sell and buy potions.          |\n" +
          "\t|        You can list what we offer.        |\n" +
          "\t|         You buy at your own risk,         |\n" +
          "\t|       complaints will be laughed at!      |\n" +
         "\t\\___________________________________________/\n";
}

public int
do_read(string str)
{
    return 0;
}

/*
 * Function name: money_text
 * Description:   convert a price in cc into a formatted
 *                string, giving the price using the smallest
 *                number of coins
 * Arguments:     am - the price in cc
 * Returns:       the string, eg: 1 pc  2 gc 10 sc  9 cc
 */
public string
money_text(int am)
{
    int    *arr = MONEY_SPLIT(am),
            ind = NUM;
    string  txt = "";

    while (--ind >= 0)
    {
        if (arr[ind])
            txt += sprintf("%3d %2s ", arr[ind], COIN_TYPES[ind]);
        else
            txt += "       ";
    }

    return txt;
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
    return 2 * query_object_value(ob) * (query_money_greed_buy() +
	15 - this_player()->query_skill(SS_TRADING) / 4 +
	random(15, seed)) / 100;
}

int
query_buy_price_special(object ob)
{
    int seed;

    sscanf(OB_NUM(ob), "%d", seed);
    return 2 * query_object_value(ob) * (query_money_greed_buy() +
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
    return query_object_value(ob) * 100 / (query_money_greed_sell() +
	15 - this_player()->query_skill(SS_TRADING) / 3 + 
	random(15, seed + 1)); /* Use another seed than on buying */
}

static void
shop_hook_potion_too_weak()
{
    NFN("The alchemist refuses to buy your potions as he " +
	"recognizes its inferior quality.");
}

static int
shop_hook_allow_sell(object ob)
{
    string	adj;

    /*If not an potion, don't take it*/
    if (!IS_POTION_OBJECT(ob))
        return 0;

    if (ob->query_identified())
    {
	adj = ob->strength_adj();
    }
    else
    {
	/* we must temporarily identify the potion in order
	 * for the adjective to be something other than "unknown"
	 */
	ob->set_identified(1);
	adj = ob->strength_adj();
	ob->set_identified(0);
    }
    if (adj == "strong" || adj == "powerful")
    {
	return 1;
    }
    if (strlen(function_exists("query_strength", ob)) && 
	(ob->query_strength() < POTION_MIN_STRENGTH))
    {
	shop_hook_potion_too_weak();
	return 0;
    }
    return 1;
}

/*
 * Function name: shop_hook_list_potion
 * Description:   List a potion
 * Arguments:	  no - number of potions
 *                ob - The potion
 *                price - the price
 */
void
shop_hook_list_potion(int no, object ob, int price)
{
    string str, mess;

    if (!strlen(mess = money_text(price)))
        mess = "That potion wouldn't cost you much.";

    write(sprintf("\t%5d %-'.'25s %26s" ,
        no, capitalize(ob->query_potion_name()) + " ", mess) + "\n");

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
    notify_fail("There are currently no potions for sale.\n");
}

/*
 * Function name: shop_hook_list_other
 * Description:   List an object other than a potion
 * Arguments:	  ob - The object
 */
void
shop_hook_list_other(object ob, int price)
{
    string str, mess;

    str = sprintf("        %-25s -  ", capitalize(ob->short()));

    if (mess = text(split_values(price)))
        write(str + mess + "\n");
    else
        write(str + "That item wouldn't cost you much.\n");
}

void
shop_hook_potion_list(string msg)
{
    write(msg);
}

int
sort_pline(string x, string y)
{
    return ((x[5..24] > y[5..24]) ? 1 : -1); 
}

/*
 * Function name:   do_list
 * Description:     Provide a list of potions in the store room
 * Arguments:       str - dummy, not used
 * Returns:         0 if not recognised
 *                  1 otherwise
 */
int
do_list(string str)
{
    int     i, n, 
            price;
    mapping potions;
    object  pot;
    string *potion_files;

    seteuid(getuid());
    call_other(store_room, "load_me");

    potions = store_room->query_potions();

    if (!m_sizeof(potions))
        shop_hook_list_empty_store(str);

    potion_files = sort_array(m_indexes(potions));


    if(strlen(str) == 0)
    {
        write("List what? List [potions/wares/other wares]\n");
    }
    else if(str == "potions")
    {
        write("   ================\\\\ We sell the following potions: //=================\n\n");

        for (i = 0, n = sizeof(potion_files); i < n; i++)
        {
            if (file_size(potion_files[i]+".c") > 0)
            {
                call_other(potion_files[i], "load_me");
                if (objectp(pot = find_object(potion_files[i])))
                {
                    price = query_buy_price(pot);
                    shop_hook_list_potion(potions[potion_files[i]][POTION_NUM],
    		    pot, price);
                }
            }
        }
        write("\n   " + EXPAND_LINE("=", 69) + "\n");
    }
    else if (str == "wares" || str == "other wares")
    {
        write("   ================\\\\ We offer the following wares too: //=================\n\n");
        call_other(mortar_file, "load_me");
        shop_hook_list_other(find_object(mortar_file),
        mortar_file->query_prop(OBJ_I_VALUE));
        call_other(satchel_file, "load_me");
        shop_hook_list_other(find_object(satchel_file),
        satchel_file->query_prop(OBJ_I_VALUE));
        call_other(vial_file, "load_me");
        shop_hook_list_other(find_object(vial_file),
            vial_file->query_prop(OBJ_I_VALUE));

        write("\n   " + EXPAND_LINE("=", 69) + "\n");
    }
    else
    {
        write("List what? List [potions/wares/other wares]\n");
    }
    return 1;
}

int
potion_filter(object ob)
{
    return IS_POTION_OBJECT(ob);
}

int
filter_potion_file(mixed x)
{
    return (stringp(x));
}

int
filter_potion_name(string potion, string name)
{
    int found;
    if (catch(found = (potion->query_potion_name() == name)))
    {
        write_file("/d/" + getuid() + "/log/runtime",
	    "File: " + file_name(this_object()) + "\n" +
	    "Potion error: " + potion + "\n" +
	    "Remedy: Potion removed from store in filter_potion_name().\n\n");
	/* Remove the potion from the store. */
        find_object(store_room)->remove_potion_file(potion);
    }
    return found;
}

int
query_shop_no_business(object pl)
{
    return 0;
}

void
shop_hook_no_business(object pl)
{
    NF("");
    tell_room(TO, "The alchemist says: I do not want your business, " +
        (pl->query_gender() ? "Lady" : "Mister") + "!\n");
    write("The alchemist spits at you.\n");
    say("The alchemist spits at " + QTNAME(pl) + ".\n");
    tell_room(TO, "The alchemist says: Leave before I call the guards!\n");
}

/*
 * Function name: do_buy
 * Description:   Try to let the player buy a potion
 * Arguments:     string - describing how to pay and get change
 * Returns:       1 on sucess
 */
int
do_buy(string str)
{
    int     i, num,
            alco,
            soft;
    object *item = ({}),
           *bought_item,
            store;
    string  str1,
            str2,
            str3,
           *potion_files;
    mapping potions;

    if (query_shop_no_business(this_player()))
    {
        shop_hook_no_business(this_player());
        return 0;
    }

    if (!strlen(str))
    {
	notify_fail("Buy what?\n");
	return 0;
    }
 
    str = LOW(str);

    call_other(store_room, "load_me"); /* Make sure storeroom is loaded */

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

    /* besides potions, we also sell vials, satchels, and mortars, but they *
     * are not kept in the storage, but cloned on demand             */
    if (str1 == "empty vial" || str1 == "vial" ||
        str1 == "mortar" || str1 == "satchel")
    {
        item = clone_and_buy_it(str1, str2, str3);
        if (sizeof(item))
            return shop_hook_bought_items(item);
        return 0;
    }

    store = find_object(store_room);
    potions = store->query_potions();
    if (!m_sizeof(potions))
        return shop_hook_buy_no_match(str1);

    potion_files = filter(m_indexes(potions), filter_potion_file);
    potion_files = filter(potion_files, &filter_potion_name(,str1));

    if (!sizeof(potion_files))
	return shop_hook_buy_no_match(str1);

    // You can only buy one potion at a time!
    item = ({ clone_object(potion_files[0]) });
    num  = potions[potion_files[0]][POTION_NUM];
    soft = potions[potion_files[0]][POTION_SOFT] / num;
    alco = potions[potion_files[0]][POTION_ALCO] / num;

    item[0]->set_up_effect(soft, alco);

    item = buy_it(item, str2, str3);
    if (sizeof(item))
    {
        store->reduce_sold_potion(potion_files[0], soft, alco);
	return shop_hook_bought_items(item);
    }

    return 0; /* Player tried to sell a non sellable object. */
}

public int
do_value(string args)
{
    object *item;
    int i, price, num, *arr;
    num = sizeof(query_money_types());
    if (!strlen(args))
    {
        NFN0("Value what?");
    }
    if (query_shop_no_business(TP))
    {
        shop_hook_no_business(TP);
        return 0;
    }

    item = FIND_STR_IN_OBJECT(args, TP);
    if (!sizeof(item))
        NFN0("You don't have that!");

    for(i = 0; i < sizeof(item); i++)
    {
        if (!shop_hook_allow_sell(item[i]) ||
            !item[i]->query_potion_value() ||
            item[i]->query_prop(OBJ_M_NO_SELL))
        {
            shop_hook_value_not_interesting(item[i]);
            continue;
        }
        price = query_sell_price(item[i]);
        arr = give(price, TP, "", 1);
        shop_hook_value_held(item[i], text(arr[num .. 2 * num -1]));
    }
    return 1;
}

/*
 * Function name: query_object_value
 * Desrciption:   What the object is worth. Allows shops to mask and
 *                value objects differently. Specifically useful for
 *                allowing herb shops, since herbs can normally not
 *                be sold in regular shops.
 */
int
query_object_value(object ob)
{
    if (IS_POTION_OBJECT(ob))
        return ob->query_potion_value() * (ob->num_heap() || 1);

    return ob->query_prop(OBJ_I_VALUE);
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
    if (satchel_file->id(str1))
        ob = clone_object(satchel_file);
    else if (vial_file->id(str1))
        ob = clone_object(vial_file);
    else if (mortar_file->id(str1))
        ob = clone_object(mortar_file);
    else
        return 0;

    price = query_buy_price_special(ob);

    /* in case potions or other potion objects ever become heaps:
     * be sure they can pay before we try to move ob to player,
     * because if ob is a heap and the move succeeds and the player
     * is holding another of that ob, they will merge.
     * too late then to discover that the player can't pay.
     * set 'test' (4th) arg so this call doesn't actually move coins
     */
    if (sizeof(arr = pay(price, this_player(), str2, 1, 0, str3)) == 1)
    {
        shop_hook_buy_cant_pay(ob, arr);
        ob->remove_object();
        return 0;
    }

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

void
smell_air()
{
    write(BSN("The air is filled by the smell of strange potions. " +
        "You cannot make out any one smell clearly enough to identify " +
        "it, but you cannot fail top notice that all the smells " +
        "cannot completely cover the sickly sweet smell of decay " +
        "that drifts through all the rooms here."));
    return;
}

public int
do_smell(string str)
{
    NFN("Smell what?");

    if (!stringp(str) || str == "air")
    {
        smell_air();
        return 1;
    }
    return 0;
}
