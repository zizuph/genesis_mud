/*
 *      /d/Emerald/telberin/arts/inn.c
 *
 *      This will be the Silver Swan Inn in Telberin. It also
 *      contains many useful routines for Inns in General.
 *
 *      Copied from /d/Gondor/common/lib/inn.c by Elessar,
 *        Olorin, and Gnadnar. In particular, this code has
 *        Gnadnar's signature quality to it.
 *
 *      Copyright (c) March 2003, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/lib/trade.c";

#include <language.h>
#include <macros.h>
#include <money.h>
#include <stdproperties.h>

#include "/d/Emerald/blackwall/delrimmon/defs.h"

#define NUM             sizeof(MONEY_TYPES)
#define COIN_TYPES      ({ "cc", "sc", "gc", "pc" })
#define MY_PRICES       ({ 3, 8, 12, 36, 75, 12, 24, 48, 216, 540, 144})
#define STAND_DIR       ("/d/Emerald/telberin/obj/")

#define	INNKEEPER_PRESENT \
    (!Have_innkeeper || (objectp(Innkeeper_npc) && ENV(Innkeeper_npc) == TO))
#define	CAP_INNKEEPER(pl) \
    (Have_innkeeper ? Innkeeper_npc->query_The_name(pl) : Innkeeper_Name)
#define	LOW_INNKEEPER(pl) \
    (Have_innkeeper ? Innkeeper_npc->query_the_name(pl) : Innkeeper_name)
#define	QCT_INNKEEPER \
    (Have_innkeeper ? QCTNAME(Innkeeper_npc) : Innkeeper_Name)
#define	QT_INNKEEPER \
    (Have_innkeeper ? QTNAME(Innkeeper_npc) : Innkeeper_name)


static int      Have_innkeeper;	/* is there an npc innkeeper?	*/
static object   Innkeeper_npc;	/* the npc. 			*/

/* if not using an npc, can still customize the innkeeper's name */
static string   Innkeeper_Name = "The innkeeper";
static string   Innkeeper_name = "the innkeeper";

public int      can_afford(int price, int number, string ware,
                    string pay_type, string get_type);
public int      do_buy(string str);
public int      check_inn_time(string str);
public string   price_long();
public void     set_innkeeper_npc(object npc);
public void     set_innkeeper_name(string name);

/*
 * Function name: init_inn
 * Description:   set up the commands
 * Usage:         void
 *                init()
 *                {
 *                    init_inn();
 *                    ::init();
 *                }
 */
void
init_inn()
{
    add_action(do_buy, "buy",   0);
    add_action(do_buy, "order", 0);

    add_action(check_inn_time, "time", 0);
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
            txt += sprintf("%2d %2s ", arr[ind], COIN_TYPES[ind]);
        else
            txt += "      ";
    }

    return txt;
}

/*
 * Function name: price_long
 * Description:   print the menu
 *                dummy example
 * Usage:         in create_room()
 *                add_item(({"menu", "prices", }), price_long());
 *                add_cmd_item(({"menu", "prices", }), "read", price_long());
 */
string
price_long()
{
   return (
      "The pricelist reads:\n\n"
    + "DRINKS:\n"
    + "   Spring Water          ...  " + money_text(MY_PRICES[0]) + "\n"
    + "   Stout Porter          ...  " + money_text(MY_PRICES[1]) + "\n"
    + "   Hefeweizen            ...  " + money_text(MY_PRICES[2]) + "\n"
    + "   Southland Wine        ...  " + money_text(MY_PRICES[3]) + "\n"
    + "   Rimmon Cognac         ...  " + money_text(MY_PRICES[4]) + "\n\n"
    + "HOT MEALS:\n"
    + "   Creamed Oats          ...  " + money_text(MY_PRICES[5]) + "\n"
    + "   Onion Soup            ...  " + money_text(MY_PRICES[6]) + "\n"
    + "   Baked Potato          ...  " + money_text(MY_PRICES[7]) + "\n"
    + "   Roasted Duck          ...  " + money_text(MY_PRICES[8]) + "\n"
    + "   Filet of Venison      ...  " + money_text(MY_PRICES[9]) + "\n\n"
    + "ROOMS:\n"
    + "   Key for a room        ...  " + money_text(MY_PRICES[10]) + "\n\n");
}

/*
 * Function name: buy_item
 * Description:   clone and move the bought item
 * Arguments:     item   - filename of item to clone
 *                number - heap size of item
 *                desc   - description for item
 */
void
buy_item(string item, int number = 1, string desc = 0)
{
    object  ob,
            tp = TP;

    ob = clone_object(item);
    ob->set_heap_size(number);

    if (ob->move(tp))
    {
        WRITE("Since you cannot carry that much, "+LOW_INNKEEPER(tp)
            + " puts the "+ob->short()+" down on a table.");
        if (ob->move(TO))
            ob->move(TO, 1);
    }

    if (strlen(desc))
        SAY(" orders " + desc + ".");
    else
        SAY(" orders " + LANG_ASHORT(ob) + ".");
}

