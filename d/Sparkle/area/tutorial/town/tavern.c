/*
 *  /d/Sparkle/area/tutorial/town/tavern1.c
 *
 *  This is the Grey Goose Tavern in Greenhollow. It will
 *  teach players about Soaked and Alcohol.
 *
 *  Copied with permission from /d/Gondor/common/lib/inn.c
 *  by Elessar, Olorin, and Gnadnar.
 *
 *  Created July 2005, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit SD_ROOM;
inherit "/lib/trade.c";

#include <language.h>
#include <macros.h>
#include <money.h>
#include <stdproperties.h>


/* definitions */
#define NUM             sizeof(MONEY_TYPES)
#define COIN_TYPES      ({ "cc", "sc", "gc", "pc" })
#define MY_PRICES        ({ 6, 9, 20 })
#define TP              this_player()
#define TO              this_object()
#define TUTORIAL_CHAPTER  17  /* the chapter for the sign */




#define INNKEEPER_PRESENT \
    (!Have_innkeeper || (objectp(Innkeeper_npc) && \
      environment(Innkeeper_npc) == this_object()))
#define CAP_INNKEEPER(pl) \
    (Have_innkeeper ? Innkeeper_npc->query_The_name(pl) : Innkeeper_Name)
#define LOW_INNKEEPER(pl) \
    (Have_innkeeper ? Innkeeper_npc->query_the_name(pl) : Innkeeper_name)
#define QCT_INNKEEPER \
    (Have_innkeeper ? QCTNAME(Innkeeper_npc) : Innkeeper_Name)
#define QT_INNKEEPER \
    (Have_innkeeper ? QTNAME(Innkeeper_npc) : Innkeeper_name)


/* prototypes */
static int      Have_innkeeper; /* is there an npc innkeeper?   */
static object   Innkeeper_npc;  /* the npc.                     */

/* if not using an npc, can still customize the innkeeper's name */
static string   Innkeeper_Name = "The innkeeper";
static string   Innkeeper_name = "the innkeeper";
static object   Innkeeper;

public int      can_afford(int price, int number, string ware,
                    string pay_type, string get_type);
public int      do_buy(string str);
public string   price_long();
public void     set_innkeeper_npc(object npc);
public void     set_innkeeper_name(string name);
public void     ring_bell(string arg);
public int      hint(string arg);


/*
 * Function name:       create_silverdell()
 * Description  :       create the room
 */
public void
create_silverdell()
{
    set_short("the Red Weasel Tavern");
    set_long("This is the Red Weasel Tavern. Dark wood panels"
      + " the walls, giving this a cozy atmosphere for"
      + " drinking and socializing with friends. You can"
      + " <exa pricelist> here to get an idea of what is"
      + " available for your pleasures. Be sure to read the"
      + " tutorial sign as well. You hear laughter and"
      + " merrymaking coming from a room to the west.\n\n");

    add_item( ({ "tavern", "weasel", "red weasel",
                 "area", "here", "room", "building",
                 "read weasel tavern" }), long);
    add_item( ({ "wall", "walls", "wood", "dark wood",
                 "panel", "panels", "dark wood panel",
                 "dark wood panels", "wood panel",
                 "wood panels" }),
        "The walls are panelled in dark wood which adds"
      + " a cozy quality to the ambiance of the tavern.\n");
    add_item( ({ "west", "room to the west", "laughter",
                 "merrymaking" }),
        "There look to be a few people having a good time in"
      + " the room to the west.\n");
    add_item( ({ "counter", "bell", "silver bell",
                 "small silver bell" }),
        "There is a small silver bell on the counter. A card beside"
      + " it reads: <ring bell> for service.\n");
    add_item( ({ "card", "bar", "counter", }),
        "There is a card on the bar that reads: If I'm not here,"
      + " just <whistle> to get my attention.\n");
    add_item( ({ "pricelist", "list", "prices", "menu", "bill",
                 "bill of fare" }), price_long());

    add_cmd_item( ({ "pricelist", "list", "prices", "menu", "bill",
                     "bill of fare" }),
                  ({ "read" }), price_long());

    add_cmd_item( ({ "card" }),
                  ({ "read" }),
        "The card reads: If I'm not here, just <whistle> to get"
      + " my attention.\n");

    add_indoor_items();
    add_window_items();
    add_door_items();

    prevent_attacks();

    add_prop(ROOM_I_INSIDE,1);

    config_default_trade();
    set_money_give_max(2000);
    set_money_give_out( ({ 2000, 700, 50, 4 }) );
    set_money_give_reduce( ({ 1, 1, 1, 1 }) ); 

    add_exit("street_2", "north");
    add_exit("tavern2", "west");
    reset_room();
} /* create_silverdell */


