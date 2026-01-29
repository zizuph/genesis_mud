/*
 *  /d/Gondor/guilds/rangers/north/mess_hall.c
 *
 *  Mess Hall of the North Hideout.
 *
 *  Modified directly from:
 *
 *  The Inn of the Restful Hearth, in the Rangers of the North Hq
 *  by Arren
 *
 *  Based on the Solace Inn by Nick, and the Ranger Inn by Elessar
 *  Modification log:
 *  950309 Improved the parser. /Arren
 *  6-Dec-1997, Gnadnar  added real fireplace
 *  15-Jul-2001, Alto    changed filename to mess_hall.c and revised
 *      to fit new ranger themes.
 *
 */
inherit "/d/Gondor/std/room.c";
inherit "/d/Gondor/common/lib/inn.c";
inherit "/d/Gondor/open/fireplace/fireplace";

#include "../rangers.h"

inherit RANGERS_NOR_DIR + "north_funcs.c";
inherit "/d/Gondor/open/room_chairs/room_chairs";

#include <composite.h>
#include <macros.h>
#include <money.h>
#include <std.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/met_defs.h"
#include "/d/Gondor/open/fireplace/fireplace.h"
#include "/d/Gondor/open/room_chairs/room_chairs.h"
#include "check_exit.c"

#define STAND_DIR      "/d/Gondor/std/"
#define MY_PRICES      ({ 3, 12, 18, 36, 72, 144, 288, 12, 36, 72, 144, 576, })
#define NUM            sizeof(MONEY_TYPES)
#define BENCH_NAME     "wooden bench"
#define BENCH_CAPACITY 12

static string  price_long();
public string  fire_desc(string arg);
public void    leave_inv(object ob, object to);

static object  gHumphrie;

public void
create_gondor() 
{
    set_short("the Mess Hall of the North Hideout");
    set_long(&fire_desc());

    north_add_items();

    set_parse_pattern("[the] [wide] [stone] 'fireplace'");
    add_item( ({ "wide fireplace", "stone fireplace", "wide stone fireplace",
        "fireplace" }), &fire_desc("fireplace"));
    add_item( ({ "flames", "flame", "fire" }), &fire_desc("fire"));
    add_item( ({ "wood", "firewood", "wood in fireplace",
        "firewood in fireplace" }), &fire_desc("wood"));
    add_item( ({ "ash", "ashes" }), &fire_desc("ash"));

    add_chair(BENCH_NAME,
        "[down] [on] [one] [of] [the] [wooden] 'benches' / 'bench'",
        BENCH_CAPACITY, "on");

    add_item(({ "wooden bench", "wooden benches", "bench", "benches",
        "sturdy bench", "sturdy benches", "oak bench", "oak benches",
        "sturdy oak bench", "sturdy oak benches", "sturdy wooden bench", 
        "sturdy wooden benches"}), "The sturdy oak benches are bolted "
        + "against the walls. They appear to be quite comfortable and "
        + "can hold quite a few people.\n");

    add_item(({ "furniture", "eating-tables", "tables", "chairs" }),
        "The furniture has seen much use, adding to the atmosphere, but is "
        + "still in good shape.\n");
    add_item(({"counter"}), "The wooden counter is shining from polish. "
        + "Above the counter there is a shelf with several brands of "
        + "liquor.\n");
    add_item(({ "liquor", "bottles" }),
        "It is with those bottles the innkeeper makes the drinks.\n");
    add_item(({ "north wall" }), "The north wall is dominated by the huge "
        + "fireplace built into it.\n");
    add_item(({ "room", "mess hall" }), &fire_desc());
    add_item(({ "door" }), "The doorway leading south is filled with thick "
        + "steam, making it difficult to see the contents of that room. The "
        + "steam has a clean, soapy scent to it.\n");
    add_item(({ "steam" }), "It fills the room to the south, making it "
        + "almost impossible to see what is inside.\n");
    add_item(({ "entrance" }), "A place where people enter this room.\n");
    add_item(({ "west wall" }), "Before the west wall is a large counter.\n");
    add_item(({ "shelf" }), "The shelf is well-stocked with the favourite "
        + "liquors of the men and women of the north kingdom.\n");
     
    add_item(({ "pricelist", "list", "prices", "menu" }), price_long());
    add_cmd_item(({ "pricelist", "list", "prices", "menu" }), 
        "read", price_long());

    config_default_trade();
    set_money_give_max(2000);
    set_money_give_out(({ 2000, 700, 50, 4 }));
    set_money_give_reduce(({ 1, 1, 1, 1 })); 

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(OBJ_I_HAS_FIRE, 1);
    add_exit(RANGERS_NOR_DIR + "w_corridor", "east");
    add_exit(RANGERS_NOR_DIR + "bathhall",   "south",);

    reset_room();
}

