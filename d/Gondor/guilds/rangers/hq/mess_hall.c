/*
 *  /d/Gondor/guilds/rangers/hq/mess_hall.c
 *  Central Headquarters Mess Hall
 * 
 *  Modified directly from:
 *
 *  The Gondorian Rangers Inn. 
 *  by Elessar
 *
 *  Modification log:
 *  950309 Improved the parser. /Arren
 *  December 1995: Inherit /d/Gondor/common/lib/inn.c. Olorin
 *  January 1997:  Added chess game by Fysix, Olorin
 *  July 2001: Modified to fit CH theme, added fire and benches, Alto
 *             (fire and benches from Gnadnar)
 *  May 3, 2004: Gwyneth, neatened up
 *
 */
inherit "/d/Gondor/std/room.c";
inherit "/d/Gondor/common/lib/inn.c";
inherit "/d/Gondor/common/lib/friend_or_foe.c";
inherit "/d/Gondor/open/fireplace/fireplace";

#include "../rangers.h"

inherit RANGERS_HQ_DIR + "ch_funcs.c";
inherit "/d/Gondor/open/room_chairs/room_chairs";

#include <composite.h>
#include <macros.h>
#include <money.h>
#include <std.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/open/fireplace/fireplace.h"
#include "/d/Gondor/open/room_chairs/room_chairs.h"

#define STAND_DIR      "/d/Gondor/std/"
#define MY_PRICES      ({ 3, 12, 24, 48, 216, 12, 36, 72, 144, 576 })
#define RESET_WOOD     10
#define BENCH_NAME     "wooden bench"
#define BENCH_CAPACITY 12

public string          fire_desc(string arg);
public void            leave_inv(object ob, object to);

public void
create_gondor()
{
    set_short("the mess hall of Central Headquarters");
    set_long(fire_desc);

    set_parse_pattern("[the] [small] 'fireplace'");
    add_chair(BENCH_NAME,
        "[down] [on] [one] [of] [the] [wooden] 'benches' / 'bench'",
        BENCH_CAPACITY, "on");

    hideout_add_items();

    add_item(({ "small fireplace", "stone fireplace",
        "small stone fireplace", "fireplace" }), &fire_desc("fireplace"));
    add_item(({ "flame", "flames", "fire" }), &fire_desc("fire"));

    /* add "... in fireplace" items so players may examine the wood/ashes 
     * in the fireplace even if they have wood/ashes in their inventory.
     */

    add_item(({ "wood", "firewood", "wood in fireplace",
        "firewood in fireplace" }), &fire_desc("wood"));
    add_item(({ "ash", "ashes", "ash in fireplace", 
        "ashes in fireplace" }), &fire_desc("ashes"));
    add_item(({ "smokestack", "stack" }), "It's a plain smokestack. It "
        + "starts somewhat above the hearth and " 
        + "disappears into the ceiling.\n");
    add_item(({ "wooden bench", "wooden benches", "bench", "benches",
        "sturdy bench", "sturdy benches", "oak bench", "oak benches",
        "sturdy oak bench", "sturdy oak benches", "sturdy wooden bench", 
        "sturdy wooden benches"}),
        "The sturdy oak benches are bolted against all walls but for "
        + "the one with the door. They are not too comfortable but can "
        + "hold quite a few people.\n");
    add_item(({ "rug", "remains of rug" }),
       "The rug was once beautiful and red, but now it is grey and "
        + "full of holes.\n");
    add_item(({"hole", "holes"}), "Looking through the holes, you can see "
        + "the old wooden floor beneath the rug.\n");
    add_item(({ "table", "tables", "chair", "chairs"}),
        "Many of the tables have open spaces on their benches. Why don't you "
        + "have a seat and relax over a meal and a cup?\n");
    add_item(({ "panels", "wooden panels" }),
        "You notice nothing special about the wooden panels.\n");
    add_item("counter", "Above the wooden counter is a lamp and a shelf. "
        + "On the shelf are "
        + "several brands of liquor. Behind the counter is the barkeeper of "
        + "the Seven Stars Inn, the inn of the Gondorian Rangers.\n");
    add_item(({ "innkeeper", "bartender", "barkeeper", "beleg" }), 
        "The barkeeper, Beleg, is a human Ranger with a jovial face. He seldom "
        + "takes a break, but runs between the kitchen and the bar serving his "
        + "customers, trying to keep the glasses as shiny as possible, and the "
        + "meals hot and delicious. Beleg looks at you, waiting for you to "
        + "order something.\n");

    add_item(({ "pricelist", "list", "prices", "menu" }), price_long());
    add_cmd_item(({ "pricelist", "list", "prices", "menu" }), "read",
        price_long());

    config_default_trade();
    set_money_give_max(2000);
    set_money_give_out(({ 2000, 700, 50, 4 }));
    set_money_give_reduce(({ 1, 1, 1, 1})); 
    set_innkeeper_name("the barkeeper");

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(RANGERS_HQ_DIR + "dcorridor2", "north", check_sitting, 1);

    if (file_size(CHESS_GAME + ".c") > 0)
        clone_object(CHESS_GAME)->move(TO);
    else
        log_file("errors", file_name(TO) + 
            " >>>>> "+CHESS_GAME+" not found!\n");

    reset_room();
}

