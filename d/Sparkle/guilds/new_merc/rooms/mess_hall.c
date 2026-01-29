/*
 *  /d/Sparkle/guilds/new_merc/mess_hall.c
 *
 *  This room is a real multi-tasker! It has the following functionality:
 *
 *    - You can order food, courtesy of Gondor Inn code.
 *    - Guild members can <feast> here once a day to completely fill
 *      their bellies.
 *    - You can sit at tables, courtesy of Gnadnar's excellent
 *      room_chair.c code, also originally from Gondor.
 *    - You can enjoy the fire, relighting it and such if it goes
 *      out, courtesy again of Gnadnar and her fireplace code from
 *      Gondor.
 *    - It houses the bulletin board of the guild.
 *    - It has a fairly uncanny waitress - not to be underestimated!
 *    - It has a fun easter egg for players who want to go to the trouble
 *      to find it! (the broth in the cauldron)
 *
 *  As if that weren't enough, this is also the destination room for
 *  the Merc Spy quest, which involves the object:
 *
 *      /d/Sparkle/guilds/new_merc/obj/journal.c
 *
 *  Created June 2009, by Cooper Sherry (Gorboth)
 *    Much credit must go to Gnadnar - so much of the code is hers.
 */
#pragma strict_types
#include "../merc_defs.h"

inherit MERC_ROOM_BASE;
inherit "/lib/trade";
inherit "/d/Emerald/blackwall/delrimmon/legacy/fireplace";
inherit "/d/Emerald/blackwall/delrimmon/legacy/room_chairs";

#include <composite.h>
#include <language.h>
#include <macros.h>
#include <money.h>
#include <stdproperties.h>
#include <time.h>
#include "/d/Emerald/blackwall/delrimmon/legacy/room_chairs.h"
#include "/d/Emerald/blackwall/delrimmon/legacy/fireplace.h"


/* definitions */
#define NUM              sizeof(MONEY_TYPES)
#define COIN_TYPES       ({ "cc", "sc", "gc", "pc" })
#define MY_PRICES        ({ 12, 32, 70, 21, 210, 530 })
#define TP               this_player()
#define TO               this_object()
#define LUNCH_INFO(x,y) (MERC_MASTER->get_info(x, y))
#define BLOCK_NAME       "dining tables"



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
static object      Board;          /* The Merc Bulletin Board      */

/* if not using an npc, can still customize the innkeeper's name */
static string      Innkeeper_Name = "The innkeeper";
static string      Innkeeper_name = "the innkeeper";
static object      Innkeeper;

/* Prototypes */
public void        create_merc_room();
public int         check_exit();
public void        summon_innkeeper(int silent = 0);
public void        reset_room();
public int         can_afford(int price, int number, string ware,
                       string pay_type, string get_type);
public int         do_buy(string str);
public string      price_long();
public void        set_innkeeper_npc(object npc);
public void        set_innkeeper_name(string name);
public void        ring_bell(string arg);
public int         free_lunch(string arg);
public object      make_board();
public mixed       copy_merc_note_to_journal();
public string      finish_copying();
public string      fire_desc(string arg);
public int         do_sit(string arg);
public void        do_sit_msgs(object pl, string prep, string name);
public void        do_stand_msgs(object pl, string name);
public string      look_tables();
public void        leave_inv(object ob, object dest);
public string      show_subloc(string subloc, object pl, object for_obj);
public string      sitting_on_chair(string name, object for_obj, int namesonly, int definite = 1);
public int         drink_broth(string arg);
public string      cook_sleeping_txt();
public int         cook_asleep();


/*
 * Function name:        create_merc_room
 * Description  :        set up the room
 */
