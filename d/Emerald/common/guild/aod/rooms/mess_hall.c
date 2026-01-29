/*
 *  /d/Emerald/common/guild/aod/rooms/mess_hall.c
 *
 *  The Mess Hall for the Army of Darkness. This only becomes operable once
 *  the guild has collected a sufficient number of Hobbit skulls.
 *
 *  Created July 2006, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit AOD_ROOM_DIR + "cave_room";
inherit AOD_LIB_DIR + "add_spike";
inherit "/lib/trade.c";

#include <language.h>
#include <macros.h>
#include <money.h>
#include <stdproperties.h>
#include <time.h>


/* definitions */
#define NUM              sizeof(MONEY_TYPES)
#define COIN_TYPES       ({ "cc", "sc", "gc", "pc" })
#define MY_PRICES        ({ 12, 32, 70, 21, 210, 530 })
#define TP               this_player()
#define TO               this_object()
#define LUNCH_INFO(x,y) (TROPHY_MASTER->get_info(x, y))




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


/* Global Variables */
static int         Have_innkeeper; /* is there an npc innkeeper?   */
static object      Innkeeper_npc;  /* the npc.                     */

/* if not using an npc, can still customize the innkeeper's name */
static string      Innkeeper_Name = "The innkeeper";
static string      Innkeeper_name = "the innkeeper";
static object      Innkeeper;

/* Prototypes */
public void        create_cave_room();
public int         can_afford(int price, int number, string ware,
                       string pay_type, string get_type);
public int         do_buy(string str);
public string      price_long();
public void        set_innkeeper_npc(object npc);
public void        set_innkeeper_name(string name);
public void        ring_bell(string arg);
public int         free_lunch(string arg);


/*
 * Function name:        create_cave_room
 * Description  :        set up the room
 */
public void
create_cave_room()
{
    set_short("a cavernous mess hall");
    set_em_long("You have come into an extremely disgraceful place! This"
      + " cavernous area within the rock has been made into a mess"
      + " hall for the Ogre soldiers of the Army. And 'mess' is clearly"
      + " an understatement! Scraps of meat and bits of ripped flesh"
      + " are strewn all over the floor, large pools of ale and wine"
      + " are everywhere, and the place is simply swarming with flies."
      + " To an Ogre, of course, this is some kind of heaven. You can"
      + " <exa pricelist> to see what is available. A large stone"
      + " counter rises along the north wall where the waiter"
      + " usually is.\n");

    add_item( ({ "here", "area" }), long);
    add_item( ({ "counter", "stone counter", "large counter",
                 "large stone counter" }),
        "The counter has a gigantic iron bell on it. If the waiter"
      + " isn't around, you can always <hit bell> to try to get his"
      + " attention.\n");
    add_item( ({ "cavern", "cave", "cavernous area", "mess hall",
                 "hall" }),
        "This appears to be a place of eating. Ogre eating! A large"
      + " hole in the north wall opens onto a kitchen of some kind.\n");
    add_item( ({ "place" }),
        "Positively disgraceful!\n");
    add_item( ({ "disgraceful place" }),
        "Most definitely ... as disgraceful as it gets!\n");
    add_item( ({ "north wall", "northern wall" }),
        "There is a large hole in it.\n");
    add_item( ({ "hole", "large hole" }),
        "It appears to open onto a kitchen of some kind.\n");
    add_item( ({ "kitchen" }),
        "Kitchen? More like a slaughter house! You can hear cows"
      + " mooing in terror in there!\n");
    add_item( ({ "slaughter house", "house" }),
        "As you peer in, you see a cow sprint down a corridor, chased"
      + " by an ogre wielding a cleaver.\n");
    add_item( ({ "cow", "cows" }),
        "Oh yes ... an Ogre favorite!\n");
    add_item( ({ "mooing", "moo" }),
        "MOOOOOOOOOOOOOOOOOOOOOOOOO!!!!!\n");
    add_item( ({ "mess" }),
        "Oh, to say the least. Hercules would take the stables of the"
      + " Gods over this place any day of the week!\n");
    add_item( ({ "scrap", "scraps", "meat", "meat scraps",
                 "scrap of meat", "meat scrap", "scraps of meat",
                 "flesh", "ripped flesh" }),
        "Looks like bits of cow!\n");
    add_item( ({ "bit", "bits", "cow bit", "cow bits", "bit of cow",
                 "bits of cow" }),
        "To think, this was once a noble bovine, smelling the clean"
      + " air of the clover field. Oh, the bovinity!\n");
    add_item( ({ "pool", "pools" }),
        "Ale ... wine ... pools of it!\n");
    add_item( ({ "ale" }),
        "Not the finest brew. You could float a paper boat in it!\n");
    add_item( ({ "wine" }),
        "If you didn't know better, you'd almost mistake this for a pool"
      + " of blood. Hmmm ... come to think of it ...\n");
    add_item( ({ "fly", "flies" }),
        "You breathe in ten or twelve with every sniff!\n");
    add_item( ({ "gigantic iron bell", "bell", "iron bell",
                 "gigantic bell" }),
        "It looks like something that was ripped out of a church"
      + " steeple! You can <hit bell> to try to get the waiter's"
      + " attention.\n");
    add_item( ({ "paper boat" }),
        "Do you have one? No, you don't.\n");
    add_item( ({ "blood", "pool of blood" }),
        "Its just wine after all ... darn!\n");
    add_item( ({ "heaven" }),
        "Heaven this ain't! Well ... maybe to an Ogre.\n");
    add_item( ({ "pricelist", "list", "prices", "menu", "bill",
                 "bill of fare" }), price_long());

    add_cmd_item( ({ "pricelist", "list", "prices", "menu", "bill",
                     "bill of fare" }),
                  ({ "read" }), price_long());

    add_cave_items();
    add_spike("mess_hall");

    config_default_trade();
    set_money_give_max(2000);
    set_money_give_out( ({ 2000, 700, 50, 4 }) );
    set_money_give_reduce( ({ 1, 1, 1, 1 }) ); 

    add_exit("tunnel4", "west");
    reset_room();
} /* create_cave_room */


