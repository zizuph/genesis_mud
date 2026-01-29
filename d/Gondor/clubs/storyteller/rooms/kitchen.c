/*
 *  /d/Gondor/clubs/storyteller/rooms/kitchen.c
 *  Copyright Rolf Braun a.k.a. Elessar, Genesis, 1998
 *
 * A room where drinks and snacks can be bought
 */
#pragma strict_types
#pragma save_binary

inherit "/d/Gondor/common/room.c";
inherit "/d/Gondor/common/lib/inn.c";

#include <macros.h>
#include <money.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/clubs/storyteller/defs.h"

#define STAND_DIR   "/d/Gondor/std/"
#define SNACKS_PRICES ({ 30, 30, 35, 40, 50, 60, 75 })
#define DRINKS_PRICES ({ 3, 35, 40, 75, 100, 100, 120, 150, 200 })
// Prototypes:

public void
create_room()
{
    set_short("the Storytellers' kitchen");
    set_long("You have entered a small cozy kitchen. Bright copper " +
        "pots hang from above amongst bunches of dried herbs. The " +
        "entire room has the sweet smell of baked goods. Cooks rush " +
        "about pulling pans of cookies, crackers and rolls from the " +
        "ovens, then placing them on racks to cool. On one wall has " +
        "a menu been posted.\n");
    add_item(({"lantern", "lanterns", "brass lantern", "brass lanterns"}),
        "You find many lanterns, all of them small and of brightly " +
        "polished brass, providing ample lighting for the entire room.\n");
    add_item(({"panel", "panels", "wood panel", "wood panels"}),
        "The wood panels on the walls have all been polished down, " +
        "though they do look aged still.\n");
    add_item(({"wall", "walls"}), "The walls are made of polished wood " +
        "panels, and have lanterns attached to them to provide light in " +
        "the room.\n");
    add_item(({"pots", "copper pots", "pot", "bright copper pots", 
        "copper pot"}), "Bright copper pots, well-polished yet well-used. " +
        "The cooks could not work without them.\n");
    add_item(({"pans", "pan", "pans of cookies", "pans of crackers",
        "pans of rolls"}), "Pans of cookies, crackers and rolls are cooling " +
        "in racks along one wall, and there are more in the ovens still.\n");
    add_item(({"cookies", "crackers", "rolls", "cookie", "cracker", "roll",
        "sugar cookies", "chocolate cookies", "salty crackers",
        "butter rolls",}), "In the ovens, and on pans cooling in racks " +
        "along one wall, you see sugar cookies, chocolate cookies, salty " +
        "crackers and butter rolls in plenty.\n");
    add_item(({"herbs", "herb", "dried herbs"}), "They are mostly spices " +
        "used in the cooking.\n");
    add_item(({"cooks"}), "There are several cooks working here, busily " +
        "forming new cookies and crackers on pans to be put in the ovens, " +
        "or taking finished ones out to cool. They do seem to have time " +
        "for taking orders though.\n");
    add_item(({ "pricelist", "list", "prices", "menu" }), price_long());
    add_cmd_item(({ "pricelist", "list", "prices", "menu" }), "read",
        price_long());

    config_default_trade();
    set_money_give_max(2000);
    set_money_give_out(({ 2000, 700, 50, 4 }));
    set_money_give_reduce(({ 1, 1, 1, 1}));
    set_innkeeper_name("the cook");

    add_prop(ROOM_I_INSIDE, 1);  /* This is a real room */
    add_prop(ROOM_I_LIGHT, 2);

    add_exit(STORYT_DIR + "rooms/foyer", "west", 0, 0);
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
      "The pricelist reads:\n\n" +
      "WELCOME TO THE STORYTELLER'S KITCHEN\n\n" +
      "Drinks:\n" +
      "   Water                 ...  " + money_text(DRINKS_PRICES[0]) + "\n" +
      "   Hot tea with lemon    ...  " + money_text(DRINKS_PRICES[1]) + "\n" +
      "   Freshly brewed coffee ...  " + money_text(DRINKS_PRICES[2]) + "\n" +
      "   Hot rum toddy         ...  " + money_text(DRINKS_PRICES[3]) + "\n" +
      "   Robust red wine       ...  " + money_text(DRINKS_PRICES[4]) + "\n" +
      "   Delicate white wine   ...  " + money_text(DRINKS_PRICES[5]) + "\n" +
      "   Sweet spiced mead     ...  " + money_text(DRINKS_PRICES[6]) + "\n" +
      "   Glass of Brandywine   ...  " + money_text(DRINKS_PRICES[7]) + "\n" +
      "   Cask-aged dwarven spirits  " + money_text(DRINKS_PRICES[8]) + "\n\n" +
      "Snacks:\n" +
      "   Chocolate cookies     ...  " + money_text(SNACKS_PRICES[0]) + "\n" +
      "   Sugar cookies         ...  " + money_text(SNACKS_PRICES[1]) + "\n" +
      "   Salty crackers        ...  " + money_text(SNACKS_PRICES[2]) + "\n" +
      "   Soft butter rolls     ...  " + money_text(SNACKS_PRICES[3]) + "\n" +
      "   Cheese                ...  " + money_text(SNACKS_PRICES[4]) + "\n" +
      "   Fresh fruit           ...  " + money_text(SNACKS_PRICES[5]) + "\n" +
      "   Bowl of mixed nuts    ...  " + money_text(SNACKS_PRICES[6]) + "\n\n" +
      "Try 'order wine for gold' if you want to specify what to pay with. " +
      "You can also specify 'order 3 mead' to get three meads. There is a " +
      "maximum of "+hook_query_max_items() +
      " items you can order at one time.") + "\n\n";
}

