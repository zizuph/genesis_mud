/*
 * Fixed a bug in the bottle (fill) 6-10-98 Amelia
 * Changed to inheriting from /d/Earthsea/std/room
 * and made indoors Ckrik 9/2003
 *
 * Changed soft amount for water to 200 Ckrik 3/2004
 */

#pragma strict_types
#pragma no_clone

inherit "/std/room";
inherit "/lib/pub";
inherit "/sys/global/money";

#include <macros.h>
#include <stdproperties.h>

public void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_short("The Seaside Tavern");
    set_long("The small tavern is filled with loud" +
        " voices and laughter, coming from gangs of" +
        " sailors and harbour workers seated at the" +
        " long tables placed alongside the walls of the room." +
        " A large hearth with a blazing fire occupies" +
        " the middle of the room, and you feel a pleasant" +
        " smell of boiling stew coming from the blackened" +
        " pots hanging over the fire." +
        " The light is very dim at the edges of the room," +
        " with flickering shadows dancing on the walls." +
        " An exit leads to a darkened room to the north." +
        " A counter is built at the far end, with a busy" +
        " tavern keeper working hard on serving his" +
        " customers. You notice a menu hanging on the wall.\n");
    add_item((({"exit", "darkened room"})),
        "There is a darkened room to the north of the tavern, " +
        "and you hear the sound of loud snores coming from it.\n");
    add_item("fire","A blazing fire burns in the" +
        " hearth, spreading light and a pleasant heat" +
        " across the large room.\n");
    add_item("tables", "This tavern is furnished with" +
        " long tables and benches, where the visitors can" +
        " sit and enjoy their meal or drink. The tables" +
        " seem worn down from years of use, with scarred" +
        " surfaces. Most of the tables are occupied.\n");
    add_item("pots","Huge blackened pots hang over" +
        " the blazing fire, filled with the boiling stew" +
        " that the tavern keeper or his maids serves to" +
        " the visitors of the tavern.\n");
    add_item("stew","Inside the pots you can see" +
        " a stew with meat, vegetables and potatoes that" +
        " smell absolutely delicious.\n");
    add_item("shadows","The light from the fire in" +
        " the middle of the room creates flickering" +
        " shadows on the walls.\n");
    add_item("sailors","Several of the long tables are" +
        " occupied with gangs of sailors, talking and" +
        " laughing loudly over a mug of Gontish beer." +
        " Some seems to have taken more than one mug as" +
        " well, judging by the drunken look they give you.\n");
    add_item("workers","Several harbour workers have" +
        " entered the inn to rest a little from the hard" +
        " work.\n");
    add_item("hearth","A large hearth is built in the" +
        " middle of the room, strategically placed to give" +
        " as much light as possible. A blazing fire burns" +
        " in it, spreading a pleasant heat across the room." +
        " Large blackened pots filled with cooking stew" +
        " hang over it.\n");
    add_item("menu","@@read_menu");
    add_cmd_item("menu","read","@@read_menu");
    add_exit("pub_sleep_room", "north");
    add_exit("city_street/city_road17", "south", "@@outfun");
    add_drink(({"water","glass of water"}), ({"glass of water","water"}),
        ({"refreshing", "ice-cold"}), 200, 0, 5, "glass of water",
        "glasses of water","A glass of water filled" +
        " to the brim with ice cold water, probably" +
        " fetched just recently from one of the" +
        " wells of Gont Port. Very refreshing!\n");
    add_drink(({"beer","Gontish beer"}),
        "beer", ({"dark", "Gontish", "gontish"}), 20, 50, 40,
        "dark Gontish beer", "dark Gontish beers",
        "This is a mug filled to the brim" +
        " with dark Gontish beer, crowned with yellow foam. It" +
        " tastes fairly bitter.\n");
    add_drink(({"wine","imported wine"}),"wine",
        ({"dark-red", "imported"}), 20, 60, 80,
        "dark-red imported wine",
        "dark-red imported wines","The dark-red imported wine is" +
        " served in a fancy glass with a high foot, with a full" +
        " earthy smell and a long aftertaste.\n");
    add_drink(({"grog", "Gontish grog", "gontish grog"}),
        "grog", ({"gontish", "Gontish"}), 20, 20, 75, "Gontish grog",
        "Gontish grogs", "This is a deep-brown, strong drink " +
        "favoured by the seamen and pirates of Gont. The precise " +
        "ingredients are unknown, however, it smells strongly of " +
        "dark rum and whiskey.\n");
    add_drink(({"liquor","home-made liquor"}),"liquor",
        "crystal-clear", 10, 75, 100, "crystal-clear liquor",
        "crystal-clear liquors","A small mug filled with" +
        " strong crystal-clear liquor made from barley and" +
        " flavored with herbs and wild berries. It burns" +
        " your throat and warms the stomach as it goes down.\n");
    add_food(({"stew","meat stew"}),"stew",({"meat","vegetable"}),
        130,100,"meat and vegetable stew","meat and vegetable stews",
        "This bowl of steaming hot stew contains both pieces of meat" +
        " and vegetables. You notice carrots, potatoes and green peas," +
        " together with large slices of probably goat meat. It smells" +
        " delicious and is fairly spicy, with whole corns of black" +
        " pepper floating around.\n");
    add_food(({"corn on the cob", "boiled corn on the cob", "corn"}),
        "corn", ({"boiled", "yellow"}), 30, 25,
        "boiled corn on the cob", "boiled corns on the cob",
        "This is a golden yellow sweet corn, still on the cob. It " +
        "makes a nice snack.\n");
    add_food(({"herring", "smoked herring"}), "herring",
        ({"smoked"}), 30, 25, "smoked herring",
        "smoked herrings", "This is a smoked herring, which has " +
        "been lightly fried in butter.\n");
    add_food(({"codfish", "cod", "boiled cod", "fish"}),
        ({"codfish", "cod", "boiled cod", "fish"}),
        ({"boiled"}), 125, 120, "boiled cod", "boiled cods",
        "This is a large codfish which has been stewed for some time " +
        "in its own juices.\n");
    add_food(({"soup","broccoli soup"}),"soup",
        ({"steaming","broccoli"}),80,79,"bowl of steaming broccoli soup",
        "bowls of steaming broccoli soup","A round wooden plate filled" +
        " with steaming broccoli soup, boiled with cheese and onions" +
        " to make it tasty.\n");
    add_prop(ROOM_I_INSIDE, 1);
}