/*
 * Function name:       summon_innkeeper
 * Description  :       restore npc as needed
 */
public void
summon_innkeeper()
{
    object    npc;

    if (!present("_army_of_darkness_waiter"))
    {
        npc = clone_object(AOD_NPC_DIR + "waiter")->move(this_object());
        tell_room(this_object(), "The waiter charges in from the"
          + " kitchen bellowing: WHO THERE??! WHAT WANT?\n");
    }
    else
    {
        tell_room(this_object(),
            "The waiter booms: ME HERE! WHAT YOU WANT?!\n");
    }
} /* summon_innkeeper */


/*
 * Function name:       reset_room
 * Description  :       clone sign, etcetera
 */
public void
reset_room()
{
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
    add_action(ring_bell, "hit");
    add_action(ring_bell, "ring");
    add_action(ring_bell, "smack");
    add_action(free_lunch, "demand");
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
    + "   GROG:                          PRICES:\n\n"
    + "   Piss Barrel         ...  " + money_text(MY_PRICES[0]) + "\n"
    + "   Keg of Rotgut       ...  " + money_text(MY_PRICES[1]) + "\n"
    + "   Bucket of Moonshine ...  " + money_text(MY_PRICES[2]) + "\n\n"
    + "   TREATS:                        PRICES:\n\n"
    + "   Roasted Calf        ...  " + money_text(MY_PRICES[3]) + "\n"
    + "   Cow on a stick      ...  " + money_text(MY_PRICES[4]) + "\n"
    + "   Buffalo Surprise    ...  " + money_text(MY_PRICES[5]) + "\n\n"
    + "You may purchase items using the <buy> command.\n"
    + "If the waiter is not around, you can <hit bell> for"
    + " service.\n"
    + "Officers of the Army may <demand grub> here for a free lunch.\n\n");
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
            + " plops the "+ob->query_short()+" down at your feet.\n");
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
        case "barrel":
        case "barrels":
        case "piss":
        case "piss barrel":
        case "piss barrels":
        case "barrel of piss":
        case "barrels of piss":
                file = AOD_OBJ_DIR + "piss";
                ware = "piss barrel";
                price = MY_PRICES[0];
            break;
        case "rotgut":
        case "rotguts":
        case "keg":
        case "kegs":
        case "keg of rotgut":
        case "kegs of rotgut":
        case "rotgut keg":
        case "rotgut kegs":
                file = AOD_OBJ_DIR + "rotgut";
                ware = "rotgut keg";
                price = MY_PRICES[1];
            break;
        case "moonshine":
        case "moonshines":
        case "bucket":
        case "buckets":
        case "moonshine bucket":
        case "moonshine buckets":
        case "bucket of moonshine":
        case "buckets of moonshine":
                file = AOD_OBJ_DIR + "moonshine";
                ware = "moonshine bucket";
                price = MY_PRICES[2];
            break;
        case "calf":
        case "calfs":
        case "roasted calf":
        case "roasted calfs":
                file = AOD_OBJ_DIR + "calf";
                ware = "calf";
                price = MY_PRICES[3];
            break;
        case "cow":
        case "cows":
        case "stick":
        case "sticks":
        case "cow on a stick":
        case "cows on a stick":
        case "cow stick":
        case "cow sticks":
        case "skewered cow":
        case "skewered cows":
        case "cow skewer":
        case "cow skewers":
        case "skewer":
        case "skewers":
                file = AOD_OBJ_DIR + "cow";
                ware = "skewered cow";
                price = MY_PRICES[4];
            break;
        case "buffalo":
        case "buffalos":
        case "surprise":
        case "surprises":
        case "buffalo surprise":
        case "buffalo surprises":
        case "bucket of moonshine":
        case "buckets of moonshine":
                file = AOD_OBJ_DIR + "buffalo";
                ware = "buffalo surprise";
                price = MY_PRICES[5];
            break;
        default:
            notify_fail(
              "The waiter booms: NOT SERVE THAT! LOOK PRICELIST!!!\n");
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
          + " a list of available items.\n");
        return 0;
    }

    if (this_object()->query_prop(OBJ_I_LIGHT) < 1)
    {
        if (!present("_army_of_darkness_waiter"))
        {
            if (CAN_SEE_IN_ROOM(tp))
                write(CAP_INNKEEPER(tp)
              + " says: TOO DARK! NOT SEE YOU!\n");
            else
                write("Someone says: TOO DARK! NOT SEE YOU!\n");
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

    if (!present("_army_of_darkness_waiter"))
    {
        write("There is no one here to serve you. You notice a large"
          + " iron bell on the counter, however. You can probably"
          + " <hit bell> to try and get the waiter in here.\n");
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
    write(CAP_INNKEEPER(tp)+" booms: YOU STUPID! YOU NOT HAVE "
      + upper_case(pay_type) + " COINS!\n");
} /* hook_not_got_coin_type */


public void
hook_not_enough_coin_type(string pay_type, string ware, object tp)
{
    write(CAP_INNKEEPER(tp)+" booms: NO!!! NOT HAVE ENOUGH "
      + upper_case(pay_type) + " COINS TO BUY " + upper_case(ware)
      + "!\n");
} /* hook_not_enough_coin_type */


public void
hook_not_enough_money(object tp, string ware)
{
    write(CAP_INNKEEPER(tp)+" booms: NOT BUY!!! NOT HAVE MONEY!\n");
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
        write(CAP_INNKEEPER(tp)+" looks a bit confused for a few"
          + " minutes, and then hands you "+coin_get_text+
            " back in change. Forcing an Ogre to do math is almost"
          + " cruel, you know!\n");
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
 * Arguments    :       string arg -- the name (e.g., "the waiter")
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
    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    write("You smack the bell with your fist. BONNNNNNGGGG!\n");
    tell_room(this_object(), QCTNAME(this_player())
      + " smacks the bell with " + this_player()->query_possessive()
      + " fist. BONNNNNNNNGGGG!\n", this_player());

    reset_room();

    return 1;
} /* ring_bell */


/*
 * Function name:        free_lunch
 * Description  :        Officers can get their once-a-day free grub
 *                       here.
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
free_lunch(string arg)
{
    string  general,
            corporal,
            time_txt = TIME2FORMAT(time(), "d mmm yyyy"),
            my_name = this_player()->query_real_name(),
            refusal;
    object  drinks,
            grub;

    if (!strlen(arg))
    {
        notify_fail("Demand what?\n");
        return 0;
    }

    if (arg != "grub")
    {
        notify_fail("Do you want to demand some grub, perhaps?\n");
        return 0;
    }

    if (!AOD_GENERAL(this_player()) &&
        !AOD_CORPORAL(this_player()))
    {
        write("You are in no position to make demands! Maybe if you"
          + " were an officer of the Army things would be different.\n");
        return 1;
    }

    refusal = "You have already gotten your free lunch today! Come"
            + " back tomorrow!\n";

    if (AOD_GENERAL(this_player()))
    {
        if (AOD_LUNCH_MASTER->get_info(LUNCH_FILE, "General") ==
            my_name &&
            AOD_LUNCH_MASTER->get_info(LUNCH_FILE, "Gen_Time") ==
            time_txt)
        {
            write(refusal);
            return 1;
        }

        AOD_LUNCH_MASTER->set_info(LUNCH_FILE, "General", my_name);
        AOD_LUNCH_MASTER->set_info(LUNCH_FILE, "Gen_Time", time_txt);
    }
    else
    {
        if (AOD_LUNCH_MASTER->get_info(LUNCH_FILE, "Corporal") ==
            my_name &&
            AOD_LUNCH_MASTER->get_info(LUNCH_FILE, "Corp_Time") ==
            time_txt)
        {
            write(refusal);
            return 1;
        }

        AOD_LUNCH_MASTER->set_info(LUNCH_FILE, "Corporal", my_name);
        AOD_LUNCH_MASTER->set_info(LUNCH_FILE, "Corp_Time", time_txt);
    }

    write("Panic fills the kitchen momentarily as cooks scramble to"
      + " meet your demands! After a great deal of crashing, breaking,"
      + " and throttling, an ogre-style free lunch is dropped at"
      + " your feet.\n");

    drinks = clone_object(AOD_OBJ_DIR + "piss");
    drinks->set_heap_size(12);
    drinks->move(this_object());

    grub = clone_object(AOD_OBJ_DIR + "buffalo");
    grub->move(this_object());

    tell_room(this_object(), QCTNAME(this_player()) + " stomps "
      + this_player()->query_possessive() + " mighty foot on the"
      + " ground and demands some grub! Panic fills the kitchen"
      + " momentarily as cooks scramble over one another in"
      + " response. After a good deal of death and destruction"
      + " has taken place, an ogre-style free lunch is dropped"
      + " at " + this_player()->query_possessive() + " feet.\n",
        this_player());

    return 1;
} /* free_lunch */