void
reset_room()
{
    gHumphrie = clone_npc(gHumphrie, (RANGERS_NPC + "humphrie"));

    set_wood(-1);

    if ( query_fire_state() != FIRE_BURNING && ENV(gHumphrie) == TO )
    {
        tell_room(TO, "Humphrie puts some fresh wood in the fireplace "
            + "and set it ablaze.\n");
        set_fire_state(FIRE_BURNING);
    }
}

public void
init() 
{
    ::init();
    init_fire();
    init_room_chairs();

    add_action(do_buy, "buy");
    add_action(do_buy, "order");
}

int
check_keeper()
{
    if (objectp(present("humphrie")))
        return 1;
    else 
        return 0;
}

int
no_keeper()
{
    notify_fail("There is no innkeeper here, so you can't do that!\n");
    return 1;
} 

static string
price_long() 
{
    return (
    "The pricelist reads:\n\n"+
    "DRINKS:\n"+
    "   Glass of water        ...  " + money_text(MY_PRICES[0])  + "\n"+
    "   Golden Ale            ...  " + money_text(MY_PRICES[1])  + "\n"+
    "   Beer from Bree        ...  " + money_text(MY_PRICES[2])  + "\n"+
    "   Wine from Merrydown   ...  " + money_text(MY_PRICES[3])  + "\n"+
    "   Rumtoddy              ...  " + money_text(MY_PRICES[4])  + "\n"+
    "   Whiskey from Buckland ...  " + money_text(MY_PRICES[5])  + "\n"+
    "   Dwarfblood            ...  " + money_text(MY_PRICES[6])  + "\n\n"+
    "HOT MEALS:\n"+
    "   Porridge              ...  " + money_text(MY_PRICES[7])  + "\n"+
    "   Vegetable stew        ...  " + money_text(MY_PRICES[8])  + "\n"+
    "   Bacon and beans       ...  " + money_text(MY_PRICES[9])  + "\n"+
    "   Pheasant              ...  " + money_text(MY_PRICES[10]) + "\n"+
    "   Stag steak            ...  " + money_text(MY_PRICES[11]) + "\n\n"+
    "The innkeeper gladly answers questions concerning his menu.\n\n"+
    "Try 'order ale with gold' if you want to specify what to pay with.\n"+
    "You can also specify 'order 10 ale' to get ten ales. There is a \n"+
    "maximum of 10 items you can order at one time.\n");
}

public int
do_buy(string str) 
{
    object  item, buyer = TP;
    string  file, ware, str1, pay_type, get_type;
    int     i, price, num;

    FIX_EUID

    if (!strlen(str))
        return 0;

    if (!check_keeper())
    {
        no_keeper();
        return 0;
    }

    if (sscanf(str, "%s with %s and get %s", str1, pay_type, get_type) != 3)
    {
        get_type = "";
        if (sscanf(str, "%s with %s", str1, pay_type) != 2)
        {
            pay_type = "";
            str1 = str;
        }
    }

    if (sscanf(str1, "%d %s", num, str1) != 2)
        num = 1;

    if (num > 10)
        num = 10;

    switch (str1)
    {
    case "water" :
    case "waters" :
    case "glass of water" :
    case "glasses of water" :
        file = "drink/water";
        ware = "water";
        price = MY_PRICES[0];
        break;
    case "golden" : 
    case "ale" :
    case "golden ale" :
        file = "drink/ale";
        ware = "golden ale";
        price = MY_PRICES[1];
        break;
    case "beer" :
    case "prime beer" :
        file = "drink/beer";
        ware = "prime beer";
        price = MY_PRICES[2];
        break;
    case "wine" :
    case "red wine" :
        file = "drink/wine";
        ware = "red wine";
        price = MY_PRICES[3];
        break;
    case "rum" :
    case "rumtoddy" :
    case "rum toddy" :
        file = "drink/rum";
        ware = "rumtoddy";
        price = MY_PRICES[4];
        break;
    case "whiskey" :
    case "dry whiskey" :
        file = "drink/whiskey";
        ware = "dry whiskey";
        price = MY_PRICES[5];
        break;
    case "dwarfblood" :
        file = "drink/dwarfblood";
        ware = "dwarfblood";
        price = MY_PRICES[6];
        break;
    case "porridge" :
        file = "food/porridge";
        ware = "porridge";
        price = MY_PRICES[7];
        break;
    case "stew" :
    case "vegetable stew" :
    case "vegetable" :
        file = "food/stew";
        ware = "vegetable stew";
        price = MY_PRICES[8];
        break;
    case "beans" : 
    case "bacon" :
    case "bacon and beans" :
        file = "food/beans";
        ware = "bacon and beans";
        price = MY_PRICES[9];
        break;
    case "pheasant" :
    case "fried pheasant" :
        file = "food/pheasant";
        ware = "fried pheasant";
        price = MY_PRICES[10];
        break;
    case "stag" :
    case "steak" :
    case "stag steak" :
        file = "food/steak";
        ware = "stag steak";
        price = MY_PRICES[11];
        break;
    default :
        notify_fail("The innkeeper says: We don't have that on the menu.\n");
        return 0;
    }

    if (!can_afford(price, num, ware, pay_type, get_type))
        return 0;

    tell_room(TO, "The innkeeper leaves into the kitchen, and returns with "
        + ware + ".\n");

    for (i = 0; i < num; i++)
    {
        item = clone_object(STAND_DIR + file);
        if(item->move(buyer))
        {
            write("You cannot carry that much!\n");
            item->move(TO);
        }
    }
    return 1;
}