/* Function name: reset_room
 * Description  : replenish the fire if necessary
 */
public void
reset_room()
{
    set_wood(RESET_WOOD);
    if ( query_fire_state() != FIRE_BURNING )
    {
        /* use an imaginary ranger to light the fire ... */
        tell_room(TO, "An apprentice ranger enters.\n");
        tell_room(TO, one_of_list(({ "He", "She" })) + " puts some wood "
            + "in the fireplace.\n");
        tell_room(TO, "The apprentice ranger lights the wood in the "
            + "fireplace.\n");
        tell_room(TO, "The apprentice ranger leaves north.\n");
        set_fire_state(FIRE_BURNING);
    }
}


public void
init() 
{
    ::init();

    init_room_chairs();
    init_fire();
    init_inn();
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
    + "   Water                 ...  " + money_text(MY_PRICES[0]) + "\n"
    + "   Golden Ale            ...  " + money_text(MY_PRICES[1]) + "\n"
    + "   Beer of the Rangers   ...  " + money_text(MY_PRICES[2]) + "\n"
    + "   Wine from Ithilien    ...  " + money_text(MY_PRICES[3]) + "\n"
    + "   Whiskey from Rohan    ...  " + money_text(MY_PRICES[4]) + "\n\n"
    + "HOT MEALS:\n"
    + "   Porridge              ...  " + money_text(MY_PRICES[5]) + "\n"
    + "   Vegetable stew        ...  " + money_text(MY_PRICES[6]) + "\n"
    + "   Bacon and beans       ...  " + money_text(MY_PRICES[7]) + "\n"
    + "   Pheasant              ...  " + money_text(MY_PRICES[8]) + "\n"
    + "   Stag steak            ...  " + money_text(MY_PRICES[9]) + "\n\n"
    + "Try 'order ale for gold' if you want to specify what to pay with. "
    + "You can also specify 'order 3 ale' to get three ales. There is a "
    + "maximum of " + hook_query_max_items()
    + " items you can order at one time.") + "\n\n";
}

public int
hook_query_max_items()
{
    return 20;
}

public int
do_buy(string str)
{
    object  tp = TP;

    if (!strlen(str))
        return 0;

    if (query_prop(OBJ_I_LIGHT) < 1)
    {
        if (CAN_SEE_IN_ROOM(TP))
            write("The barkeeper says: Sorry, it's too dark in here - I "
                + "can't see!\n");
        else
            write("Someone says: Sorry, it's too dark in here - I can't "
                + "see!\n");
        return 1;
    }

    if (query_friend_or_foe(TP) < 0)
    {
        write("The barkeeper just scowls at you, pointing at the door.\n");
        return 1;
    }

    return ::do_buy(str);
}

/*
 * Function name: buy_it
 * Description:   identify the item the player tries to buy
 * Arguments:     item_name - the name
 *                number    - the amount
 *                pay_type  - coins to pay with
 *                get_type  - coins for change
 * Returns:       0/1 - failure/success
 */