public int
outfun()
{
    write("You blink your eyes as you step out from the smokey tavern.\n");
    return 0;
}

public string
read_menu()
{
    say(QCTNAME(this_player()) + " reads the menu on the wall.\n");
    return "The menu reads: \n" +
        "     **************************************\n" +
        "     *                                    *\n" +
        "     *    Welcome to the Seaside Tavern!  *\n" +
        "     *                                    *\n" +
        "     *    Drinks:       Water    5 cc     *\n" +
        "     *           Gontish Beer   40 cc     *\n" +
        "     *          Imported Wine   80 cc     *\n" +
        "     *           Gontish grog   75 cc     *\n" +
        "     *          Barley Liquor  160 cc     *\n" +
        "     *                                    *\n" +
        "     *    For the road:                   *\n" +
        "     *                                    *\n" +
        "     *   Large bottle of grog  800 cc     *\n" +
        "     *        Small bottle of             *\n" +
        "     *          barley liquor  650 cc     *\n" +
        "     *         Bottle refills  varies     *\n" +
        "     *                                    *\n" +
        "     *    Food:                           *\n" +
        "     *        Corn on the cob   25 cc     *\n" +
        "     *          Broccoli soup   79 cc     *\n" +
        "     *              Meat stew  100 cc     *\n" +
        "     *             Boiled cod  120 cc     *\n" +
        "     *         Smoked herring   25 cc     *\n" +
        "     *                                    *\n" +
        "     *    Room key              35 cc     *\n" +
        "     *      (sleep one off overnight)     *\n" +
        "     *                                    *\n" +
        "     **************************************\n\n";
}

