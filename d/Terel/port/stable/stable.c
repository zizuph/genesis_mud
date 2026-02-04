inherit "/std/room";
inherit "/lib/trade";

#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <cmdparse.h>
#include <composite.h>
#include <filter_funs.h>

#include "/d/Terel/common/terel_defs.h"

#undef PORT
#define PORT "/d/Terel/port/"

#define STORE_ROOM       (PORT + "stable/store")
#define KEEPER           (PORT + "monster/stable_man")
#define RIDE_PROP        "_can_ride_here"
#define MAXLIST          30
#define NF(xx)           notify_fail(xx)
#define TO               this_object()
#define TP               this_player()
#define ETP              environment(TP)
#define BS(xx)           break_string(xx, 77)
#define BSN(xx)          break_string(xx + "\n", 77)
#define MORE_OBJ         "/std/board/board_more"
#define HORSE_INFO       (PORT + "stable/horse_info.txt")
#define NUM 4
#define SNUM 1

object *sell_it(object *ob, string str);
object *buy_it(object *ob, string str2, string str3);
int not_interesting(object obj);

object keeper;

void
reset_room()
{

   if (keeper) return;

   keeper = clone_object(KEEPER);
   keeper -> move_living("M", TO);
}

/*
 * Function name:   create_room
 * Description:     Initialize this room
 * Returns:
 */
void
create_room()
{
    config_default_trade();
    set_money_give_max(7200);
    set_money_give_out(({1000,480,25,0}));
    set_short("stable");
    set_long(break_string(
       "From the smell you realise that this place must be a stable of "
     + "some kind. On the desk you see a NEW book and "
     + "there is also a small sign with more instructions."
     + "\n", 70));

    add_item("sign", "You should read it!\n");
    add_item("book", "It is a book chained to the desk. You read the title:\n"
                    +"How to handle our horses. You better read it!\n");
    add_item("chain", "It's made of iron and you cannot break it.\n");
    add_exit(STORE_ROOM, "west", "@@wiz_check");
    add_exit(PORT + "road6", "east", 0);

    STORE_ROOM->teleledningsanka();

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(RIDE_PROP, 1);

    reset_room();
}

void
init()
{
    ::init();
    add_action("do_buy", "buy");
    add_action("do_sell", "sell");
    add_action("do_value", "value");
    add_action("do_list", "list");
    add_action("do_read", "read");
}

int
wiz_check()
{
    if (this_player()->query_wiz_level())
      	return 0;
    write("You are prevented from going there " +
	  "by a strong magic force.\n");
    say(QCTNAME(this_player()) + " tries to go west but fails.\n");
    return 1;
}

int
do_read(string str)
{
    if (str == "sign") {
        write(
	    "You can try these instructions: \n" +
	    "   buy horse for gold and get copper back\n" +
	    "   buy horse for gold coins\n" +
	    "   sell horse for copper coins\n" +
	    "   value horse\n" +
	    "   list horses\n" 
	    );
        return 1;
    }
    if (str == "book") {
        seteuid(getuid());
        clone_object(MORE_OBJ)->more(HORSE_INFO, 1);
        return 1;
    }
    NF("Read what?\n");
    return 0;
}

int
do_sell(string str)
{
    object *item;
    int value;
    string str1, str2;

    if (!keeper) {
       NF("You can't do that! The stable keeper is dead!\n");
       return 0;
    }

    if(!str || str =="") {
	NF("Sell what?\n");
	return 0;
    }

    if (sscanf(str, "%s for %s", str1, str2) != 2)
    {
 	str1 = str;
	str2 = "";
    }

    if (parse_command(str1, ETP, "%i", item))
	item = NORMAL_ACCESS(item, 0, 0);
    else
	item = ({ });

    NF("I can't find " + str1 + ".\n");
    if (sizeof(item) == 0)
	if (!(item = ({ present(str1, ETP) }) ))
	    return 0;

    item = sell_it(item - ({ 0 }), str2);
    if (sizeof(item))
    {
	str2 = COMPOSITE_LIVE(item);
	say(QCTNAME(TP) + " sold " + str2 + ".\n");
	write("You sold " + str2 + ".\n");
	return 1;
    }

    return 0; /* Player tried to sell a non sellable object. */
}

