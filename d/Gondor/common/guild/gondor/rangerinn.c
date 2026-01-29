/*
 *  The Gondorian Rangers Inn. 
 *  by Elessar
 *
 *  Modification log:
 *  950309 Improved the parser. /Arren
 *  December 1995: Inherit /d/Gondor/common/lib/inn.c. Olorin
 *  January 1997:  Added chess game by Fysix, Olorin
 */
#pragma strict_types
#pragma save_binary

inherit "/d/Gondor/common/room.c";
inherit "/d/Gondor/common/lib/inn.c";
inherit "/d/Gondor/common/lib/friend_or_foe.c";
inherit "/d/Gondor/common/guild/gondor/no_theft";

#include <macros.h>
#include <money.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild/lib/punish_defs.h"

#define STAND_DIR   "/d/Gondor/std/"
#define MY_PRICES ({ 3, 12, 24, 48, 216, 12, 36, 72, 144, 576 })

// Prototypes:
int     ranger_test();

public void
create_room()
{
    set_short("the Seven Stars Inn");
    set_long(BSN(
       "You are in the Seven Stars Inn. This is the place the Gondorian "
     + "Rangers come to forget their sorrows over a beer, and fill their "
     + "empty stomachs with a nice, hot meal. The pub is decorated with oak "
     + "panels, and you can smell the odour of beer and sweaty people from "
     + "the walls. There are several tables here with chairs beside them. "
     + "On the wooden floor lies the remains of a rug, which is now worn out, "
     + "covered with dirt, pipe ashes and holes. A few lamps are hanging from "
     + "the ceiling, creating a nice atmosphere. By the west wall is a "
     + "counter, behind which the barkeeper is standing. Behind him is a "
     + "pricelist and menu. A stairway leads up."));

    add_item(({ "rug", "remains of rug" }),
       "The rug was once beautiful and red, but now it is grey and "
     + "full of holes.\n");
    add_item(({ "table", "tables", "chair", "chairs"}),
      "All the tables and chairs are taken by other Rangers.\n");
    add_item(({ "panels", "wooden panels" }),
      "You notice nothing special about the wooden panels.\n");
    add_item("counter", BSN(
       "Above the wooden counter is a lamp and a shelf. On the shelf "
     + "are several brands of liquor. Behind the counter is the barkeeper of "
     + "the Seven Stars Inn, the inn of the Gondorian Rangers."));
    add_item(({ "innkeeper", "bartender", "barkeeper", "beleg" }), BSN(
       "The barkeeper, Beleg, is a human Ranger with a jovial face. He seldom "
     + "takes a break, but runs between the kitchen and the bar serving his "
     + "customers, trying to keep the glasses as shiny as possible, and the "
     + "meals hot and delicious. Beleg looks at you, waiting for you to order "
     + "something."));
    add_item(({ "stair", "stairs", "stairway" }), BSN(
       "The wooden stairway is just to the left by the door, and "
     + "leads up to the floor above, where the bedrooms are located. "
     + "The steps bear sign that many Rangers have passed this way, "
     + "to get rest after a tiresome journey, or to sleep before going "
     + "on a dangerous mission."));
    add_item(({ "pricelist", "list", "prices", "menu" }), price_long());
    add_cmd_item(({ "pricelist", "list", "prices", "menu" }), "read", price_long());

    config_default_trade();
    set_money_give_max(2000);
    set_money_give_out(({ 2000, 700, 50, 4 }));
    set_money_give_reduce(({ 1, 1, 1, 1})); 
    set_innkeeper_name("the barkeeper");

    add_prop(ROOM_I_INSIDE, 1);  /* This is a real room */
    add_prop(ROOM_M_NO_STEAL, no_theft);

    add_exit(RANGER_GON_DIR + "startchamber", "up", ranger_test, 2);

    clone_object(RANGER_DIR + "obj/inn_door2")->move(TO);

    if (file_size(CHESS_GAME + ".c") > 0)
        clone_object(CHESS_GAME)->move(TO);
    else
        log_file("errors", file_name(TO) + 
            " >>>>> "+CHESS_GAME+" not found!\n");
}

public void
init() 
{
    ::init();

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
    + BSN("Try 'order ale for gold' if you want to specify what to pay with. "
    + "You can also specify 'order 3 ale' to get three ales. There is a "
    + "maximum of "+hook_query_max_items()
    + " items you can order at one time.") + "\n");
}

public int
hook_query_max_items()
{
    return 10;
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
            write("The barkeeper says: Sorry, it's too dark in here - I can't see!\n");
        else
            write("Someone says: Sorry, it's too dark in here - I can't see!\n");
        return 1;
    }

    if ((tp->query_skill(SS_PUNISHMENT) == NOTRADE) ||
        (tp->query_skill(SS_PUNISHMENT) == NOACCESS))
    {
        write("The barkeeper says: Sorry, but the Council of Rangers informed me "
          + "that you are not to be served.\n");
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

int
ranger_test()
{
    if (IS_RANGER(TP) || IS_NRANGER(TP))
        return 0;

    if (this_player()->query_wiz_level())
        return 0;

    write("Since you are not a ranger, the barkeeper stops you from " +
        "going there.\n");
    return 1;
}
