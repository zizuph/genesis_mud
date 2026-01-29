/* Use c++ mode in emacs -*- C++ -*- */
/*
 * File name:    high_armoury.c
 * Description:
 *
 * Coded by Percy using modified shop code.
 */

#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <cmdparse.h>
#include <composite.h>
#include <filter_funs.h>
#include <ss_types.h>
#include "../../guild.h"

inherit IN_BASE;

#define MAXLIST    15
/*You can't get more than MAX_POINTS charity for one item!*/
#define MAX_POINTS 10000

object bin, guard;

static  string  store_room; /* The storeroom to use */

#define STORE_ROOM    VROOM + "high_armoury_rack"

static  string  rackstr;    /* The rack to use */

#define RACK   VOBJ + "rack"
static  mixed   money_greed_buy;
static  mixed   money_greed_sell;

#define ALLOW_RACK 1

object shopkeeper, glow_rack;

/*
 * Prototypes
 */
object *sell_it(object *ob, string str, int check);
object *buy_it(object *ob, string str2, string str3);

/*
 * Function name: set_money_greed_buy
 * Description:   Set the greed when player buys something
 * Arguments:     m - The greed in %, VBFC support
 */
void set_money_greed_buy(mixed m) { money_greed_buy = m; }

/*
 * Function name: set_money_greed_sell
 * Description:   Set the greed when player sells something to us
 * Arguments:     m - The greed in %, VBFC support
 */
void set_money_greed_sell(mixed m) { money_greed_sell = m; }

int
query_money_greed_buy()
{
    return this_object()->check_call(money_greed_buy);
}

int query_money_greed_sell()
{
    return this_object()->check_call(money_greed_sell);
}



/*
 * Function name: armoury_hook_allow_donate
 * Description:   If you want to do more testing on objects the player intend
 *        to sell.
 * Argument:      ob - The object player wants to sell
 * Returns:   1 if we allow player to sell the object (default)
 */
int
armoury_hook_allow_donate(object ob)
{
    if (!ob->check_recoverable())
    {
    notify_fail("Only recoverable items are accepted here.\n");
    return 0;
    }
    if (function_exists("create_weapon", ob) || function_exists("create_armour", ob))
      return 1;
    notify_fail("This object is not a valid armour or weapon!\n");
    return 0;
}

/*
 * Function name: shop_hook_sell_no_match
 * Description:   Hook that is called when players tried to sell something
 *        but we couldn't understand what he wanted to sell
 * Arguments:     str - The string player tried to sell
 * Returns:   0
 */
int
shop_hook_sell_no_match(string str)
{
    notify_fail("Can't find '" + str + "'.\n");
    return 0;
}

/*
 * Function name: shop_hook_sold_items
 * Description:   Hook that is called when player sold something
 * Arguments:     item - The item array player sold
 * Returns:   1
 */
int
shop_hook_sold_items(object *item)
{
    write(break_string("You donated " + COMPOSITE_DEAD(item) + ".\n", 75));
    say(QCTNAME(this_player()) + " donated " + QCOMPDEAD + ".\n");
    return 1;
}

/*
 * Function name: shop_hook_sold_nothing
 * Description:   Function called if player sold nothing with sell all
 * Returns:   0
 */
int
shop_hook_sold_nothing()
{
    notify_fail("Nothing donated.\n");
    return 0;
}

/*
 * Function name: shop_hook_sell_no_value
 * Description:   Called if object has no value
 * Arguments:     ob - The object
 */
void
shop_hook_sell_no_value(object ob)
{
    notify_fail(capitalize(LANG_THESHORT(ob)) + " has no value.\n");
}

/*
 * Function name: shop_hook_sell_worn_or_wielded
 * Description:   If object is worn or wielded and player has not said he
 *        wants to sell such an item
 * Arguments:     ob - The object
 */
void
shop_hook_sell_worn_or_wielded(object ob)
{
    notify_fail("You have not specified to donate worn and wielded objects.\n");
}

/*
 * Function name: shop_hook_sell_no_sell
 * Description:   An object has the no sell prop set (OBJ_M_NO_SELL)
 * Arguments:     ob  - The object
 *        str - Set if object has an own not sell string
 */