public void
create_merc_room()
{
    set_short("in a large feasting hall");
    set_long("@@fire_desc@@"); /* use VBFC for room description */

    add_chair(BLOCK_NAME, "[down] [at] [in] [on] [one] [of] [the] [nearby]"
                        + " [large] [dining] "
                        + " 'table' / 'tables' / 'chair' / 'chairs'",
                          20, "at", 0);
    set_fire_container("chimney");
    /* set the pattern for the parse_command() */
    set_parse_pattern("[the] [enormous] 'chimney'");

    add_item( ({ "hall", "feasting hall", "here", "room", "area",
                 "large hall", "large feasting hall",
                 "dining room", "feasting room", "large room",
                 "place" }),
        "This is one of the most popular rooms in the lodge, and one"
      + " can see why - a roaring fire, food, and a place to sit down."
      + " What more can a tired traveller ask for?\n");
    add_item( ({ "food" }),
        "Your belly can be cheered up a bit if you feel like placing"
      + " an <order> with the waitress.\n");
    add_item( ({ "waitress" }),
        "If she isn't around, just <ring> the bell.\n");
    add_item( ({ "bell", "brass bell", "large bell", "large brass bell" }),
        "A large brass bell is mounted to the wall near the kitchen. A"
      + " metal rod on a thin cord hangs beside it in case anyone wants"
      + " to <ring> it.\n");
    add_item( ({ "rod", "metal rod" }),
        "It is used for ringing the bell. I wouldn't recommend it, though"
      + " if the waitress is already in the room.\n");
    add_item( ({ "cord", "thin cord" }),
        "It's got a metal rod tied to it. Nifty!\n");
    add_item( ({ "chimney", "enormous chimney", "fireplace",
                 "huge fireplace" }),
        "The chimney fills much of the northern wall. It has been built"
      + " with deep red bricks.\n");
    add_item( ({ "northern wall", "north wall", "north",
                 "wall to the north" }),
        "The northern wall has a few windows, but is mostly occupied"
      + " by the huge fireplace and chimney.\n");
    add_item( ({ "brick", "bricks", "red brick", "red bricks",
                 "deep red brick", "deep red bricks" }),
        "Hardened mortar has slopped from between the bricks where they"
      + " were pressed together to make the chimney.\n");
    add_item( ({ "mortar", "hardened mortar" }),
        "The sloppy look of the mortar has a certain quaint charm.\n");
    add_item( ({ "west wall", "west", "western wall", "wall to the west" }),
        "The western wall has many windows which look out over the"
      + " training grounds.\n");
    add_item( ({ "training", "training ground", "training grounds" }),
        "Looking out the windows in the west wall, you get a fairly good"
      + " view of them.\n");
    add_item( ({ "south wall", "southern wall",
                 "wall to the south" }),
        "There is no southern wall. Rather, the dining hall simply"
      + " adjoins with the entry hall in that direction.\n");
    add_item( ({ "entry hall", "entry", "south" }),
        "The entry hall is south of here. Every so often you notice"
      + " guild members walking through it.\n");
    add_item( ({ "east", "east wall", "eastern wall",
                 "wall to the east" }),
        "The wall to the east has a doorway leading into the kitchen in it."
      + " On one side of the doorway a large menu has been posted. On the"
      + " other is a window which the cook passes orders through to"
      + " be picked up by the waitress.\n");
    add_item( ({ "east window", "window in the east wall" }),
        "The window in the east wall is much bigger than those that line"
      + " the rest of the room.\n");
    add_item( ({ "doorway", "door", "passage", "passageway" }),
        "The doorway leading into the kitchen actually does not have a"
      + " door inside it. Rather, it is simply a passage that is always"
      + " left open.\n");
    add_item( ({ "kitchen" }),
        "You can't see much of the kitchen from here. You'd have to go"
      + " through the doorway to the east to see what is going on in"
      + " there.\n");
    add_item( ({ "firepit", "pit", "shallow pit",
                 "shallow firepit" }), &fire_desc("firepit"));
    add_item( ({ "firelight", "warmth", "flickering firelight", "shadows" }),
        &fire_desc("firelight"));
    add_item( ({ "fire", "flame", "flames",
                 "roaring fire" }), &fire_desc("fire"));
    add_item( ({ "wood", "firewood", "wood in firepit",
                 "firewood in firepit", "wood in pit",
                 "firewood in pit", "burning wood", "burning firewood" }),
        &fire_desc("wood"));
    add_item( ({ "ash", "ashes", "ash in firepit",
                 "ashes in firepit", "ash in pit",
                 "ashes in pit", "chimney bottom",
                 "bottom of the chimney" }),
        &fire_desc("ashes"));
    add_item( ({ "cauldron", "copper cauldron", "huge copper cauldron",
                 "huge cauldron", "large cauldron",
                 "large copper cauldron", "pot", "copper pot",
                 "huge copper pot" }),
        &fire_desc("cauldron"));
    add_item( ({ "broth", "brown broth", "inside cauldron" }),
        &fire_desc("broth"));
    add_item( ({ "table", "tables", "large table", "large tables",
                 "one of the tables", "one of the dining tables",
                 "various tables", "various dining tables",
                 "large dining table", "large dining tables",
                 "dining table", "dining tables", "place to sit",
                 "place to sit down" }),
        look_tables);
    add_item( ({ "chair", "chairs", "dining chair", "dining chairs" }),
        "Chairs are crowded around the dining tables, tempting the"
      + " weary traveller to <sit> and <order> something from the menu.\n");
    add_item( ({ "pricelist", "list", "prices", "menu", "bill",
                 "bill of fare", "sign", "large menu" }), price_long());

    add_cmd_item( ({ "pricelist", "list", "prices", "menu", "bill",
                     "bill of fare", "sign", "large menu" }),
                  ({ "read" }), price_long());

    add_name("_new_merc_board_room"); /* This id is checked by the
                                       * quest item for the Merc Spy
                                       * quest.
                                       */

    /* This command is a secret command triggered by the journal itself
     * using command()
     */
    add_delay_cmd_item( ({ "_board" }),
                        "_trigger_copy",
                        "copying down what is written on the bulletin"
                      + " board",
                        15,
                        "You begin carefully copying down the latest"
                      + " note from the bulletin board into the red"
                      + " leatherbound journal.\n",
                        "@@finish_copying@@");

    config_default_trade();
    set_money_give_max(2000);
    set_money_give_out( ({ 2000, 700, 50, 4 }) );
    set_money_give_reduce( ({ 1, 1, 1, 1 }) ); 

    set_fire_state(FIRE_BURNING);

    add_indoor_view();
    add_indoor_lodge_view();

    add_prop(ROOM_I_INSIDE, 1);

    add_exit("kitchen", "east", check_exit, 0);
    add_exit("entry_hall", "south");

    set_no_exit_msg( ({ "northeast", "southeast", "southwest",
                        "northwest" }),
        "You poke around the corner of the room, but find nothing.\n");
    set_no_exit_msg( ({ "north" }),
        "Thats a chimney, not a door.\n");
    set_no_exit_msg( ({ "west" }),
        "You walk over and peer out the windows in the west wall, but"
      + " find no way to proceed.\n");

    setuid();
    seteuid(getuid());

    if (!(Board = make_board()))
    {
        add_my_desc("ERROR: Board not created. Please mail Gorboth.\n");
    }

    reset_room();
} /* create_merc_room */


