 /*
  *  /d/Sparkle/area/jade/rooms/jade_stand.c
  *
  *  Doing business in the Jade Forest is dangerous - shopkeepers are often
  *  attacked for their goods.  This fruit stand runs on the honor system -
  *  pay or be honored by the far-sighted archer in the attic. Change consists
  *  of a limited amount of copper and silver.
  *
  *  Shop code based on:  /d/Sparkle/guilds/new_merc/mess_hall.c
  *
  *  Created 2017-02-03 by Martin Berka (Mar)
  *
  */

#pragma strict_types
#include "../defs.h"

inherit "/lib/trade";
inherit ROOM_DIR + "jade_room";

#include <composite.h>
#include <language.h>
#include <macros.h>
#include <money.h>
#include <stdproperties.h>
#include <time.h>


/* definitions */
#define NUM              sizeof(MONEY_TYPES)
#define COIN_TYPES       ({ "cc", "sc", "gc", "pc" })
#define MY_PRICES        ({ 50, 300, 750, 500 })
#define COMMON_FRUIT_DIR "/d/Genesis/start/human/wild2/obj/"


/* Global Variables */
object  gate,    //The other side of the orchard gate is an exit.
        family1; //NPC native to this room

/* Prototypes */
public void     create_room();
public void     reset_room();
public int      can_afford(int price, int number, string ware,
                    string pay_type, string get_type);
public int      do_buy(string str);
public int      do_steal();
public string   fruit_sign();

/*
 * Function name:        create_room
 * Description  :        set up the room
 */
public void
create_room()
{
    set_short("A fruit stand in the northern part of a yard");
    set_long("A large sign and a table stand next to a giant pile of fruit. "
        + "The fruit stand is surrounded on three sides by a fence, the only "
        + "way out to the south, where a small yard lies before a two-storey "
        + "house. A path leads through a closed gate to the east, beyond "
        + "which is an orchard. Beyond the fence to the north and the west, "
        + "scorched earth holds back the Jade Forest.\n");

    add_item( ({"table", "stand", "fruit stand", "legs", "table legs"}),
        "The table holds a strongbox and a smaller box with change. Its "
        + "legs appear to be embedded in the ground.\n");
    add_item( ({"table", "stand", "fruit stand", "legs", "table legs"}),
        "The table holds a strongbox and a smaller box with change. Its "
        + "legs appear to be embedded in the ground.\n");
    add_item( ({"strongbox", "iron strongbox", "safe", "chain", "slit",
        "narrow slit"}),
        "The iron strongbox is chained to the table. You see no way to open it ."
        + "A narrow slit in the top is accompanied by an embossed label.\n");
    add_item( ({"box", "box with change", "change box", "smaller box",
        "smaller box with change", "small box with change", "change"}),
        "The change box is built into the surface of the table and contains a "
        + "handful of silver and copper coins.\n");
    add_item( ({"label", "embossed label"}),
            "The letters are stamped into the surface - even a blind "
            + "person could read them.\n");
    add_cmd_item( ({"label", "embossed label"}),
        ({"read"}), "Insert money here.\n" );

    add_item( ({"ground", "dirt", "packed dirt", "sparse grass"}),
        "The ground here is a mixture of packed dirt and sparse grass.\n");

    add_item( ({"fruit", "fruits", "pile", "giant pile", "pile of fruits"}),
        "The fruits are in varying states of ripeness. There seem to be more "
        + "than could normally be sold to passers-by.\n");
    add_cmd_item( ({"fruit from pile", "fruits from pile", "pile",
        "pile of fruits", "box", "strongbox", "money from box",
        "money from strongbox", "coins from box", "change box"}),
            ({"get", "take", "grab", "steal"}), "@@do_steal" );

    add_item( ({"sign", "large sign", "list", "pricelist", "prices"}),
            "@@fruit_sign@@" );
    add_cmd_item( ({"sign", "large sign", "list", "pricelist", "prices"}),
        ({"read"}), fruit_sign() );

    add_item( ({"orchard", "trees", "fruit trees", "grass", "lush grass"}),
        "The orchard beyond the fence is full of lush grass and fruit trees.\n" );

    add_fence( ({ "southeast", "northeast", "north", "northwest", "west" }) );
    add_deadzone();
    add_forest();
    add_house();

    add_exit(ROOM_DIR + "jade_yard", "south");
    add_exit(ROOM_DIR + "jade_yard", "southwest", 0, 1, 1);

    config_default_trade();
    set_money_give_max(850); //Half a platinum
    set_money_give_out( ({ 95, 63, 0, 0 }) ); //Can't have valuables in the box
    set_money_give_reduce( ({ 1, 1, 1, 1 }) );

    /* Gate to orchard */
    gate = clone_object("/std/door");
    gate->set_door_id("orchard_gate");
    gate->set_pass_command( ({ "e", "east" }) );
    gate->set_door_name( ({ "gate", "sturdy gate", "east gate", "gateway",
        "wooden gate", "sturdy wooden gate", "eastern gate",
        "fence gate", "gate to the east", "gateway to the east",
        "fencegate", "gate in the fence", "sharpened gate" }) );
    gate->set_open_desc("There is a gate in the fence leading east.\n");
    gate->set_closed_desc("There is a gate in the fence to the west.\n");
    gate->set_fail_pass("The sturdy wooden gate is closed.\n");
    gate->set_open_mess( ({ "opens the gate in the sturdy wooden fence.\n",
                          "The gate in the sturdy wooden fence opens.\n" }) );
    gate->set_close_mess( ({ "closes the sturdy wooden gate door.\n",
                           "The gate in the sturdy wooden fence closes.\n" }) );
    gate->set_door_desc("A gate leads through the fence. Its construction is "
        + "much like the fence's. There is no handle or clear way to open it "
        + "from this side.\n");
    //gate->set_other_room(ROOM_DIR + "jade_orchard_w");
    gate->set_open(0);
    gate->set_locked(1);
    gate->move(TO);

    setuid();
    seteuid(getuid());

    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(PATH_HOME_PROP, "south");

    reset_room();
} /* create_room */