/*
 * Function name: buy_it
 * Description:   identify the item the player tries to buy
 *                dummy example
 * Arguments:     item_name - the name
 *                number    - the amount
 *                pay_type  - coins to pay with
 *                get_type  - coins for change
 * Returns:       0/1 - failure/success
 */
public int
buy_it(string item_name, int number, string pay_type, string get_type)
{
    string     tmpstr;
    switch (item_name)
    {
        case "water":
        case "spring water":
            if (can_afford(MY_PRICES[0], number, "spring water", pay_type, get_type))
                buy_item(STAND_DIR + "water", number);
            break;
        case "porter":
        case "stout porter":
            if (can_afford(MY_PRICES[1], number, "stout porter",
                           pay_type, get_type))
                buy_item(STAND_DIR + "porter", number);
            break;
        case "beer":
        case "hefeweizen":
            if (can_afford(MY_PRICES[2], number, "hefeweizen",
                           pay_type, get_type))
                buy_item(STAND_DIR + "hefeweizen", number);
            break;
        case "wine":
        case "southland wine":
            if (can_afford(MY_PRICES[3], number, "southland wine",
                           pay_type, get_type))
                buy_item(STAND_DIR + "wine", number);
            break;
        case "cognac":
        case "rimmon cognac":
            if (can_afford(MY_PRICES[4], number, "rimmon cognac",
                           pay_type, get_type))
                buy_item(STAND_DIR + "cognac", number);
            break;
        case "oats":
        case "creamed oats":
            if (can_afford(MY_PRICES[5], number, "creamed oats",
                           pay_type, get_type))
                buy_item(STAND_DIR + "oats", number);
            break;
        case "soup":
        case "onion soup":
            if (can_afford(MY_PRICES[6], number, "onion soup",
                           pay_type, get_type))
                buy_item(STAND_DIR + "soup", number);
            break;
        case "potato":
        case "baked potato":
            if (can_afford(MY_PRICES[7], number, "baked potato",
                           pay_type, get_type))
                buy_item(STAND_DIR + "potato", number);
            break;
        case "duck":
        case "roasted duck":
            if (can_afford(MY_PRICES[8], number, "roasted duck",
                           pay_type, get_type))
                buy_item(STAND_DIR + "duck", number);
            break;
        case "venison":
        case "filet":
        case "filet of venison":
        case "venison filet":
            if (can_afford(MY_PRICES[9], number, "filet of venison",
                           pay_type, get_type))
                buy_item(STAND_DIR + "venison", number);
            break;
        case "room":
        case "key":
        case "key for a room":
        case "single room":
        case "night":
            if (number > 1)
            {
                WRITE(CAP_INNKEEPER(TP)+
                  " says: Only one room at a time! And only for one night!");
                return 1;
            }
            if (can_afford(MY_PRICES[10], number, "room", pay_type, get_type))
            {
                buy_item("/d/Emerald/telberin/obj/hotel_key", number,
                    "a single room to spend the night in Telberin");
                WRITE(CAP_INNKEEPER(TP)+
                    " gives you the key to the room. Don't lose it!");
            }
            break;
        default:
            NF(CAP_INNKEEPER(TP)+
                " says: We don't have that on the menu.\n");
            return 0;
            break;
    }

    return 1;
}


public int
hook_query_max_items()
{
    return 6;
}

/*
 * Function name: do_buy
 * Description:   parse the command
 * Arguments:     str - argument to command verb
 * Returns:       0/1 - failure/success
 */
public int
do_buy(string str)
{
    object  tp = TP;
    int     number,
            buy_max = hook_query_max_items();
    string  item_name,
            pay_type,
            get_type;

    if (!strlen(str))
        return 0;

    if (TO->query_prop(OBJ_I_LIGHT) < 1)
    {
        if ( INNKEEPER_PRESENT )
        {
            if (CAN_SEE_IN_ROOM(tp))
                WRITE(CAP_INNKEEPER(tp)
              + " says: Sorry, it's too dark in here - I can't see!");
            else
                write("Someone says: Sorry, it's too dark in here - "
                  + "I can't see!\n");
        }
        else
        {
            if (CAN_SEE_IN_ROOM(tp))
                write("There is no one here to serve you.\n");
            else
                /* strictly speaking, we should let them figure out that
                 * there's no response by making no response, but someone's
                 * sure to report that as a bug.
                 */
                 write("You hear no response to your request for service.\n");
        }
        return 1;
    }

    if ( !INNKEEPER_PRESENT )
    {
        write("There is no one here to serve you.\n");
        return 1;
    }

    str = LOW(str);

    if ((sscanf(str,"%d %s for %s and get %s",
                number, item_name, pay_type, get_type) != 4) &&
        (sscanf(str,"%s for %s and get %s",
                item_name, pay_type, get_type) != 3))
    {
        get_type = "";
        if ((sscanf(str,"%d %s for %s", number, item_name, pay_type) != 3) &&
            (sscanf(str,"%s for %s", item_name, pay_type) != 2))
        {
            pay_type = "";
            if (sscanf(str, "%d %s", number, item_name) != 2)
                item_name = str;
        }
    }

    if (number <= 0)
        number = 1;

    if (number > buy_max)
    {
        NFN("You cannot buy more than "+buy_max+" items at a time!");
        return 0;
    }

    return buy_it(item_name, number, pay_type, get_type);
}