/*
 * Function name:        check_exit
 * Description  :        If the waitress is present, she won't let people
 *                       into the kitchen
 * Returns      :        0 - allow passage, 1 - prevent passage
 */
public int
check_exit()
{
    if (!present("_merc_guild_waiter"))
    {
        return 0;
    }

    if (this_player()->id("_merc_guild_cook"))
    {
        Innkeeper_npc->command("glare cook");
        Innkeeper_npc->command("say You overslept! Typical ...");
        return 0;
    }

    if (this_player() == Innkeeper_npc)
    {
        return 0;
    }

    if (!CAN_SEE(Innkeeper_npc, this_player()))
    {
        write("You manage to slip past the waitress ...\n");
        return 0;
    }

    Innkeeper_npc->command("glare " + this_player()->query_real_name());
    Innkeeper_npc->command("emote shrieks: Keep out of the kitchen!!");

    if (this_player()->query_wiz_level())
    {
        Innkeeper_npc->command("emote mutters: Oh ... a wizard. Very well,"
          + " but don't slow down the cook! We're already backed up!");
        return 0;
    }

    return 1;
} /* check_exit */


/*
 * Function name:       summon_innkeeper
 * Description  :       restore npc as needed
 * Arguments    :       int silent - true if we don't want the waitress
 *                                   to act as if she's just showing up.
 */
public void
summon_innkeeper(int silent = 0)
{
    object    npc;

    if (!present("_merc_guild_waiter"))
    {
        npc = clone_object(NPC_DIR + "waiter");
        npc->move(this_object());
        npc->command("emote arrives.");
        npc->command("shout Alright, who's next?");

        set_innkeeper_npc(npc);
        set_innkeeper_name("pearl");
    }
    else
    {
        if (silent)
        {
            Innkeeper_npc->command("cough");
        }
        else
        {
            Innkeeper_npc->command("emote roars: I'm right here, you"
              + " nitwit! If you want to <order> something, just say"
              + " so!");
        }
    }
} /* summon_innkeeper */


/*
 * Function name:       reset_room
 * Description  :       clone sign, etcetera
 * Arguments    :       float summon delay - the delay we want for the
 *                                           arrival of the waitress.
 *                                           Default = 2.0
 */
public void
reset_room()
{
    set_alarm(0.0, 0.0, &summon_innkeeper(1));

    /* reset wood to default amount */
    set_wood(-1);

    /* if fire's gone out and Pearl are around to rekindle it,
     * start it up again.
     */
    if (query_fire_state() != FIRE_BURNING &&
        present("_merc_guild_waiter", this_object()))
    {
        Innkeeper_npc->command("emote tosses some fresh logs on"
          + " the fire in the chimney and sets it freshly ablaze.");
        set_fire_state(FIRE_BURNING);
    }
} /* reset_room */


/*
 * Function name: init
 * Description:   set up the commands
 */