void
shop_hook_sell_no_sell(object ob, string str)
{
    if (stringp(str))
      notify_fail(str);
    else
      notify_fail("I don't want " + LANG_THESHORT(ob) + ".\n");
}

/*
 * Function name: shop_hook_sell_object_stuck
 * Description:   Object didn't want to be moved to the store room
 * Arguments:     ob  - The object
 *        err - Error code from move
 */
void
shop_hook_sell_object_stuck(object ob, int err)
{
    notify_fail("It seems you are stuck with " + LANG_THESHORT(ob) + ".\n");
}

/*
 * Function name: shop_hook_sell_get_money
 * Description:   Called when player gets money for the stuff he sold
 * Arguments:     str - String describing the money he got
 */
void
shop_hook_sell_get_money(int total)
{
    write("You received " + total + " charity points.\n");
}

/*
 * Function name: shop_hook_allow_buy
 * Description:   A hook to use if you want to test the object further if you
 *        allow it to be bought
 * Arguments:     ob - The object player wants to buy.
 * Returns:   1 if we allow it to be bought (default)
 */
int
shop_hook_allow_buy(object ob)
{
    return 1;
}

/*
 * Function name: shop_hook_buy_no_match
 * Description:   Called if we can't find what player wants to buy
 * Arguments:     str - The string the player typed in
 * Returns:   0
 */
int
shop_hook_buy_no_match(string str)
{
    notify_fail("There is no '" + str + "' in stock.\n");
}

/*
 * Function name: shop_hook_bought_items
 * Description:   Called when player has bought something
 * Arguments:     arr - The array of objects
 * Returns:       1
 */
int
shop_hook_bought_items(object *arr)
{
    write(break_string("You borrowed " + COMPOSITE_DEAD(arr) + ".\n", 75));
    say(QCTNAME(this_player()) + " borrowed " + QCOMPDEAD + ".\n");
    return 1;
}

/*
 * Function name: shop_hook_buy_cant_carry
 * Description:   Player can't carry the object he tried to buy
 * Arguments:     ob  - The object
 *        err - Error code from move()
 */
void
shop_hook_buy_cant_carry(object ob, int err)
{
    notify_fail("You can't carry " + LANG_THESHORT(ob) + ".\n");
}

/*
 * Function name: shop_hook_buy_cant_pay
 * Description:   Called when player can't pay for what he wants to buy.
 *        The /lib/trade.c sets some default error messages but
 *        perhaps you are not happy with them?
 * Arguments:     ob - The object
 *        arr - The error code as it comes from trade.c
 */
void
shop_hook_buy_cant_pay(object ob, int price) {}

/*
 * Function name: shop_hook_buy_magic_money
 * Description:   Called if we failed to take the money from the player for
 *        some strange reason (magic money , fool's gold ? )
 * Arguments:     ob - The object player tried to buy
 */
void
shop_hook_buy_magic_money(object ob)
{
    write("Hrmpf, strange money you have! The deal is off!.\n");
}

/*
 * Function name: shop_hook_buy_pay_money
 * Description:   Called when player pays the money for something
 * Arguments:     str    - How much he pays in text form
 *        change - The change he gets back (if any)
 */
void
shop_hook_buy_pay_money(int price)
{
    write("You pay " + price + " charity points.\n");
}

/*
 * Function name: shop_hook_value_not_interesting
 * Description:   Called when player values something we don't want to buy
 * Arguments:     ob - The object
 */
void
shop_hook_value_not_interesting(object ob)
{
    write(capitalize(LANG_THESHORT(ob)) + " is not interesting.\n");
}

/*
 * Function name: shop_hook_value_held
 * Description:   Player values an object he's holding
 * Arguments:     ob   - The object
 *        text - The price in text form
 */
void
shop_hook_value_held(object ob, int price)
{
    write(break_string("You would get " + price + " charity points for " +
               LANG_THESHORT(ob) + ".\n", 75));
}

/*
 * Function name: shop_hook_value_store
 * Description:   Player values object in store
 * Arguments:     ob   - The object
 *        text - The value in text form
 */
void
shop_hook_value_store(object ob, int price)
{
    write(break_string(capitalize(LANG_THESHORT(ob)) +
               " would cost you " + price + " charity points.\n", 75));
}

/*
 * Function name: shop_hook_value_asking
 * Description:   What other see when someone evaluates something
 * Arguments:     str - The text form what the player is asking about
 */
