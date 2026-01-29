/*
 *  The Ithilien Rangers Food Storage, in Henneth Annuin
 *  by Elessar
 *
 *  Based on the Solace Inn by Nick, and the Ranger Inn by Elessar
 *
 *  Modification log:
 *    950309 Improved the parser. /Arren
 *    July 1997: Added water, Opus
 *    27 Aug 1998, Gnadnar: move herb jar here from training hall
 *    12 Oct 1998, Gnandar: tidy up, add some items, add real npc
 *    20 Jul 2001, Alto: change inheritance for new rangers.
 */
inherit "/d/Gondor/std/room.c";
inherit "/d/Gondor/common/lib/inn.c";
inherit "/d/Gondor/common/lib/friend_or_foe.c";
inherit "/d/Gondor/open/room_chairs/room_chairs";
#include "../rangers.h"
inherit RANGERS_ITH_DIR + "ith_funcs.c";

#include <macros.h>
#include <money.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/met_defs.h"
#include "/d/Gondor/open/room_chairs/room_chairs.h"
#include "exit.c"

#define MAX_ITEMS    10
#define MY_PRICES ({ 4, 8, 28, 18, 50, 235 })
#define PRICELIST_TEXT \
    "The menu reads:\n\n" + \
    "DRINKS:\n" + \
    "   Glass of water         ... " + MY_PRICES[0] + " coppers\n" + \
    "   Golden Ale             ... " + MY_PRICES[1] + " coppers\n" + \
    "   Wine from Ithilien     ... " + MY_PRICES[2] + " coppers\n" + \
    "   Dry whiskey from Rohan ... " + MY_PRICES[5] + " coppers\n" + \
    "\nMEALS:\n" + \
    "   Vegetable stew         ... " + MY_PRICES[3] + " coppers\n" + \
    "   Dried beef             ... " + MY_PRICES[4] + " coppers\n\n" + \
    "Due to food shortage, this is all we can offer.\n\n" + \
    "Note also that the whiskey may run out.\n\n" + \
    "Try 'order ale with gold' if you want to specify what to pay with. " + \
    "You can also specify 'order 10 ale' to get ten ales. There is a " + \
    "maximum of " + MAX_ITEMS + " items you can order at one time.\n"

#define BENCH_NAME  "low bench"

static object   Jar,
                Cook;
static int      Whiskey;

/* prototypes */
public void   create_gondor();
public void   reset_room();
public void   init();
public void   leave_inv(object ob, object dest);
public string look_bench();
public int    buy_it(string item, int num, string pay, string get_type);
public int    hook_query_max_items();


/* Function name: create_gondor
 * Description  : set up the room
 */
public void
create_gondor()
{
    set_short("the food storage chamber");
    set_long("A few light wooden tables rest against one wall of this "
        + "rough-roofed rock chamber, while others are set up on "
        + "trestles and laden with platters, bowls and dishes of clay. "
        + "A long low bench runs along the wall behind the tables, "
        + "and crates and barrels are stored against the inner wall, "
        + "with a pricelist hanging above them. To the northwest, a "
        + "dark passage winds away.\n");

    add_chair(BENCH_NAME,
        "[down] [on] / [in] [the] [long] [low] [wooden] 'bench'", 8);

    add_item( ({ "cave", "chamber" }), &long());
    add_item( ({ "light wooden tables", "wooden tables", "tabletops",
        "table tops", "table", "tables" }),
        "The wooden tables are worn smooth, as if they have seen long use. "
        + "Some, not in use, lean against the walls; others are set upon "
        + "sturdy trestles and laden with crockery. All appear "
        + "lightweight and easily moved.\n");
    add_item( ({ "trestle", "trestle" }), "The trestles are simple "
        + "folding frameworks, used to support the table tops.\n");
    add_item( ({ "crockery", "platter", "platters", "bowl", "bowls",
        "dish", "dishes" }), "The plain, sturdy dishes all are of clay. "
        + "Most are rather large, more suitable for serving groups of "
        + "people than for individual use.\n");
    add_item( ({ "long bench", "low bench", "long low bench",
        "wooden bench", "bench", }), &look_bench());
    add_item( ({ "stack", "crate", "barrel", "crates", "barrels" }),
        "Various crates and barrels are stacked along the inner "
        + "wall of the cave. The barrels appear to hold liquids; "
        + "the crates probably hold dry provender.\n");
    add_item( ({ "liquid", "liquids", "provender", "food" }),
        "The crates and barrels are closed, but the pricelist "
        + "probably gives a fair notion of their contents.\n");
    add_item("floor", "The rock floor is very clean. There's not a crumb "
        + "or a drop to be seen.\n");
    add_item("walls", "The walls are grey rock, curving gently up to the "
        + "low roof. Except for the pricelist on the inner wall, "
        + "they are bare.\n");
    add_item( ({ "west wall", }), "Several table tops rest against the "
        + "west wall of the chamber.\n");
    add_item( ({ "north wall", "wall", }), "The wall is bare grey rock, "
        + "curving gently up to the low roof.\n");
    add_item( ({ "roof", "ceiling" }), "The roof, formed of the same "
        + "rock as the walls and floor, is rough of surface and uneven "
        + "in height.\n");
    add_item( ({ "stone", "rock" }), "The rock is rough surfaced, and "
        + "dark grey in colour.\n");
    add_item( ({ "south wall", "inner wall", }), "The inner wall of the "
        + "chamber seems to be used for storage; several crates and "
        + "barrels are stacked against it.\n");
    add_item( ({ "one wall", "east wall", }), "A long bench runs along "
        + "the wall, with several wooden tables drawn up before it.\n");

    add_item( ({ "pricelist", "list", "prices", "menu" }), PRICELIST_TEXT);

    add_cmd_item( ({ "pricelist", "list", "prices", "menu" }),
        "read", PRICELIST_TEXT);
    add_cmd_item( ({ "light wooden tables", "wooden tables", "table",
        "tables" }), ({ "move", "push", "pull" }), "You give one of "
        + "the tables a gentle push, and it slides a few inches "
        + "across the floor.\n");
    add_cmd_item( ({ "long bench", "low bench", "long low bench",
        "wooden bench", "bench", }), ({ "move", "push", "pull" }),
        "You give the bench a gentle push, but it seems to be "
        + "attached to the wall in some way, for it doesn't budge.\n");

    config_default_trade();
    set_money_give_max(2000);
    set_money_give_out( ({ 2000, 700, 50, 4}) );
    set_money_give_reduce( ({ 1, 1, 1, 1 }) ); 

    add_prop(ROOM_I_INSIDE, 1);

    /* Add Ithilien add_items */
    ith_add_items();

    /* Make sure they're not sitting before they move. */
    add_exit((RANGERS_ITH_DIR + "rackchamber"), "northwest", check_sitting);

    reset_room();
}