void
init()
{
    ::init();

    init_fire();
    init_room_chairs();

    add_action(do_buy, "buy",   0);
    add_action(do_buy, "order", 0);
    add_action(ring_bell, "hit");
    add_action(ring_bell, "ring");
    add_action(ring_bell, "smack");
    add_action(free_lunch, "feast");
    add_action(drink_broth, "drink");
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
    + "   DRINKS:                         PRICES:\n\n"
    + "   Barley Ale          ...  " + money_text(MY_PRICES[0]) + "\n"
    + "   Strong Mead         ...  " + money_text(MY_PRICES[1]) + "\n"
    + "   Sparkle's Finest    ...  " + money_text(MY_PRICES[2]) + "\n\n"
    + "   FOOD:                           PRICES:\n\n"
    + "   Dried Meat Jerky    ...  " + money_text(MY_PRICES[3]) + "\n"
    + "   Roasted Quail       ...  " + money_text(MY_PRICES[4]) + "\n"
    + "   16-oz Steak         ...  " + money_text(MY_PRICES[5]) + "\n\n"
    + "You may purchase items using the <buy> command.\n"
    + "If the cook's wife is not around, you can <ring bell> for"
    + " service.\n"
    + "Once a day, Mercenaries may <feast> here for a free meal.\n\n");
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
            + " sets the "+ob->query_short()+" down in front of you.\n");
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

    switch (lower_case(item_name))
    {
        case "ale":
        case "ales":
        case "beer":
        case "beers":
        case "barley":
        case "barleys":
        case "barley ale":
        case "barley ales":
        case "barley beer":
        case "barley beers":
        case "pint":
        case "pints":
        case "pint of ale":
        case "pints of ale":
        case "beer":
        case "beers":
        case "pint of beer":
        case "pints of beer":
        case "pint of barley ale":
        case "pints of barley ale":
                file = OBJ_DIR + "ale";
                ware = "barley ale";
                price = MY_PRICES[0];
            break;
        case "mead":
        case "meads":
        case "strong mead":
        case "strong meads":
        case "glass":
        case "glasses":
        case "glass of mead":
        case "glasses of mead":
        case "glass of strong mead":
        case "glasses of strong mead":
                file = OBJ_DIR + "mead";
                ware = "strong mead";
                price = MY_PRICES[1];
            break;
        case "finest":
        case "sparkle":
        case "sparkles":
        case "sparkle's":
        case "sparkle finest":
        case "sparkles finest":
        case "sparkle's finest":
        case "shot":
        case "shot of finest":
        case "shot of sparkles finest":
        case "shot of sparkle's finest":
        case "shot of sparkle finest":
        case "shots of finest":
        case "shots of sparkles finest":
        case "shots of sparkle's finest":
        case "shots of sparkle finest":
                file = OBJ_DIR + "finest";
                ware = "Sparkle's Finest";
                price = MY_PRICES[2];
            break;
        case "jerky":
        case "jerkys":
        case "meat jerky":
        case "meat jerkys":
        case "dried jerky":
        case "dried jerkys":
        case "dried meat jerky":
        case "dried meat jerkys":
        case "cord":
        case "cords":
        case "cord of jerky":
        case "cords of jerky":
        case "cord of meat jerky":
        case "cords of meat jerky":
        case "cords of dried jerky":
        case "cord of dried jerky":
        case "cord of dried meat jerky":
        case "cords of dried meat jerky":
                file = OBJ_DIR + "jerky";
                ware = "dried meat jerky";
                price = MY_PRICES[3];
            break;
        case "quail":
        case "quails":
        case "roasted quail":
        case "roasted quails":
        case "plate":
        case "plates":
        case "plate of roasted quail":
        case "plates of roasted quail":
        case "plate of quail":
        case "plates of quails":
                file = OBJ_DIR + "quail";
                ware = "roasted quail";
                price = MY_PRICES[4];
            break;
        case "steak":
        case "steaks":
        case "16 oz steak":
        case "16 oz steaks":
        case "16 oz. steak":
        case "16 oz. steaks":
        case "16-oz steak":
        case "16-oz steaks":
        case "16-oz. steak":
        case "16-oz. steaks":
                file = OBJ_DIR + "steak";
                ware = "16-oz steak";
                price = MY_PRICES[5];
            break;
        default:
            notify_fail(
              "You'd better check the menu again. That isn't on it.\n");
            return 0;
    }

    TELL_G("cook_asleep = " + cook_asleep());

    if (cook_asleep())
    {
        notify_fail(cook_sleeping_txt());
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

    if (this_object()->query_prop(OBJ_I_LIGHT) < 1)
    {
        if (present("_merc_guild_waiter"))
        {
            if (CAN_SEE_IN_ROOM(tp))
            {
                write(CAP_INNKEEPER(tp)
                  + " says: I can't see a blasted thing!\n");
            }
            else
            {
                write("Someone says: I can't see a blasted thing!\n");
            }
        }
        else
        {
            if (CAN_SEE_IN_ROOM(tp))
            {
                write("There is no one here to serve you.\n");
            }
            else
            {
                /* strictly speaking, we should let them figure out that
                 * there's no response by making no response, but someone's
                 * sure to report that as a bug.
                 */
                 write("You hear no response to your request for service.\n");
            }
        }
        return 1;
    }

    if (!present("_merc_guild_waiter"))
    {
        write("There is no one here to serve you. You notice a large"
          + " brass bell mounted on the wall, however. You can probably"
          + " <ring bell> to try and get some service.\n");
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
    write(CAP_INNKEEPER(tp)+" snarls: Look, if you had any "
      + pay_type + " coins, we might get somewhere!\n");
    Innkeeper_npc->command("emote mutters something about wasted time.");
} /* hook_not_got_coin_type */


public void
hook_not_enough_coin_type(string pay_type, string ware, object tp)
{
    write(CAP_INNKEEPER(tp)+" says: Looks like you are a few "
      + pay_type + " coins short. Get a few more if"
      + " you want to buy " + ware + "!\n");
} /* hook_not_enough_coin_type */


public void
hook_not_enough_money(object tp, string ware)
{
    write(CAP_INNKEEPER(tp)+" snarls: Hey, what are you playing at? You"
      + " don't have the money for it!\n");
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
        write(CAP_INNKEEPER(tp)+" nods and hands you "+coin_get_text+
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

    write("You grab the cord and give the bell a good ring. CLANGGG!\n");
    tell_room(this_object(), QCTNAME(this_player())
      + " rings a bell that is mounted on  the wall. CLANGGG!\n",
         this_player());

    summon_innkeeper();

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
    string  time_txt = TIME2FORMAT(time(), "d mmm yyyy"),
            refusal;
    object  drinks,
            grub;
    int     how_full = this_player()->query_stuffed(),
            how_fat = this_player()->eat_max(),
            feast_size = how_fat - how_full,
            i;

    if (strlen(arg))
    {
        notify_fail("No need to be verbose. Just <feast> and you'll"
          + " get your fill.\n");
        return 0;
    }

    if (!IS_MERC(this_player()))
    {
        write("Only Mercenaries are waited upon here!\n");
        return 1;
    }

    refusal = "You have already feasted today! Come back tomorrow!\n";

    if (MERC_MASTER->get_info(this_player(), "Last_Feast") ==
        time_txt)
    {
        write(refusal);
        return 1;
    }

    if (!present("_merc_guild_waiter"))
    {
        write("There is no one here to serve you. Perhaps you should"
          + " first ring the bell.\n");
        return 1;
    }

    if (cook_asleep())
    {
        write(cook_sleeping_txt());
        return 1;
    }

    MERC_MASTER->set_info(this_player(), "Last_Feast", time_txt);

    Innkeeper_npc->command("shout Harold, we've got a hungry one out here!");
    Innkeeper_npc->command("east");
    Innkeeper_npc->command("emote grabs a ton of food and marches back out"
      + " into the Feasting Hall.");
    Innkeeper_npc->command("west");

    write("A full daily portion of food is set before you, and you eat"
      + " your fill!\n");
    tell_room(this_object(), "A full daily portion of food is set before "
      + QCTNAME(this_player()) + ", who proceeds to eat "
      + this_player()->query_possessive() + " fill.\n", this_player());

    /* Fill 'em up!
     * There appears to be a maximum limit on eat_food() set to approximately
     * this_player()->eat_max() / 5. So ... we'll do this in 5 chunks of
     * just that portion, with the last a bit smaller.
     */
    for (i = 0; i < 5; i++)
    {
        if (i > 4)
        {
            this_player()->eat_food(feast_size - 5);
        }
        else
        {
            this_player()->eat_food(how_fat / 5);
        }
    }

    this_player()->command("$burp");

    return 1;
} /* free_lunch */


/*
 * Function name:        make_board
 * Description  :        set up the bulletin board
 * Returns      :        the board object - success,
 *                       0                - failure, board not created.
 */
public object
make_board()
{
    object  bboard;

    bboard = clone_object(OBJ_DIR + "merc_board");

    if (bboard)
    {
        bboard->move(this_object());

        return bboard;
    }

    return 0;
} /* make_board */


/*
 * Function name:        copy_merc_note_to_journal
 * Description  :        Allow players on the Mercenary Spy quest to
 *                       copy the most recent note from the board to
 *                       their journal.
 * Returns      :        mixed - the result of query_latest_note called
 *                               in the board object
 */
public mixed
copy_merc_note_to_journal()
{
    return Board->query_latest_note();
} /* copy_merc_note_to_journal */


/*
 * Function name:        finish_copying
 * Description  :        The player has finished copying from the
 *                       bulletin board. Assuming the board has not been
 *                       emptied of notes, we declare it a success.
 * Returns      :        string - the message to send to the player.
 */
public string
finish_copying()
{
    string  note = read_file("/d/Sparkle/boards/new_merc_board/"
                 + Board->query_latest_note());
    object  journal;

    if (!note)
    {
        return "Someone removed the note while you were copying it,"
          + " ruining your efforts!\n";
    }

    journal = present("_merc_spy_journal", this_player());

    if (!journal)
    {
        return "You seem to have lost track of your journal! What is"
          + " going on here?!?\n";
    }

    journal->set_Note_Txt(note);

    write_file(LOG_DIR + "merc_spy",
        TIME2FORMAT(time(), "mm/dd/yyyy") + " ("
          + ctime(time())[11..18] + ") "
          + capitalize(this_player()->query_real_name()) 
          + " successfully copies a note to the journal.\n");

    return "You finish copying down the most recent note from the"
      + " bulletin board. That wasn't so hard, was it?\n";
} /* finish_copying */


/*
 * Function name:        fire_desc
 * Description  :        VBFC for room and items that vary w/ fire
 * Arguments    :        string arg -- what we're looking at
 * Returns      :        string description
 */
public string
fire_desc(string arg)
{
    int fire_state = query_fire_state();

    switch (arg)
    {
        case "firepit":
            switch (fire_state)
            {
                case FIRE_BURNING:
                    return "The chimney is enormous, taking up a large"
                      + " portion of the northern wall. Within it,"
                      + " flames lick up the sides of a cauldron"
                      + " which hangs above a brightly burning fire.\n";
                    break;
                case FIRE_UNLIT_WOOD:
                    return "The chimney is enormous, taking up a large"
                      + " portion of the northern all. A cauldron"
                      + " within the chimney hangs above a stack of"
                      + " wood.\n";
                    break;
                default:        /* FIRE_ASHES */
                    return "The chimney is enormous, taking up a large"
                      + " portion of the northern wall. A cauldron"
                      + " within the chimney hangs above a pile of"
                      + " ashes.\n";
                    break;
            }
            break;
        case "fire":
            if (fire_state == FIRE_BURNING)
            {
                return "A fire burns brightly beneath a cauldron"
                  + " in the chimney.\n";
            }
            return "There doesn't seem to be any fire burning.\n";
            break;
        case "wood":
            switch (fire_state)
            {
                case FIRE_BURNING:
                    return "The wood in the chimney burns"
                             + " brightly beneath a cauldron, emitting"
                             + " a pleasant warmth.\n";
                    break;
                case FIRE_UNLIT_WOOD:
                    return "Unlit wood is piled in the"
                             + " chimney beneath a cauldron.\n";
                    break;
                default:    /* FIRE_ASHES */
                    return "You find no firewood, only ashes.\n";
                    break;
            }
            break;
        case "firelight":
            switch (fire_state)
            {
                case FIRE_BURNING:
                    return "The fire casts light and shadows which dance"
                      + " throughout the room with the movement of the"
                      + " flames.\n";
                    break;
                default:    /* FIRE_ASHES */
                    return "There is no fire. Thus, you see none.\n";
                    break;
            }
            break;
        case "ashes":
            switch (fire_state)
            {
                case FIRE_BURNING:
                    return "Beneath the brightly burning fire,"
                             + " ashes cover the bottom of the"
                             + " chimney.\n";
                    break;
                case FIRE_UNLIT_WOOD:
                    return "Beneath the wood, ashes cover the"
                             + " bottom of the firepit.\n";
                    break;
                default:    /* FIRE_ASHES */
                    return "Ashes cover the bottom of the"
                             + " chimney.\n";
                    break;
            }
            break;
        case "cauldron":
            switch (fire_state)
            {
                case FIRE_BURNING:
                    return "A huge copper cauldron hangs above the"
                     + " flames of the fire, a broth boiling vigorously"
                     + " within its belly.\n";
                    break;
                case FIRE_UNLIT_WOOD:
                    return "A huge copper cauldron hanges above wood"
                     + " that has been stacked in the chimney. A broth"
                     + " within has grown cold.\n";
                    break;
                default:    /* FIRE_ASHES */
                    return "A huge copper cauldron hangs above ashes"
                     + " which are spread out over the bottom of the"
                     + " chimney. Within it, a broth appears to be"
                     + " quickly cooling.\n";
                    break;
            }
        case "broth":
            switch (fire_state)
            {
                case FIRE_BURNING:
                    return "The broth is slightly brown in color. It is"
                      + " boiling at a fevered pitch.\n";
                    break;
                case FIRE_UNLIT_WOOD:
                    return "The broth sits cold inside the cauldron,"
                      + " slightly brown in color.\n";
                    break;
                default:    /* FIRE_ASHES */
                    return "The broth swirls slowly in the cauldron,"
                      + " quickly cooling over the ashes of the"
                      + " extinguished fire.\n";
                    break;
            }
            break;
        default:    /* room long description */
            if (fire_state == FIRE_BURNING)
            {
                return "This large feasting hall is the heart of"
                  + " the Mercenary guild. A fire blazes in the"
                  + " enormous chimney set into the northern wall,"
                  + " casting warmth and flickering firelight along"
                  + " the surfaces of the large tables which crowd"
                  + " the floor. A doorway to the east leads into"
                  + " the kitchen, and south the room opens onto"
                  + " the entry hall. A large menu has been painted"
                  + " on a sign hung beside the kitchen.\n\n";
            }
            return "This large feasting hall is the heart of the"
              + " Mercenary guild. Someone has let the fire go"
              + " out (a shame!) in the enormous chimney set into the"
              + " northern wall opposite the large tables which"
              + " crowd the floor. A doorway to the east leads into"
              + " the kitchen, and south the room opens onto the"
              + " entry hall. A large menu has been painted on a"
              + " sign hung beside the kitchen.\n\n";
            break;
    }
    return "";  /* "cannot" happen */
} /* fire_desc */


/*
 * Function name:       do_sit
 * Description  :       mask parent to block "sit" and "sit down"
 * Arguments    :       string arg -- whatever the player typed
 * Returns      :       1 on success, 0 on failure
 */
public int
do_sit(string arg)
{
    if (!arg ||
        arg == "down")
    {
        notify_fail("Sit where?\n");
        return 0;
    }
    return ::do_sit(arg);
} /* do_sit */


/*
 * Function name:       do_sit_msgs
 * Description  :       mask parent so the block msgs look right
 * Arguments    :       object pl -- the person who's sitting
 *                      string prep -- the preposition
 *                      string name -- the name of the chair
 */
public void
do_sit_msgs(object pl, string prep, string name)
{
    write("You find a place at one of the tables, and take a seat.\n");
    say(QCTNAME(pl) + " finds a place at one of the tables and takes"
      + " a seat.\n");
} /* do_sit_msgs */


/*
 * Function name:       do_stand_msgs
 * Description  :       mask parent so the block msgs look right
 * Arguments    :       object pl -- the person who's standing
 *                      string name -- the name of the chair
 */
public void
do_stand_msgs(object pl, string name)
{
    write("You stand up from the table at which you were seated.\n");
    say(QCTNAME(pl) + " stands up from one of the tables.\n");
} /* do_stand_msgs */


/*
 * Function name:        look_tables
 * Description  :        VBFC for block; include occupants
 * Returns      :        string -- the desc
 */
public string
look_tables()
{
    return "Large dining tables are arranged around the room,"
      + " offering a place to <sit> for anyone who is hungry enough to"
      + " <order> some food.\n"
         + sitting_on_chair(BLOCK_NAME, this_player(), 0, 0);
} /* look_block */


/*
 * Function name:       leave_inv
 * Description  :       mask parent to be sure that departing players
 *                      are removed from table occupants
 * Arguments    :       object ob -- the departing object
 *                      object dest -- its destination
 *
 * If they leave via a normal exit, they've already been made to stand.
 * However, if they leave by quitting, going netdead, teleporting, etc
 * and we don't call leave_inv_room_chairs(), then they'll still look
 * as if they're here.
 */
public void
leave_inv(object ob, object dest)
{
    ::leave_inv(ob, dest);
    leave_inv_room_chairs(ob, dest);
} /* leave_inv */


/*
 * Function name:       show_subloc
 * Description  :       generate "foo is sitting ..." msg
 *                      for living's desc.
 * Arguments    :       string subloc -- the subloc
 *                      object pl -- the player
 *                      object for_obj -- who's doing the looking
 * Returns      :       string -- the "is sitting" msg
 *
 * This is a mask from the room_chairs.c code, because I don't want to
 * have it be someone sitting at "the" anything ... I want my own
 * verbage here.
 */
public string
show_subloc(string subloc, object pl, object for_obj)
{
    string      name;
    mixed       *chairptr;

    if (this_player()->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
    {
        return "";
    }

    if (subloc != SITTING_S_SUBLOC)
    {
        return pl->show_subloc(subloc, pl, for_obj);
    }

    if (strlen(name = pl->query_prop(LIVE_S_SITTING)) &&
        pointerp(chairptr = query_room_chairs()[name]))
    {
        if (for_obj != pl)
        {
            return capitalize(pl->query_pronoun()) + " is sitting " +
                chairptr[3] + " a " + name + ".\n";
        }
        return "You are sitting " + chairptr[3] + " one of the"
          + " tables.\n";
    }
    return "";
} /* show_subloc */


/*
 * Function name:       sitting_on_chair
 * Description  :       describe who's on the chair.
 * Arguments    :       string name -- the chair name
 *                      object for_obj -- who's doing the looking
 *                      int namesonly -- if true, returns only
 *                              the names of occupants, suitably
 *                              formatted, + " is" or " are"
 *                      int definite -- if true, we use a
 *                                     definite article when
 *                                     we modify the ledge name
 * Returns      :       string -- the desc of the occupants
 *
 * N.B. if namesonly is false, the returned string will have an ending
 * newline. if namesonly is true, it will not. it follows that if you
 * want to embed info about who's sitting on what in the middle of 
 * other text, you set namesonly to true and append your own location
 * string (e.g., " at the desk.").
 *
 * Ugh. I had to mask this one from the parent, too. I just didn't like
 * having the prepositions locked into "a" or "the". I needed "one"
 * or "various." (Gorboth)
 */
public string
sitting_on_chair(string name, object for_obj, int namesonly, int definite = 1)
{
    mixed       *chairptr;
    object      *occupants,
                *others;
    int         i,
                s;
    string      *names,
                 desc,
                 my_art,
                 some = " one of the ";

    my_art = (definite ? " the " : " a ");

    if (!strlen(name) ||
        !pointerp(chairptr = query_room_chairs()[name]) ||
        !(s = sizeof(occupants = chairptr[2])))
    {
        return "";
    }

    if (!objectp(for_obj))
    {
        for_obj = this_player();
    }

    if (s == 1)
    {
        if (occupants[0] != for_obj) 
        {
            desc =  occupants[0]->query_Art_name(for_obj) + " is";
        }
        else
        {
            desc = "You are";
        }
    }
    else
    {
        some = " various ";
        if ((i = member_array(for_obj, occupants)) < 0)
        {
            names = occupants->query_art_name(for_obj);
        }
        else
        {
            others = exclude_array(occupants, i, i);
            names = others->query_art_name(for_obj)  +  ({ "you" });
        }
        desc =  capitalize(COMPOSITE_WORDS(names)) + " are";
    }

    if (!namesonly)
        desc += " sitting " + chairptr[3] + some + name + ".\n";
    return desc;
} /* sitting_on_chair */


/*
 * Function name:        drink_broth
 * Description  :        allow players to try to drink the broth
 *                       from the cauldron. It is actually a powerful
 *                       healing potion that the waitress (a powerful
 *                       witch!) has brewed up. If she's around, the
 *                       players is prevented from drinking it. Also,
 *                       if the fire is burning, it is too hot to
 *                       drink. The player will need a ladel to drink
 *                       it.
 * Arguments    :        string arg - whatever the player typed after
 *                                    the verb
 * Returns      :        int 1 -- success, 0 -- failure
 */
public int
drink_broth(string arg)
{
    object  ladel;

    if (!strlen(arg))
    {
        notify_fail("Drink what?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[some] [of] [the] 'broth' [from] [the] [cauldron]"))
    {
        notify_fail("You aren't able to drink that.\n");
        return 0;
    }

    if (query_fire_state() == FIRE_BURNING)
    {
        write("Drink from a fire-lit cauldron"
          + " at full boil? You'd scald your throat beyond"
          + " repair!\n");
        return 1;
    }

    if (!objectp(ladel = present("ladel", this_player())))
    {
        write("What, just dunk your head in and start gulping? No,"
          + " you'll need a ladel first.\n");
        return 1;
    }

    if (ladel->query_wielded() != this_player())
    {
        write("Perhaps you should wield the ladel?\n");
        return 1;
    }

    if (present("_merc_guild_waiter"))
    {
        write("You tiptoe over to the cauldron, ladel in hand.\n");
        tell_room(this_object(), QCTNAME(this_player()) + " tiptoes over"
          + " to the cauldron with a ladel at the ready.\n", this_player());
        Innkeeper_npc->command("emote shrieks: GET AWAY FROM THERE OR"
          + " I'LL STEW YOU RIGHT ALONG WITH THE BROTH!");
        this_player()->command("$sulk");
        return 1;
    }

    write("You scoop some broth out of the cauldron with the ladel and"
      + " drink it down. Your insides give a sudden leap!\nYou feel"
      + " completely healed!\n");
    tell_room(this_object(), QCTNAME(this_player()) + " scoops some"
      + " broth out of the cauldron with a ladel and drinks it down. A"
      + " look of astonishment breaks upon "
      + this_player()->query_possessive() + " face, and "
      + this_player()->query_pronoun() + " smiles broadly.\n",
        this_player());

    /* Heal them all the way up! I figure this really doesn't break any
     * balance situations. It can only happen here in the guildhall,
     * and only if you manage to defeat the witch (VERY TOUGH). I am
     * guessing that the worst that could happen would be for a non-
     * guild member to sneak in here, steal the ladel, defeat the witch
     * and then be attacked by Mercs. The intruder could sit here all
     * day healing up, making them essentially unbeatable. But you
     * know what? I'm fine with that! I think it would be hilareous!
     * More power to 'em!   - Gorboth
     */
    this_player()->heal_hp(this_player()->query_max_hp());
    return 1;
} /* drink_broth */


/*
 * Function name:        cook_sleeping_txt
 * Descriptions :        You can't buy food when the cook is sleeping.
 *                       This text is returned to tell players what
 *                       is going on.
 * Returns      :        the text
 */
public string
cook_sleeping_txt()
{
    return "Looks like it's after hours, and the cook is asleep. You'll"
      + " have to wait until morning.\n";
} /* cook_sleeping_txt */


/*
 * Function name:        cook_asleep
 * Description  :        Check to see if the cook has gone to bed
 * Returns      :        1 - the cook is asleep
 *                       0 - the cook is awake
 */
public int
cook_asleep()
{
    object     kitchen = safely_load_master_file(ROOM_DIR + "kitchen");

    if (present("_merc_guild_cook", kitchen))
    {
        return 0;
    }

    TELL_G("looks like the cook is out!");

    /* If it isn't his sleeping period, we assume that he's outside
     * doing one of his very brief errands. In this case, the kitchen
     * is still running.
     */
    switch (s_get_time_hour_of_day())
    {
        case 23:
        case 0..6:
            return 1;
            break;
        default:
            return 0;
            break;
    }

    return 1;
} /* cook_asleep */