/*
 * Function name:       summon_innkeeper
 * Description  :       restore npc as needed
 */
public void
summon_innkeeper()
{
    object    npc;

    if (!present("_silverdell_bartender"))
    {
        npc = clone_object(NPC_DIR + "bartender")->move(this_object());
        tell_room(this_object(), "The bartender pokes his head over the"
          + " bar and says: What can I get'cha?\n");
    }
    else
    {
        tell_room(this_object(),
            "The bartender smiles and says: What can I get'cha?\n");
    }
} /* summon_innkeeper */


/*
 * Function name:       reset_room
 * Description  :       clone sign, etcetera
 */
public void
reset_room()
{
    if (!present("_tutorial_sign"))
    {
        add_sign(TUTORIAL_CHAPTER);
    }

    set_alarm(2.0, 0.0, "summon_innkeeper");
} /* reset_room */


/*
 * Function name: init
 * Description:   set up the commands
 */
void
init()
{
    ::init();

    add_action(do_buy, "buy",   0);
    add_action(do_buy, "order", 0);
    add_action(ring_bell, "whistle");
    add_action(hint, "hint");
} /* init */


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
} /* money_text */


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
    + "   DRINKS:                             PRICES:\n\n"
    + "   Amber Ale         ...  " + money_text(MY_PRICES[0]) + "\n"
    + "   Barley Wine       ...  " + money_text(MY_PRICES[1]) + "\n"
    + "   Shot of Whiskey   ...  " + money_text(MY_PRICES[2]) + "\n\n"
    + "You may purchase drinks using the <buy> command.\n"
    + "If the bartender is not present, you may <whistle> for"
    + " service.\n\n");
} /* price_long */


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
            tp = this_player();

    ob = clone_object(item);
    ob->set_heap_size(number);

    if (ob->move(tp))
    {
        write("Since you cannot carry that much, "+LOW_INNKEEPER(tp)
            + " puts the "+ob->short()+" down on a table.\n");
        if (ob->move(TO))
            ob->move(TO, 1);
    }

    if (strlen(desc))
    {
        say(QCTNAME(tp) + " orders " + desc + ".\n");
    }
    else
    {
        say(QCTNAME(tp) + " orders " + LANG_ASHORT(ob) + ".\n");
    }
} /* buy_item */


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
    string      file,
                ware;
    int         price;


    switch (item_name)
    {
        case "ale":
        case "amber ale":
        case "amber":
        case "beer":
        case "ales":
        case "amber ales":
        case "beers":
        case "ambers":
                file = OBJ_DIR + "ale";
                ware = "ale";
                price = MY_PRICES[0];
            break;
        case "wine":
        case "wines":
        case "barley wine":
        case "barley wines":
        case "bottle":
        case "bottles":
        case "bottle of wine":
        case "bottles of wine":
                file = OBJ_DIR + "wine";
                ware = "wine bottle";
                price = MY_PRICES[1];
            break;
        case "whiskey":
        case "whiskies":
        case "shot":
        case "shots":
        case "shot of whiskey":
        case "shots of whiskey":
        case "whiskey shot":
        case "whiskey shots":
                file = OBJ_DIR + "whiskey";
                ware = "whiskey shot";
                price = MY_PRICES[2];
            break;
        default:
            notify_fail(
              "The bartender says: We don't serve that here.\n");
            return 0;
    }

    if (can_afford(price, number, ware, pay_type, get_type))
    {
        buy_item(file, number, ware);
    }

    return 1;
} /* buy_it */