void
shop_hook_value_asking(string str)
{
    say(QCTNAME(this_player()) + " asks about some values.\n");
}

/*
 * Function name: shop_hook_value_no_match
 * Description:   Called if there were no match with what the player asked
 *        about
 * Arguments:     str - The string player asked about
 * Returns:   0
 */
int
shop_hook_value_no_match(string str)
{
    notify_fail("We hold no '" + str + "' in stock.\n");
}

/*
 * Function name: shop_hook_list_empty_store
 * Description:   If the storeroom is empty when the player wants a list
 *        of its items
 * Arguments:     str - If player specified string
 */
void
shop_hook_list_empty_store(string str)
{
    notify_fail("The store room is currently empty.\n");
}

/*
 * Function name: shop_hook_list_no_match
 * Description:   Called if player specified the list and no matching
 *        objects where found
 * Arguments:     str - The string he asked for
 * Returns:   0
 */
int
shop_hook_list_no_match(string str)
{
    notify_fail("We have no '" + str + "' in stock.\n");
}

/*
 * Function name: shop_hook_list_object
 * Description:   List an object
 * Arguments:     ob - The object
 */
void
shop_hook_list_object(object ob, int price)
{
    string str, mess;

    str = sprintf("%-37s", capitalize(LANG_ASHORT(ob)));
    if (price)
      write(break_string(str + price + " charity points.\n", 75));
    else
      write(str + "That item wouldn't cost you much.\n");
}

/*
 * Function name: shop_hook_appraise_object
 * Description  : Called when a player asks to see an object for sale.
 */
void
shop_hook_appraise_object(object ob)
{
    say(QCTNAME(this_player()) + " asks to see " + LANG_ASHORT(ob) + ".\n");
}


/*
 * Function name: query_buy_price
 * Description:   What price should the player pay
 * Arguments:     ob - The object to test
 * Returns:       The price
 */
int
query_buy_price(object ob)
{
    int seed;
    int realval = ob->query_prop(OBJ_I_VALUE);
    int my_val = F_VALUE_WEAPON(ob->query_hit(),ob->query_pen());
    if (!my_val)
      my_val = F_VALUE_ARMOUR(ob->query_ac());

    if (my_val < realval)
      my_val = realval;

    sscanf(OB_NUM(ob), "%d", seed);
    return  2 * my_val /*ob->query_prop(OBJ_I_VALUE)*/ *
      (query_money_greed_buy() + 15 - this_player()->query_skill(SS_TRADING) / 4 +
       random(15, seed)) / 100;
}

/*
 * Function name: query_sell_price
 * Description:   What price will the player get when selling an object?
 * Arguments:     ob - The object
 * Returns:   The price
 */
int
query_sell_price(object ob)
{
    int seed;
    int num;
    int realval = ob->query_prop(OBJ_I_VALUE);
    int my_val = F_VALUE_WEAPON(ob->query_hit(),ob->query_pen());
    if (!my_val)
      my_val = F_VALUE_ARMOUR(ob->query_ac());

    if (my_val < realval)
      my_val = realval;

    sscanf(OB_NUM(ob), "%d", seed);
    num =           /*ob->query_prop(OBJ_I_VALUE)*/ my_val * 100 /
      (query_money_greed_sell() + 15 - this_player()->query_skill(SS_TRADING) / 3 +
       random(15, seed + 1));   /* Use another seed than on buying */
    return (num > MAX_POINTS ? MAX_POINTS : num);
}

/*
 * Function name: set_store_room
 * Description:   Tell us wich storeroom to use
 * Arguments:     str - The storeroom
 */
void
set_store_room(string store, string rackst)
{
    store_room = store;
    rackstr = rackst;
}

/*
 * Function name: query_store_room
 * Description:   What store room do we use?
 * Returns:   The file name to the store room
 */
string
query_store_room()
{
    return store_room;
}

/*
 * Function name: init_shop
 * Description:   Is called for each living that enters this room
 */
void
init_shop()
{
    add_action("do_buy", "borrow");
    add_action("do_sell", "donate");
    add_action("do_value", "value");
    add_action("do_list", "list");
    add_action("do_read", "read");
    add_action("do_account", "account");
    add_action("do_show","show");
}