/*
 * Function name:   sell_it
 * Description:     Try to let the player sell the item array
 * Returns:         1 on sucess
 * Arguments:       ob - the object array
 *                  str - string describing how the money should be paid
 */
object *
sell_it(object *ob, string str) 
{
    int price, i, j, k, *tmp_arr, *null, *value_arr;
    object *sold;
    mixed tmp;

    STORE_ROOM->short();

    value_arr = allocate(NUM);
    sold = allocate(sizeof(ob));

    for (i = 0; i < sizeof(ob); i++)
    {
        if (not_interesting(ob[i]))
	{
	    NF("We deal only with horses here!\n");
	    continue;
        }
	if (ob[i]->query_mounted()) {
	    NF("Someone is riding it?!\n");
	    continue;
	}
    
	price = ob[i]->query_horse_value();
	if (price <= 0)
	{
	    NF("The "+ob[i]->short()+" has no value!\n");
	    continue;
	}

        if (ob[i]->move(STORE_ROOM))
    	{
	    NF("It seems you are stuck with that.\n");
	    continue;
    	}
	ob[i]->reset_named_by();

        price = price * 100 / query_money_greed_sell();
        tmp_arr = calc_change(price, null, str);
        for (k = 0; k < NUM; k++) value_arr[k] += tmp_arr[k];

        sold[j] = ob[i];
        j++;
        if (j >= 20) break;
    }

    sold = sold - ({ 0 });

    if (sizeof(sold) > 0) {
        change_money(({ 0, 0, 0, 0 }) + value_arr, TP);
        write("You got " + text(value_arr) + ".\n");
    }

    return sold;
}

/*
 * Function name:   do_buy
 * Description:     Try to let the player buy an item
 * Returns:         1 on sucess
 * Arguments:       string - describing how to pay and get change
 */
int
do_buy(string str)
{
    object *item, store;
    string str1, str2, str3;

    if(!keeper){
      NF("You can't do that! The stable keeper is dead!\n");
      return 0;
    }

    if(!str || str =="")
    {
	NF("Buy what?\n");
	return 0;
    }
 
    if (sscanf(str, "%s for %s and get %s", str1, str2, str3) != 3)
    {
        str3 = "";
        if (sscanf(str, "%s for %s", str1, str2) != 2)
        {
            str2 = "";
            str1 = str;
        }
    }

    STORE_ROOM->short();
    store = find_object(STORE_ROOM);

    if (parse_command(str1, store, "%i", item))
	item = NORMAL_ACCESS(item, "fool_filter", TO);
    else
	item = ({ });

    NF("No " + str1 + " present in the stable.\n");
    if (sizeof(item) == 0)
	if (!(item = ({ present(str1, store) }) ))
	    return 0;

    item = (item - ({ 0 })) - ({ store }); /* Don't buy the store room ! ;-) */

    item = buy_it(item, str2, str3);
    if (sizeof(item))
    {
	str2 = COMPOSITE_LIVE(item);
	say(QCTNAME(TP) + " bought " + str2 + ".\n");
	write("You bought " + str2 + ".\n");
	return 1;
    }

    return 0; /* Player tried to sell a non sellable object. */
}

/*
 * Function name:   buy_it
 * Description:     Try to let the player buy the item array
 * Returns:         1 on sucess
 * Arguments:       ob - the object array
 *                  str2 - string describing how the money should be paid
 *                  str3 - what coin types to get chainge back in
 */