public int
buy_special(string str)
{
    object tp = this_player(), to = this_object(), bottle, key;

    if(!str)
    {
        return 0;
    }

    setuid();
    seteuid(getuid());

    if(str == "key" || str == "room key")
    {
        if(!take_money(tp, 35))
        {
            write("You can't afford a room key.\n");
            return 1;
        }

        key = clone_object("/d/Earthsea/gont/gont_city/obj/pub_key");

        if(key->move(tp))
        {
            key->move(to, 1);
            write("You are too loaded, and the key drops onto the floor.\n");
            return 1;
        }

        write("You pay the price and get your room key.\n");
        return 1;
    }

    switch(str)
    {
        case "bottle of liquor":
        case "small bottle of liquor":
        case "bottle of barley liquor":
        case "small bottle of barley liquor":
        case "small bottle":
            if(!take_money(tp, 650))
            {
                write("You can't afford the small bottle of barley liquor.\n");
                return 1;
            }

            bottle = clone_object("/d/Calia/gelan/objects/bottle");
            bottle->set_max(825);
            bottle->set_adj("small");
            bottle->set_short("small bottle");
            bottle->set_pshort("small bottles");
            bottle->set_soft(bottle->query_max());
            bottle->set_filled_short(({"barley liquor"}));
            bottle->set_alco(60 * bottle->query_max() / 100);

            if(bottle->move(tp))
            {
                write("You are too loaded, and the bottle " +
                    "drops down on the floor.\n");
                bottle->move(to, 1);
                return 1;
            }

            write("You pay the price and get your small bottle.\n");
            return 1;
        break;

        case "big bottle":
        case "big bottle of grog":
        case "big bottle of gontish grog":
        case "big bottle of Gontish grog":
        case "bottle of grog":
        case "large bottle of grog":
        case "large bottle of Gontish grog":
        case "bottle of Gontish grog":
            if(!take_money(tp, 800))
            {
                write("You can't afford the large bottle of grog.\n");
                return 1;
            }

            bottle = clone_object("/d/Calia/gelan/objects/bottle");
            bottle->set_max(3500);
            bottle->set_adj("big");
            bottle->set_soft(bottle->query_max());
            bottle->set_filled_short(({"Gontish grog"}));
            bottle->set_short("big bottle");
            bottle->set_pshort("big bottles");
            bottle->set_alco(40 * bottle->query_max() / 100);

            if(bottle->move(tp))
            {
                bottle->move(to);
                write("You are too loaded and the bottle drops " +
                    "on the floor.\n");
                return 1;
            }

            write("You pay the price and get your " +
                "big bottle of Gontish grog.\n");
            return 1;
        break;
    }

    return 0;
}

public int
refill_bottle(string str)
{
    object tp = this_player(), to = this_object(), bottle;
    string drink;
    int price;

    if(!str)
    {
        write("Refill which container with what drink?\n");
        return 1;
    }

    setuid();
    seteuid(getuid());
    if (!parse_command(str, tp, " %o [with] %s ", bottle, drink))
    {
        write("Refill which container with what drink?\n");
        return 1;
    }
    if (drink == "")
    {
        write("Refill which container with what drink?\n");
        return 1;
    }
    if (bottle->query_soft() != 0)
    {
        write("The " + bottle->query_short() + " is not empty!\n");
        return 1;
    }
    switch (drink)
    {
    case "grog":
    case "Gontish grog":
    case "gontish grog":
        price = bottle->query_max() / 5;
        if (!take_money(tp, price))
        {
            write("You cannot afford the price to refill the " +
                    bottle->query_short() + ".\n");
            return 1;
        }
        bottle->set_soft(bottle->query_max());
        bottle->set_filled_short(({"Gontish grog"}));
        bottle->set_alco(40 * bottle->query_max() / 100);
        write("You pay " + price + " cc and refill your " +
                bottle->query_short() + " with " +
                "Gontish grog.\n");
        return 1;
    case "liquor":
    case "barley liquor":
        price = bottle->query_max() / 2;
        if (!take_money(tp, price))
        {
            write("You cannot afford the price to refill the " +
                    bottle->query_short() + ".\n");
            return 1;
        }
        bottle->set_soft(bottle->query_max());
        bottle->set_filled_short(({"barley liquor"}));
        bottle->set_alco(60 * bottle->query_max() / 100);
        write("You pay " + price + " cc and refill your " +
                bottle->query_short() + " with " +
                "barley liquor.\n");
        return 1;
    default:
        write("You cannot refill the " + bottle->query_short() + " with " +
                drink + " at this pub.\n");
        return 1;
    }
}

public void
init()
{
    ::init();
    init_pub();
    add_action(buy_special, "buy");
    add_action(refill_bottle, "refill");
}