/* Show an item to the person */
int
do_show(string str)
{
    object *item_arr;
    int i, *arr;
    object rack;

    call_other(store_room, "load_me");

    rack = present("krynnarm_rack", find_object(store_room));
    item_arr = all_inventory(rack);

    if (!sizeof(item_arr))
    {
    shop_hook_list_empty_store(str);
    return 0;
    }

    item_arr = FIND_STR_IN_ARR(str, item_arr);

    if (sizeof(item_arr) < 1)
    {
    return shop_hook_list_no_match(str);
    }

    shop_hook_appraise_object(item_arr[0]);
    item_arr[0]->appraise_object();

    return 1;
}

int
do_account(string str)
{
    int points;
    points = this_player()->query_skill(108113);
    if (points > 50000)
    {
    points = ((points / 1000) - 5 + random(10, time() / 1000)) * 1000;
    write("Your account stands at roughly " + points + " charity points.\n");
    }
    else
      write("Your account stands at " + points + " charity points.\n");
    return 1;
}
/*
 * Function name: wiz_check
 * Description:   Check if a player is a wizard
 * Returns:       0 if the player is a wizard
 *                1 otherwise
 */
int
wiz_check()
{
    if (this_player()->query_wiz_level())
      return 0;
    write("Some magic force keeps you from going there.\n");
    say(QCTNAME(this_player()) + " tries to enter the storeroom but fails.\n");
    return 1;
}

/*
 * Function name: do_read
 * Description:   If a player wants to know what instuctions can be
 *                used
 * Arguments:     str - string, hopefully "sign"
 * Returns:       1/0
 */
int
do_read(string str)
{
    notify_fail("Read what?\n");
    if (str != "sign")
      return 0;

    write("" +
      "Only Solamnian Knight guild members may use this armoury.\n" +
      "This is the high armoury for items of high value to be donated\n" +
      "and borrowed. It is also the place to leave items of use to\n" +
      "your fellow knights. Members at level nine or higher in the \n" +
      "Order of the Crown, and members of the Rose and Sword Knight\n" +
      "Orders will gain charity points for donating items and lose\n" +
      "charity points and prestige for borrowing items. The amount of\n" +
      "points lost depends on the value of the item.\n" +
      "Only valid armours and weapons can be donated to the armoury.\n" +
      "You can try these instructions: \n" +
      "    account     - tells you how many charity points you have.\n" +
      "    value sword \n" +
      "    borrow sword \n" +
      "    donate sword \n" +
      "    donate all  - will let you donate all items except for\n" +
      "                items you wield or wear.\n" +
      /*"    donate all! - will let you donate ALL items you have, well\n" +
        "                at least the droppable, and no coins.\n" +*/
      "    donate sword, donate second sword, donate sword 2, donate two swords\n" +
      "                also works. You might want to change the verb to\n" +
      "                'value' or 'borrow' too. Beware, you will never borrow\n"+
      "                more than one item at a time. So if you really\n" +
      "                want those three expensive swords, you have to repeat\n" +
      "                yourself three times.\n" +
      "    If you want a list of all swords available in the store, the\n" +
      "    correct syntax is: list swords\n" +
      "                'list weapons', 'list armours' also works\n" +
      "");
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
    object *item;
    int value, check;
    string str1, str2;

    if (!MEMBER(TP))
    {
    notify_fail("You have to be an occupational knight to use " +
            "the rack.\n");
    return 0;
    }
    if (TP->query_knight_level() < 3)
    {
    notify_fail("You have to be a real knight to use the rack.\n");
    return 0;
    }
    if (TP->query_knight_level() == 3 && TP->query_knight_sublevel() < 5)
    {
    notify_fail("You must be of fifth prestige level or higher in " +
            "your order to donate.\n");
    return 0;
    }
    if (!str || str =="")
    {
    notify_fail("Donate what?\n");
    return 0;
    }

    /*  Did player specify how to get the money? */
    if (sscanf(str, "%s for %s", str1, str2) != 2)
    {
    str1 = str;
    str2 = "";
    }

    check = 1;          /* Nothing worn or wielded will be sold. */

    if (str1 == "all!")
    {
    str1 = "all";
    /* check = 0; */ /* Unless the player wants it. */
    /* We never allow selling of worn or wielded items to make
     * sure the value is correct. A weapon or armour may have
     * a different ac/wp/wt if worn/wielded.
     */
    }

    item = FIND_STR_IN_OBJECT(str1, this_player());
    if (!sizeof(item))
      return shop_hook_sell_no_match(str1);

    item = sell_it(item, str2, check);
    if (sizeof(item))
      return shop_hook_sold_items(item);

    if (str1 == "all")
      return shop_hook_sold_nothing();

    return 0;           /* Player tried to sell a non sellable object. */
}