/* Function name: reset_room
 * Description  : Replace the cook if not present at reset.
 */
public void
reset_room()
{
    FIX_EUID;

    Cook = clone_npc(Cook, (RANGERS_NPC + "ceodar"));
    set_innkeeper_npc(Cook);
    Whiskey = 30;
}

/* Function name: init
 * Description  : Set up the inn and chair commands.
 */
public void
init() 
{
    ::init();
    init_inn();
    init_room_chairs();
}


/* Function name: leave_inv
 * Description  : mask parent to be sure that departing players
 *                are removed from bench occupants
 * Arguments    : object ob -- the departing object
 *                object dest -- its destination
 */
public void
leave_inv(object ob, object dest)
{
    ::leave_inv(ob, dest);
    leave_inv_room_chairs(ob, dest);
}


/* Function name: look_bench
 * Description  : VBFC to describe bench + occupants
 * Returns      : string -- the description
 */
public string
look_bench()
{
    return "The low bench is made of plain wood, smooth but unadorned.\n"
        + sitting_on_chair(BENCH_NAME, this_player(), 0);
}

/* Function name: buy_it
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
    string file, ware;
    int price;

    switch (item_name)
    {
    case "water":
    case "glass of water":
    case "waters":
    case "glasses of water":
        file = "water";
        ware = "water";
        price = MY_PRICES[0];
        break;

    case "ale":
    case "golden ale":
    case "ales":
    case "golden ales":
        file = "ale";
        ware = "golden ale";
        price = MY_PRICES[1];
        break;

    case "wine":
    case "white wine":
    case "wines":
    case "white wines":
        file = "wine";
        ware = "white wine";
        price = MY_PRICES[2];
        break;

    case "whiskey":
    case "whiskeys":
    case "dry whiskey":
    case "dry whiskeys":
        file = "rohan_whiskey";
        ware = "dry whiskey";
        price = MY_PRICES[5];
        if (Whiskey - number < 0)
        {
            Cook->command("sigh .");
            if (Whiskey <= 0)
            Cook->command("say I am sad to say we are out of whiskey again.");
            else
            {
                Cook->command("say I'm sorry to say I only have about "
                    + "...hmm ..");
                Cook->command("say " + LANG_WNUM(Whiskey)
                    + " glasses of whiskey left.");
            }
            Cook->command("shrug");
            return 1;
        }
        break;

    case "stew":
    case "vegetable stew":
    case "vegetable":
    case "stews":
    case "vegetable stews":
    case "vegetables":
        file = "stew";
        ware = "vegetable stew";
        price = MY_PRICES[3];
        break;

    case "beef":
    case "dried beef":
    case "piece of beef":
    case "piece of dried beef":
    case "beefs":
    case "pieces of beef":
    case "pieces of dried beef":
        file = "drybeef";
        ware = "dried beef";
        price = MY_PRICES[4];
        break;

    default :
        notify_fail(Cook->query_The_name(TP) + "says: We don't have "
            + "that on the menu.\n");
        return 0;
    }

    if (can_afford(price, number, ware, pay_type, get_type))
        buy_item(RANGERS_OBJ + file, number);

    return 1;
}

/* Function name: hook_query_max_items
 * Description  : Returns the maximum number of items to buy at once.
 */
public int
hook_query_max_items()
{
    return MAX_ITEMS;
}