public int
buy_it(string item_name, int number, string pay_type, string get_type)
{
    string  file,
            ware;
    int     price;

    switch (item_name)
    {
    case "water":
    case "waters":
        file = "drink/water";
        ware = "water";
        price = MY_PRICES[0];
        break;

    case "golden":
    case "ale":
    case "ales":
    case "golden ale":
    case "golden ales":
        file = "drink/ale";
        ware = "golden ale";
        price = MY_PRICES[1];
        break;

    case "beer":
    case "beers":
    case "prime beer":
    case "prime beers":
        file = "drink/rbeer";
        ware = "prime beer";
        price = MY_PRICES[2];
        break;

    case "wine":
    case "wines":
    case "white wine":
    case "white wines":
        file = "drink/ith_wine";
        ware = "white wine";
        price = MY_PRICES[3];
        break;

    case "whiskey":
    case "whiskeys":
    case "dry whiskey":
    case "dry whiskeys":
        file = "drink/rohan_whiskey";
        ware = "dry whiskey";
        price = MY_PRICES[4];
        break;

    case "porridge":
        file = "food/porridge";
        ware = "porridge";
        price = MY_PRICES[5];
        break;

    case "stew":
    case "stews":
    case "vegetable stew":
    case "vegetable stews":
    case "vegetable":
    case "vegetables":
        file = "food/stew";
        ware = "vegetable stew";
        price = MY_PRICES[6];
        break;

    case "beans": 
    case "bean stew":
    case "bacon":
    case "bacons":
    case "bacon and bean stew":
        file = "food/beans";
        ware = "bacon and bean stew";
        price = MY_PRICES[7];
        break;

    case "pheasant":
    case "pheasants":
    case "fried pheasant":
    case "fried pheasants":
        file = "food/pheasant";
        ware = "fried pheasant";
        price = MY_PRICES[8];
        break;

    case "stag":
    case "steak":
    case "steaks":
    case "stag steak":
    case "stag steaks":
        file = "food/steak";
        ware = "stag steak";
        price = MY_PRICES[9];
        break;

    default :
        NFN("The barkeeper says: We don't have that on the menu.");
        return 0;
    }

    if (can_afford(price, number, ware, pay_type, get_type))
        buy_item(STAND_DIR + file, number);
    return 1;
}

/*
 * Function name: fire_desc
 * Descripiton  : VBFC for room and items that vary w fire
 * Arguments    : string arg -- what we're looking at
 * Returns      : string description
 */
public string
fire_desc(string arg)
{
    int fire_state = query_fire_state();
    string tmpstr;

    switch ( arg )
    {
    case "fireplace":
        switch ( fire_state )
        {
        case FIRE_BURNING:
            return "The stone fireplace in the center of the room " +
                "is not large, but holds a cheerful fire.\n";
        case FIRE_UNLIT_WOOD:
            return "The small stone fireplace in the center of the " +
                "room holds a stack of unlit wood.\n";
        default:  /* FIRE_ASHES */
            return "The small stone fireplace in the center of the " +
                "room is empty.\n";
        }

    case "fire":
        if ( fire_state == FIRE_BURNING )
        {
            return one_of_list(({ "Flames dance in the fireplace.\n",
                                 "The fire casts a warm glow over the room.\n",
                                 "The fire is burning brightly.\n" }));
        }
        return "You find no fire.\n";

    case "wood":
        switch ( fire_state )
        {
        case FIRE_BURNING:
            return "The wood in the fireplace burns brightly, emiting "+
                "a pleasant warmth.\n";
        case FIRE_UNLIT_WOOD:
            return "Unlit wood is piled in the fireplace.\n";
        default: /* FIRE_ASHES */
            return "You find no firewood.\n";
        }

    case "ashes":
        switch ( fire_state )
        {
        case FIRE_BURNING:
            return "Beneath the brightly burning fire, "+
                "ashes cover the bottom of the fireplace.\n";
        case FIRE_UNLIT_WOOD:
            return "Beneath the wood, ashes cover the bottom of the " +
                "fireplace.\n";
        default: /* FIRE_ASHES */
            return "Ashes cover the bottom of the fireplace.\n";
        }

    default: /* room description */
        if ( fire_state == FIRE_BURNING )
            tmpstr = " A merry fire casts its glow over the room.";
        else
            tmpstr = "";

    return "You are in a large Mess Hall. This is the place the Rangers "
        + "come to forget their sorrows over a beer, and fill their "
        + "empty stomachs with a nice, hot meal. The hall is decorated with "
        + "oak panels, and you can smell the odour of beer and sweaty people "
        + "from the walls. There are several tables here with benches beside "
        + "them. On the wooden floor lies the remains of a rug, which is now "
        + "worn out, covered with dirt, pipe ashes and holes. By the west "
        + "wall is a counter, behind which the barkeeper is standing. Behind "
        + "him is a pricelist and menu." + tmpstr + "\n";
    }
    /* NOTREACHED */
}

/*
 * Function name: leave_inv
 * Description  : This masks the parent to be sure that departing players
 *                are removed from chair/sofa occupants. If they leave via
 *                a normal exit, they've already been made to stand by the
 *                exit efunc check_sitting(). However, if they leave by
 *                quitting, going netdead, teleporting, etc and we don't 
 *                call leave_inv_room_chairs(), then they'll still look as 
 *                if they're here.
 * Arguments    : object ob -- the departing object
 *                object dest -- its destination
 */
public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    leave_inv_room_chairs(ob, to);
}