/*
 * Function name:       reset_room
 * Description  :       Populate room with potential role-holder NPC
 */
public void
reset_room()
{
    if (!objectp(family1))
    {
        family1 = clone_object(NPC_DIR + "family.c");
        family1->set_family_index(1);
        family1->move(TO);
    }
} /* reset_room */


/*
 * Function name: init
 * Description:   Set up the commands, ensure that gate closes when anyone
 *      arrives through it.
 */
void
init()
{
    ::init();

    add_action(do_buy, "buy",   0);
    add_action(do_buy, "purchase", 0);

    if (gate->query_open())
    {
        tell_room(TO, "The gate in the wooden fence slams shut.\n", 0);
        gate->set_open(0);  //It's a one-way gate.
    }
} /* init */


/*
 * Function name: do_steal
 * Description  : Lets the player try to steal fruit or money from the stand.
 * Returns      : (string) Message to display - ""
 */
string do_steal()
{
    write("You reach out, and -\n");
    find_object(ARCHER_ROOM)->send_arrow(this_player());
    return one_of_list( ({"Clearly that is not allowed.\n",
        "Maybe you should read the sign.\n",
        "You give up - it is not worth the pain.\n" }) );
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
} /* money_text */


/*
 * Function name: fruit_sign
 * Description  : Print the fruit pricelist
 * Returns      : The text on the sign.
 */