public int
hook_query_max_items()
{
    return 6;
} /* hook_query_max_items */


/*
 * Function name: do_buy
 * Description:   parse the command
 * Arguments:     str - argument to command verb
 * Returns:       0/1 - failure/success
 */
public int
do_buy(string str)
{
    object  tp = this_player();
    int     number,
            buy_max = hook_query_max_items();
    string  item_name,
            pay_type,
            get_type;

    if (!strlen(str))
    {
        notify_fail("What do you wish to buy? You can <read pricelist> for"
          + " a list of available drinks.\n");
        return 0;
    }

    if (this_object()->query_prop(OBJ_I_LIGHT) < 1)
    {
        if (!present("_silverdell_bartender"))
        {
            if (CAN_SEE_IN_ROOM(tp))
                write(CAP_INNKEEPER(tp)
              + " says: Sorry, it's too dark in here - I can't see!\n");
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

    if (!present("_silverdell_bartender"))
    {
        write("There is no one here to serve you. You notice a small"
        + " card on the bar that reads: If I'm not here, just"
        + " <whistle> to get my attention.\n");
        return 1;
    }

    str = lower_case(str);

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
        notify_fail("I'm afraid you cannot buy more than " + buy_max
                  + " items at a time.\n");
        return 0;
    }

    return buy_it(item_name, number, pay_type, get_type);
} /* do_buy */


public void
hook_not_got_coin_type(string pay_type, object tp)
{
    write(CAP_INNKEEPER(tp)+" says: You haven't got any "
      + pay_type + " coins, there, "
      + (tp->query_gender() ? "Missy" : "Bub") + ".\n");
} /* hook_not_got_coin_type */


public void
hook_not_enough_coin_type(string pay_type, string ware, object tp)
{
    write(CAP_INNKEEPER(tp)+" says: You haven't got enough "
      + pay_type + " coins to pay for the " + ware
      + ", there, "
      + (tp->query_gender() ? "Missy" : "Bub") + ".\n");
} /* hook_not_enough_coin_type */


public void
hook_not_enough_money(object tp, string ware)
{
    write(CAP_INNKEEPER(tp)+" says: If you had enough money "
      + "to pay for the " + ware + ", I would be glad to serve "
      + "you some, "
      + (tp->query_gender() ? "Missy" : "Bub") + ".\n");
} /* hook_not_enough_money */


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
    {
        write("You order "+LANG_ADDART(ware)+" and pay "+coin_pay_text+".\n");
    }
    else
    {
        write("You order "+LANG_WNUM(number)+" "+LANG_PWORD(ware)
          + " and pay "+coin_pay_text+".\n");
    }

    if (strlen(coin_get_text))
    {
        write(CAP_INNKEEPER(tp)+" hands you "+coin_get_text+
              " back in change.\n");
    }

    return 1;
} /* can_afford */


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
} /* set_innkeeper_npc */


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
        Innkeeper_name = lower_case(name);
        Innkeeper_Name = capitalize(name);
    }
} /* set_innkeeper_name */


/*
 * Function name:        ring_bell
 * Description  :        allow players to summon the innkeeper if
 *                       the innkeeper is not present.
 * Arguments    :        string arg - what the player typed
 * Returns      :        int 1 - success, 0 - otherwise
 */
public int
ring_bell(string arg)
{
    if (strlen(arg))
    {
        return 0; /* turn it into an emote instead */
    }

    write("You whistle for the bartender.\n");
    tell_room(this_object(), QCTNAME(this_player())
      + " whistles for the bartender.\n", this_player());

    reset_room();

    return 1;
} /* ring_bell */


/*
 * Function name:        hint
 * Description  :        give the player a hint if they get stuck
 * Arguments    :        string - what the player typed
 * Returns      :        int 1
 */
public int
hint(string arg)
{
    write("A hint? Sure ... Unless you have already trained your skills"
      + " up, you might not want to spend money on alcohol just yet. It"
      + " is an essential tool when you want to do a lot of combat. But,"
      + " if you are just starting out, skill training is a better use of"
      + " your money.\n");
 
    return 1;
} /* hint */