public int
hook_query_max_items()
{
    return 5;
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
            write("The cook says: Sorry, it's too dark in here - I can't " +
                "see!\n");
        else
            write("Someone says: Sorry, it's too dark in here - I can't " +
                "see!\n");
        return 1;
    }

    if (!IS_STORYTELLER(TP))
    {
        write("The cook shakes his head at you, and says: Storytellers only.\n");
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

    if (number > 1)
    {
        NFN("The barkeeper says: One at a time, I can only work "+
            "so fast!");
        return 0;
    }

    switch (item_name)
    {
    case "water":
    case "waters":
        file = "obj/water";
        ware = "water";
        price = DRINKS_PRICES[0];
        break;
    case "tea":
    case "teas":
    case "lemon tea":
    case "lemon teas":
    case "hot tea":
    case "hot teas":
    case "hot lemon tea":
    case "hot lemon teas":
    case "hot tea with lemon":
    case "hot teas with lemon":
        file = "obj/tea";
        ware = "hot lemon tea";
        price = DRINKS_PRICES[1];
        break;
    case "coffee":
    case "coffees":
    case "fresh coffee":
    case "fresh coffees":
    case "brewed coffee":
    case "brewed coffees":
    case "fresh brewed coffee":
    case "fresh brewed coffees":
    case "freshly brewed coffee":
    case "freshly brewed coffees":
        file = "obj/coffee";
        ware = "freshly brewed coffee";
        price = DRINKS_PRICES[2];
        break;
    case "toddy":
    case "toddies":
    case "rum":
    case "rums":
    case "rum toddy":
    case "rum toddies":
    case "hot rum toddy":
    case "hot rum toddies":
    case "hot toddy":
    case "hot toddies":
    case "hot rum":
    case "hot rums":
        file = "obj/toddy";
        ware = "hot rum toddy";
        price = DRINKS_PRICES[3];
        break;
    case "wine":
    case "wines":
    case "red wine":
    case "red wines":
    case "robust wine":
    case "robust wines":
    case "robust red wine":
    case "robust red wines":
        file = "obj/redwine";
        ware = "red wine";
        price = DRINKS_PRICES[4];
        break;
    case "white wine":
    case "white wines":
    case "delicate white wine":
    case "delicate white wines":
    case "delicate wine":
    case "delicate wines":
        file = "obj/whitewine";
        ware = "white wine";
        price = DRINKS_PRICES[5];
        break;
    case "mead":
    case "meads":
    case "sweet mead":
    case "sweet meads":
    case "spiced mead":
    case "spiced meads":
    case "sweet spiced mead":
    case "sweet spiced meads":
        file = "obj/mead";
        ware = "sweet spiced mead";
        price = DRINKS_PRICES[6];
        break;
    case "brandy":
    case "brandies":
    case "brandywine":
    case "brandywines":
    case "glass of brandywine":
    case "glasses of brandywine":
        file = "obj/brandywine";
        ware = "glass of brandywine";
        price = DRINKS_PRICES[7];
        break;
    case "spirit":
    case "spirits":
    case "dwarven spirit":
    case "dwarven spirits":
    case "cask-aged spirit":
    case "cask-aged spirits":
    case "cask-aged dwarven spirit":
    case "cask-aged dwarven spirits":
        file = "obj/spirits";
        ware = "dwarven spirits";
        price = DRINKS_PRICES[8];
        break;
    case "cookie":
    case "cookies":
    case "chocolate":
    case "chocolates":
    case "chocolate cookie":
    case "chocolate cookies":
        file = "obj/chocolate_cookie";
        ware = "chocolate cookie";
        price = SNACKS_PRICES[0];
        break;
    case "sugar":
    case "sugars":
    case "sugar cookie":
    case "sugar cookies":
        file = "obj/sugar_cookie";
        ware = "sugar cookie";
        price = SNACKS_PRICES[1];
        break;
    case "cracker":
    case "crackers":
    case "salty cracker":
    case "salty crackers":
    case "salt cracker":
    case "salt crackers":
        file = "obj/cracker";
        ware = "salty cracker";
        price = SNACKS_PRICES[2];
        break;
    case "roll":
    case "rolls":
    case "butter roll":
    case "butter rolls":
    case "soft roll":
    case "soft rolls":
    case "soft butter roll":
    case "soft butter rolls":
        file = "obj/roll";
        ware = "soft butter roll";
        price = SNACKS_PRICES[3];
        break;
    case "cheese":
    case "cheeses":
        file = "obj/cheese";
        ware = "piece of cheese";
        price = SNACKS_PRICES[4];
        break;
    case "fruit":
    case "fruits":
    case "fresh fruit":
    case "fresh fruits":
        file = "obj/fruit";
        ware = "bowl of fresh fruit";
        price = SNACKS_PRICES[5];
        break;
    case "nut":
    case "nuts":
    case "mixed nuts":
    case "bowl of nuts":
    case "bowls of nuts":
    case "bowl of mixed nuts":
    case "bowls of mixed nuts":
        file = "obj/nuts";
        ware = "bowl of mixed nuts";
        price = SNACKS_PRICES[6];
        break;
    default :
        NFN("The barkeeper says: We don't have that on the menu.");
        return 0;
    }

    if (can_afford(price, number, ware, pay_type, get_type))
                buy_item(STORYT_DIR + file, number);
    return 1;
}