string
fruit_sign()
{
    return (
      "The sign reads:\n\n"
    + "Welcome! Here you can <buy>:\n\n"
    + "      ITEM:                       PRICE:\n"
    + "Apple / Peach / Pear..." + money_text(MY_PRICES[0]) + "\n"
    + "     Jade pear      ..." + money_text(MY_PRICES[1]) + "\n"
    + "     Neh fruit      ..." + money_text(MY_PRICES[2]) + "\n\n"
    + "     HOMEMADE:                     PRICE:\n"
    + "  Jar of fruit jam  ..." + money_text(MY_PRICES[3]) + "\n\n"
    + "This fruit stand operates on the honour system:\n"
    + "Pay or be honoured with arrows.\n"
    + "Change is limited.\n");
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
        write("You cannot carry your purchase, so it just sits there.\n");
        if (ob->move(TO))
            ob->move(TO, 1);
    }

    if (strlen(desc))
    {
        say(QCTNAME(tp) + " slowly, carefully buys " + desc + ".\n");
    }
    else
    {
        say(QCTNAME(tp) + " slowly, carefully buys " + LANG_ASHORT(ob) + ".\n");
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

    switch (lower_case(item_name))
    {
        case "apple":
        case "apples":
            file = COMMON_FRUIT_DIR + "apple";
            ware = "apple";
            price = MY_PRICES[0];
            break;
        case "peach":
        case "peaches":
            file = COMMON_FRUIT_DIR + "peach";
            ware = "peach";
            price = MY_PRICES[0];
        case "pear":
        case "pears":
            file = COMMON_FRUIT_DIR + "pear";
            ware = "pear";
            price = MY_PRICES[0];
            break;
        case "jade":
        case "jades":
        case "jade pear":
        case "jade pears":
                file = OBJ_DIR + "jade_pear";
                ware = "jade pear";
                price = MY_PRICES[1];
            break;
        case "neh":
        case "nehs":
        case "neh fruit":
        case "neh fruits":
        case "fruit":
        case "fruits":
                file = OBJ_DIR + "neh_fruit";
                ware = "neh fruit";
                price = MY_PRICES[2];
            break;
        case "jam":
        case "jams":
        case "jar":
        case "jars":
        case "jam jar":
        case "jam jars":
        case "fruit jam":
        case "fruit jams":
        case "jar of fruit jam":
        case "jars of fruit jam":
                file = OBJ_DIR + "herb_jam";
                ware = "jar of fruit jam";
                price = MY_PRICES[3];
            break;
        default:
            notify_fail(
                "You don't see any in the pile.\n");
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
            the_max = hook_query_max_items();
    string  item_name,
            pay_type,
            get_type;

    if (!strlen(str))
    {
        notify_fail("What do you wish to buy? You can <read pricelist> for"
          + " a list of available items.\n");
        return 0;
    }

    if (!CAN_SEE_IN_ROOM(tp))
    {
        write("You have to feel around blindly for coins.\n");
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

    if (number > the_max)
    {
        notify_fail("I'm afraid you cannot buy more than " + the_max
                  + " items at a time.\n");
        return 0;
    }

    return buy_it(item_name, number, pay_type, get_type);
} /* do_buy */


public void
hook_not_got_coin_type(string pay_type, object tp)
{
    write("You don't have any " + pay_type + " coins!\n");
} /* hook_not_got_coin_type */


public void
hook_not_enough_coin_type(string pay_type, string ware, object tp)
{
    write("You set your " + pay_type + "coins on the table and reach for "
        + ware + ". Someone shouts: That's not enough! You stop and retrieve "
        + "your coins.\n");
} /* hook_not_enough_coin_type */


public void
hook_not_enough_money(object tp, string ware)
{
    write("You set your coins on the table  and reach for " + ware + ".\n");
    write("Someone shouts: Hey, that's not enough!\n");
    write("You stop and retrieve your coins.\n");
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
        write("You slowly take "+ LANG_ADDART(ware) + " from the pile and "
            + "set it on the table, along with " + coin_pay_text + ". When "
            + "nothing happens, you put the coins in the strongbox and take your "
            + "purchase.\n");
    }
    else
    {
        write("You put " + coin_pay_text + " in the box and take " +
            LANG_WNUM(number) + " "+LANG_PWORD(ware)
          + " and pay "+coin_pay_text+".\n");
    }

    if (strlen(coin_get_text))
    {
        write( "You slide " + coin_get_text + " from the change box onto the "
            + "table and wait. When nothing happens, you take them.\n");
    }

    return 1;
} /* can_afford */