int
check_time(string str)
{
    if (objectp(present("humphrie", TO)))
    {
        write("You ask the innkeeper what time it is.\n");
        say(QCTNAME(TP) + " asks the innkeeper what time it is.\n");
        gHumphrie->command("say It is about " + qstime() + ".");
        return 1;
    }

    return 0;
}

/*
 * Function name: fire_desc
 * Descripiton  : VBFC for fireplace
 * Arguments    : string arg -- what we're looking at
 * Returns      : string description
 */
public varargs string
fire_desc(string arg = "")
{
    int fire_state = query_fire_state();
    string tmpstr;

    switch ( arg )
    {
    case "fireplace":
        switch ( fire_state )
        {
        case FIRE_BURNING:
            return "A wide stone fireplace, large enough to roast an "
                + "entire stag, is set into the north wall. A fire burns "
                + "brightly in the fireplace, casting a flickering light "
                + "over the room.\n";
        case FIRE_UNLIT_WOOD:
            return "A wide stone fireplace, large enough to roast an "
                + "entire stag, is set into the north wall. Firewood "
                + "is stacked in the fireplace.\n";
        default:
            return "A wide stone fireplace, large enough to roast an "
                + "entire stag, is set into the north wall.\n";
        }

    case "fire":
        if ( fire_state == FIRE_BURNING )
            return "A fire burns brightly in the fireplace.\n";

        return "You find no fire.\n";

    case "wood":
        switch ( fire_state )
        {
        case FIRE_BURNING:
            return "The wood in the fireplace burns brightly, emiting "
                + "a pleasant warmth.\n";
        case FIRE_UNLIT_WOOD:
            return "Unlit wood is piled in the fireplace.\n";

    default:
        return "You find no firewood.\n";
    }

    case "ash":
        switch ( fire_state )
        {
        case FIRE_BURNING:
            return "Beneath the brightly burning fire, ashes cover "
                + "the bottom of the fireplace.\n";
        case FIRE_UNLIT_WOOD:
            return "Beneath the unlit wood, ashes cover the bottom of "
                + "the fireplace.\n";
        default:
            return "Ashes cover the bottom of the fireplace.\n";
        }

    default:
        if ( fire_state == FIRE_BURNING )
            tmpstr = "The smell of warm food greets you as you enter this "
                + "cosy room. A wide fireplace in the north wall, large "
                + "enough to roast an entire stag, holds a brightly "
                + "burning fire. ";
        else
            tmpstr = "The smell of warm food greets you as you enter this "
                + "cosy room. A wide fireplace is in the north wall, large "
                + "enough to roast an entire stag. ";

        return (tmpstr + "A door leads south into a room filled with "
            + "steam. Old, smoothly carved wooden furniture lines the walls, "
            + "consisting primarily of eating-tables and benches. By the "
            + "west wall there is a counter. On the wall close to the "
            + "entrance there is a menu.\n");
    }
    return "";
}

/*
 * Function name: leave_inv
 * Description  : mask parent to be sure that departing players
 *                are removed from chair/sofa occupants
 * Arguments    : object ob -- the departing object
 *                object dest -- its destination
 *
 * If they leave via a normal exit, they've already been made to stand
 * by the exit efunc check_sitting(). However, if they leave by quitting,
 * going netdead, teleporting, etc and we don't call leave_inv_room_chairs(),
 * then they'll still look as if they're here.
 */
public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    leave_inv_room_chairs(ob, to);
}