object *
buy_it(object *ob, string str2, string str3) 
{
    int price, i, j, k, *value_arr, *arr, error;
    object *bought;


    value_arr = allocate(2 * NUM);
    bought = allocate(sizeof(ob));

    for (i = 0; i < sizeof(ob); i++)
    {
	price = 4 * ob[i]->query_horse_value() *
	    query_money_greed_buy() / 300;

	if (ob[i]->move_living("M", ETP))
	{
	    NF("For some reason the "+ob[i]->short()+" doesn't leave " +
	       "the rear parts of the stable.\n");
	    continue;
	}

	if (sizeof(arr = pay(price, TP, str2, 0, 0, str3)) == 1)
	{
	    ob[i]->move_living("M", STORE_ROOM);
            continue;  /* pay() handles notify_fail() call */
	}

	/* Detect if there was a move error. */
	if (error = arr[sizeof(arr) - 1])
	{
	    if (error < -1)
	    {
	       write("You are carrying magic money my frind, no deal!.\n");
	       continue;
	    }
	}

        for (k = 0; k < 2 * NUM; k++)
            value_arr[k] += arr[k];

	bought[j] = ob[i];
        j++;
	if (j >= 1)
       	    break;
	/* Well, we don't want to let a player accidentily buy too much :) */
    }

    bought = bought - ({ 0 });

    if (sizeof(bought) > 0)
    {
        write("You pay " + text(arr[0 .. NUM - 1]) + ".\n");
	str2 = text(arr[NUM .. 2 * NUM - 1]);
	if (str2)
            write("Your change is " + str2 + ".\n");
    }

    return bought;
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
    int *arr, price, i, j;

    if(!keeper){
      NF("You can't do that! The stable keeper is dead!\n");
      return 0;
    }

    if(!str || str =="")
    {
	NF("Value what?\n");
	return 0;
    }

    if (parse_command(str, ETP, "%i", item))
	item = NORMAL_ACCESS(item, 0, 0);
    else
	item = ({ });

    if (sizeof(item) == 0)
	item = ({ present(str, ETP) });

    item = item - ({ 0 });

    for (i = 0; i < sizeof(item); i++)
    {
	price = item[i]->query_horse_value() * query_money_greed_sell() / 100;
	if (price <= 0) {
	    NF("The "+item[i]->short()+" has no value.\n");
	    continue;
	}
	arr = give(price, TP, "", 1);
	arr = exclude_array(arr, 0, NUM - 1);
	if (!text(arr))
	    write("That animal is not worth anything here.\n");
	else
            write(BS("You would get " + text(arr) + " for the " +
                item[i]->short() + ".\n"));
	j++;
    }

    store = find_object(STORE_ROOM);

    if (parse_command(str, store, "%i", item))
	item = NORMAL_ACCESS(item, "fool_filter", TO);
    else
	item = ({ });

    NF("No " + str + " present in the stable.\n");
    if (sizeof(item) == 0)
	item = ({ present(str, store) });

    item = (item - ({ 0 })) - ({ store });

    for (i = 0; i < sizeof(item); i++)
    {
	price = 4 * item[i]->query_horse_value() *
		query_money_greed_buy() / 300;

	arr = split_values(price); /* A price with few coins possible */
	if (!text(arr))
	    write("That item wouldn't cost you much.\n");
	else
            write(BS("I want " + text(arr) + " for the " +
		item[i]->short() + ".\n"));
	j++;
    }	

    say(QCTNAME(TP) + " asks about some values.\n"); 
    if (j > 0)
	return 1;
    return 0;
}

/*
 * Function name:   do_list
 * Description:     Provide a list of objects in the store room
 * Returns:         0 if not recognised
 *                  1 otherwise
 * Arguments: 	    str - the name of the objects to search for
 */
int
do_list(string str)
{
    object *item_arr;
    int i, price, *arr;

    if (str && str != "horses") {
      NF("List what? Horses?\n");
      return 0;
    }

    if(!keeper){
      NF("You can't do that! The shop keeper is dead!\n");
      return 0;
    }

    STORE_ROOM->short();
    item_arr = all_inventory(find_object(STORE_ROOM));

    if (!sizeof(item_arr))
    {
	NF("The stable has no horses to offer you. Sorry.\n");
	return 0;
    }

    item_arr = filter(item_arr,"horse_filter", TO);

    if (sizeof(item_arr) < 1)
    {
	NF("What are you interested in?\n");
	return 0;
    }

    for (i = 0; i < sizeof(item_arr); i++)
	if (i < MAXLIST)
	{
	    price = 4 * item_arr[i]->query_horse_value() *
		 query_money_greed_buy() / 300;

	    arr = split_values(price);
	    str = sprintf("%-26s",
		 capitalize(LANG_ADDART(item_arr[i]->short())));

	    if (!text(arr))
	        write(str + "That item wouldn't cost you much.\n");
	    else
	        write(BS(str + text(arr) + ".\n"));
	} else {
	    write("Truncated: " + i + ".\n");
	    break;
	}

    return 1;
}

mixed
horse_filter(object ob)
{
    if (function_exists("create_horse", ob)) return 1;
    return 0;
}

int
not_interesting(object ob)
{
    if (!function_exists("create_horse", ob)) return 1;
    return 0;
}

int
fool_filter(object ob) { return 1; }