/*
 * Function name: sell_it
 * Description:   Try to let the player sell the item array
 * Arguments:     ob - the object array
 *                check - wheather check for worn or wielded stuff
 *                str - string describing how the money should be paid
 * Returns:   An array with the objects sold
 */
object *
sell_it(object *ob, string str, int check)
{
    int price, i, j, k, *tmp_arr, *null, *value_arr, *null_arr, err, total;
    object *sold;
    mixed tmp;

    call_other(store_room, "load_me"); /* Make sure store room is loaded */

    sold = allocate(sizeof(ob));

    for (i = 0; i < sizeof(ob); i++)
    {
    if (!armoury_hook_allow_donate(ob[i]))
      continue;

    if (ob[i]->query_prop(OBJ_I_VALUE) == 0)
    {
        shop_hook_sell_no_value(ob[i]);
        continue;
    }

    if ((ob[i]->query_prop(OBJ_M_NO_SELL) ||
         ob[i]->query_prop(OBJ_M_NO_DROP)) &&
        !(ob[i]->query_prop(CHAR_OBJ)))
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


    if (tmp = function_exists("create_heap", ob[i]) == "/std/coins")
    {
        shop_hook_sell_no_sell(ob[i], tmp);
        continue;
    }

    /* not set up   if (tmp = ob[i]->query_prop(OBJ_M_NO_DONATE))
       {
       shop_hook_sell_no_sell(ob[i], tmp);
       continue;
       }
       */
    /* Save price if ob destructed in move */
    price = query_sell_price(ob[i]);

    if (price < 200)
    {
        write("The " + ob[i]->short() + " was not stored.\n");
        tmp = ob[i]->short();
        ob[i]->remove_object();
        ob[i] = clone_object(VOBJ + "no_donate_dummy");
        ob[i]->set_short(tmp);
        /* it's just a dummy so that there still exists an object... */
    }
    else
      if (err = ob[i]->move(store_room))
      {
          shop_hook_sell_object_stuck(ob[i], err);
          continue;
      }

    if (price > 0)
    {
        total += price;
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
    shop_hook_sell_get_money(total);
    this_player()->add_charity(total);
    }

    return sold;
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
    object *item, store, rack;
    string str1, str2, str3;

    if (!MEMBER(TP))
    {
    notify_fail("You have to be an occupational knight to use " +
            "the rack.\n");
    return 0;
    }
    if (TP->query_knight_level() < 3)
    {
    notify_fail("You have to be a real knight to use the rack.\n");
    return 0;
    }
    if (TP->query_knight_level() == 3 && TP->query_knight_sublevel() < 5)
    {
    notify_fail("You must be of fifth prestige level of Crown or " +
            "in the Sword or Rose Order to borrow.\n");
    return 0;
    }
    notify_fail("Borrow what?\n");
    if (!str || str =="")
    {
    return 0;
    }

    call_other(store_room, "load_me"); /* Make sure storeroom is loaded */

    /*  Did the player specify payment and change? */
    if (sscanf(str, "%s for %s and get %s", str1, str2, str3) != 3)
    {
    /* Well, maybe player has defined how payment will be done at least? */
    str3 = "";
    if (sscanf(str, "%s for %s", str1, str2) != 2)
    {
        str2 = "";
        str1 = str;
    }
    }
    rack = present("krynnarm_rack", find_object(store_room));

    item = FIND_STR_IN_OBJECT(str1, rack);

    if (!sizeof(item))
      return shop_hook_buy_no_match(str1);

    item = buy_it(item, str2, str3);
    if (sizeof(item))
      return shop_hook_bought_items(item);

    return 0;           /* Player tried to sell a non sellable object. */
}

/*
 * Function name: buy_it
 * Description:   Try to let the player buy the item array
 * Arguments:     ob - the object array
 *                str2 - string describing how the money should be paid
 *                str3 - what coin types to get chainge back in
 * Returns:       1 on sucess
 */
object *
buy_it(object *ob, string str2, string str3)
{
    int price, i, j, k, *value_arr, *arr, error, num, err, total;
    object *bought;

    bought = allocate(sizeof(ob));

    for (i = 0; i < sizeof(ob); i++)
    {
    if (!shop_hook_allow_buy(ob[i]))
      continue;

    price = query_buy_price(ob[i]);

    /* If you don't feel greedy you can shorten the calculation above. */

    if (err, ob[i]->move(this_player()))
    {
        shop_hook_buy_cant_carry(ob[i], err);
        continue;
    }

    if (this_player()->query_skill(108113) < price)
    {
        ob[i]->move(store_room, 1);
        shop_hook_buy_cant_pay(ob[i], price);
        notify_fail("You haven't enough points for that!\n");
        continue;       /* pay() can handle notify_fail() call */
    }
    if (this_player()->query_skill(108113) > price)
    {
        this_player()->sub_charity(price);
        this_player()->change_prestige(-(price / 10), 1);
    }
    total += price;
    bought[j] = ob[i];
    j++;
    if (j >= 1)
      break;
    /* Well, we don't want to let a player accidentily buy too much :) */
    }

    bought = bought - ({ 0 });

    if (sizeof(bought) > 0)
      shop_hook_buy_pay_money(total);

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
    object *item, store, rack;
    int *arr, price, i, j, num;

    if (!str || str =="")
    {
    notify_fail("Value what?\n");
    return 0;
    }

    item = FIND_STR_IN_OBJECT(str, this_player());

    for (i = 0; i < sizeof(item); i++)
    {
    if (!armoury_hook_allow_donate(item[i]) ||
        !item[i]->query_prop(OBJ_I_VALUE) ||
        item[i]->query_prop(OBJ_M_NO_SELL))
    {
        shop_hook_value_not_interesting(item[i]);
        continue;
    }

    price = query_sell_price(item[i]);
    shop_hook_value_held(item[i], price);
    j++;
    }

    call_other(store_room, "load_me");
    rack = present("krynnarm_rack", find_object(store_room));
    item = FIND_STR_IN_OBJECT(str, rack);

    for (i = 0; i < sizeof(item); i++)
    {
    price = query_buy_price(item[i]);
    shop_hook_value_store(item[i], price);
    j++;
    }

    shop_hook_value_asking(str);
    if (j > 0)
      return 1;

    return shop_hook_value_no_match(str);
}

/*
 * Function name:   do_list
 * Description:     Provide a list of objects in the store room
 * Returns:         0 if not recognised
 *                  1 otherwise
 * Arguments:       str - the name of the objects to search for
 */
int
do_list(string str)
{
    object *item_arr, rack;
    int i, price, *arr;

    call_other(store_room, "load_me");
    /* call_other("/d/Krynn/solamn/vkeep/obj/rack.c", "load_me"); */
    rack = present("krynnarm_rack", find_object(store_room));
    if (rack)
    {
    item_arr = all_inventory(rack);
    }
    if (!sizeof(item_arr))
    {
    shop_hook_list_empty_store(str);
    return 0;
    }

    if (str == "weapons")
      item_arr = filter(item_arr, "weapon_filter", this_object());
    else if (str == "armours")
      item_arr = filter(item_arr, "armour_filter", this_object());
    else if (str)
      item_arr = FIND_STR_IN_ARR(str, item_arr);

    if (sizeof(item_arr) < 1)
      return shop_hook_list_no_match(str);


    for (i = 0; i < sizeof(item_arr); i++)
      if (i < MAXLIST)
      {
      price = query_buy_price(item_arr[i]);
      shop_hook_list_object(item_arr[i], price);
      }

      else
      {
      write("Truncated: " + i + ".\n");
      break;
      }

    return 1;
}

/*
 * Function name: weapon_filter
 * Description:   Filter out weapons
 */
int
weapon_filter(object ob)
{
    return (function_exists("create_object", ob) == "/std/weapon");
}

/*
 * Function name: armour_filter
 * Description:   Filter out armours
 */
int
armour_filter(object ob)
{
    return (function_exists("create_object", ob) == "/std/armour");
}

/*
 * Function name:   create_room
 * Description:     Initialize this room
 */
void
create_vin_room()
{
    set_money_greed_buy(80);
    set_money_greed_sell(75);
    set_short("The Solamnian Knight High Armoury");
    set_long("You are in the High Armoury of the Solamnian Knights. " +
         "Here, a high-ranking Knight of the Crown, or any " +
         "Knight of the Sword or Rose may borrow and donate items of " +
         "power for the good of the Knights of Solamnia guild. " +
         "This is also a room in which Knights of Solamnia may " +
         "leave any items which could be of use to their fellow " +
         "Knights. There is a small sign to read with instructions " +
         "on how to use this armoury.\n");

    AI(({"wall","ceiling","floor"}),"It is made of typical Vingaard " +
       "Keep granite.\n");
    AI("walls","They are made of the typical Vingaard Keep granite.\n");
    AI(({"granite","keep granite","vingaard keep granite"}),"A grey " +
       "volcanic rock, that is used throughout the Keep.\n");
    AI(({"rock","volcanic rock","grey rock","grey volcanic rock"}),
       "It is granite.\n");
    ACI("sign", "read", "@@do_read");
    AI("sign", "A nice looking sign, perhaps you should read it.\n");
    AE(VROOM + "high_armoury_rack", "north", "@@wiz_check", 0, 1);
    AE(VROOM + "armoury", "south", 0);

    add_prop(ROOM_I_LIGHT,2);   /* This is a real room */
    INSIDE;         /* This is a real room */
    add_prop(ROOM_I_NO_CLEANUP, 1); /* prevent room updates and loss of equipment */

    set_store_room(STORE_ROOM, RACK);
    reset_room();
}

void
reset_vin_room()
{
    if (!bin)
    {
    bin = clone_object(VOBJ + "bin.c");
    bin->move(TO);
    }
    if (!guard)
    {
    guard = clone_object(NPCSTD + "vin_knight_base");
    guard->move(TO);
    guard->command("list");
    }
    if (bin && all_inventory(bin) && sizeof(all_inventory(bin)))
    {
    tell_room(TO, "A well-muscled black-bearded male dwarf arrives.\n" +
          "The smith gets " + COMPOSITE_DEAD(all_inventory(bin)) +
          " from the " + bin->short() + ".\n" +
          "The well-muscled black-bearded male dwarf leaves " +
          "south.\n");
    all_inventory(bin)->remove_object();
    }

#ifdef  ALLOW_RACK
    if (!glow_rack)
    {
        //glow_rack = clone_object(VOBJ + "glow_rack");
        //glow_rack->move(TO);
    }
#endif

}

/*
 * Function name:   init
 * Description:     Is called for each living that enters this room
 * Returns:
 */
void
init()
{
    ::init();           /* You MUST do this in a room-init */
    init_shop();        /* Get the commands from the shop */
}


/* Code to mark all items that are dropped on the floor in
 * the armoury.
 */
/*
   void
   enter_inv(object dest, object old)
   {
       ::enter_inv(dest, old);

       if (dest->query_prop(LIVE_I_IS))
     return;
       if (dest->query_prop(ARM_PROP))
     return;
       else
     set_alarm(2.0, -1.0, "mark_items", dest);
       return;
   }
   */

void
mark_items(object dest)
{
    string ll = dest->query_long();

    if (!dest || !stringp(ll) || !strlen(ll) || !stringp(ll))
    {
        return;
    }

    if (ll != dest->long() && sizeof(explode(ll,"@@")) % 2 == 0)
    {
      dest->set_long(dest->query_long() + "@@\nIt bears the distinctive mark of "+
                     "the Solamnian Armoury.\n");
    }
    else
    {
      dest->set_long(dest->query_long() + "\nIt bears the distinctive mark of "+
                    "the Solamnian Armoury.\n");
    }
    dest->add_item(({"mark", "sigil"}), "A kingfisher bird bearing a "+
                     "sword in one claw and a rose in the other.\n");
    dest->add_prop(ARM_PROP,1);

    if (!guard)
    {
        return;
    }
    tell_room(TO, "The knight guard carefully marks the " +
              dest->short() + " with the sigil of the armoury.\n");
}