public void
hook_not_got_coin_type(string pay_type, object tp)
{
    write(CAP_INNKEEPER(tp)+" says: You haven't got any "
      + pay_type + " coins, honoured "
      + (tp->query_gender() ? "Lady" : "Sir") + ".\n");
}

public void
hook_not_enough_coin_type(string pay_type, string ware, object tp)
{
    write(CAP_INNKEEPER(tp)+" says: You haven't got enough "
      + pay_type + " coins to pay for the " + ware
      + ", honoured "
      + (tp->query_gender() ? "Lady" : "Sir") + ".\n");
}

public void
hook_not_enough_money(object tp, string ware)
{
    write(CAP_INNKEEPER(tp)+" says: If you had enough money "
      + "to pay for the " + ware + ", I would be glad to serve "
      + "you, honoured "
      + (tp->query_gender() ? "Lady" : "Sir") + ".\n");
}

/*
 * Function name: can_afford
 * Description:   Test if this_player has more money on him than the price
 * Arguments:     price  - the price in cc
 *                number - the amount to buy
 *                ware   - a description of the item to buy
 *                pay_type - coins to pay with
 *                get_type - coin type for change
 * Returns:       0/1 - failure/success
 */
public int
can_afford(int price, int number, string ware, string pay_type, string get_type)
{
    object  tp = TP;
    int    *money_arr,
            tot_price;
    string  coin_pay_text,
            coin_get_text;

    tot_price = price * number;

    if (sizeof(money_arr = pay(tot_price, tp, pay_type, 0, 0, get_type)) == 1)
    {
        switch (money_arr[0])
        {
            case 2:
                hook_not_got_coin_type(pay_type, tp);
                break;
            case 1:
                hook_not_enough_coin_type(pay_type, ware, tp);
                break;
            default:
                hook_not_enough_money(tp, ware);
                break;
        }
        return 0;
    }

    coin_pay_text = text(exclude_array(money_arr, NUM, NUM*2-1));
    coin_get_text = text(exclude_array(money_arr, 0, NUM-1));

    if (number == 1)
        WRITE("You order "+LANG_ADDART(ware)+" and pay "+coin_pay_text+".");
    else
        WRITE("You order "+LANG_WNUM(number)+" "+LANG_PWORD(ware)
          + " and pay "+coin_pay_text+".");
    if (strlen(coin_get_text))
        WRITE(CAP_INNKEEPER(tp)+" hands you "+coin_get_text+
              " back in change.");
    return 1;
}

/*
 * Function name: check_inn_time
 * Description:   Redefine 'time' command inside the inn
 * Argument:      str - command verb argument
 * Returns:       1
 */
public int
check_inn_time(string str)
{
    object       tp = TP;
    if (INNKEEPER_PRESENT)
    {
        WRITE("You ask "+LOW_INNKEEPER(tp)+" what time it is.");
        tell_room(TO,
            QCTNAME(tp)+" asks "+QT_INNKEEPER+" what time it is.\n", tp);
        tell_room(TO, QCT_INNKEEPER+" says: It is about "+TO->qstime()+".\n");
        return 1;
    }
    return 0;   /* fall back on normal "time" command */
}


/*
 * Function name:       set_innkeeper_npc
 * Description  :       use a real npc as the innkeeper
 * Arguments    :       object npc -- the npc
 *
 * This should be called each time the npc is cloned.
 */
public void
set_innkeeper_npc(object npc)
{
    Have_innkeeper = 1;
    Innkeeper_npc = npc;
}

/*
 * Function name:       set_innkeeper_name
 * Description  :       customize the innkeeper name when not
 *                      using a real npc as the innkeeper
 * Arguments    :       string arg -- the name (e.g., "the bartender")
 */
public void
set_innkeeper_name(string name)
{
    if ( strlen(name) )
    {
        Innkeeper_name = LOW(name);
        Innkeeper_Name = CAP(name);
    }
}

