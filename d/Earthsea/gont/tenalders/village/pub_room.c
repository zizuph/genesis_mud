/*
 * coded by Amelia for Ten Alders 4/13/97
 * the local pub
*/

#pragma no_clone
#pragma strict_types

inherit "/d/Earthsea/std/room";
inherit "/d/Earthsea/lib/room_tell";
inherit "/lib/pub";
inherit "/lib/trade";
inherit "/sys/global/money";

#include <stdproperties.h>
#include <macros.h>
#include <language.h>

#define COFFEE "/d/Earthsea/gont/tenalders/obj/items/gontish_coffee"
#define MILK "/d/Earthsea/gont/tenalders/obj/items/goat_milk"
#define SALAD "/d/Earthsea/gont/tenalders/obj/items/herb_salad"
#define COFFEE_PRICE 75
#define MILK_PRICE 35
#define SALAD_PRICE 300

private object tender;

public void
create_earthsea_room()
{
    object door;
    config_default_trade();
    set_short("A pub");
    set_long("A pub. Not expensively furnished, " +
        "this room is small yet comfortable. A hearth takes up " +
        "most of the west wall, where you see some meat roasting " +
        "on a spit over the fire. There are rough pine tables " +
        "and chairs set about for customers to sit at while " +
        "drinking their brew. Along the north wall there is " +
        "a long counter. A sign hangs on " +
        "the wall above the counter.\n");
    add_item((({"hearth", "spit", "fire", "meat"})),
        "Along the west wall is a large open hearth " +
        "with a fire burning merrily in it. You see what " +
        "appears to be a goat roasting on a spit, filling " +
        "the room with its savoury aroma.\n");
    add_item((({"tables", "pine tables", "chairs"})),
        "The furniture is unfinished and a bit rough, but " +
        "serviceable.\n");
    add_item((({"counter", "long counter"})),
        "The long counter along the north wall is also " +
        "made of rough pine. There are glasses and crude " +
        "pottery dishes stacked behind it.\n");
    add_item((({"menu", "pricelist", "sign"})),
        "Please read the sign, if you know how to read.\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_food(
        ({"cheese", "goat cheese"}), ({"cheese", "goat cheese"}),
        ({"goat", "white"}), 35, 25, "goat cheese", "goat cheeses",
        "A hunk of white goat cheese.\n");
    add_food(
        ({"honey", "golden honey", "some golden honey"}),
        ({"honey", "golden honey", "some golden honey"}),
        ({"golden", "some"}), 20, 25, "golden honey", "golden honeys",
        "Some golden clover honey made by the bees of Gont.\n");
    add_food(
        ({"loaf", "bread", "loaf of black bread", "black bread"}),
        ({"loaf", "bread", "loaf of black bread", "black bread"}),
        ({"black"}), 45, 30, "loaf of black bread",
        "loaves of black bread",
        "A round loaf of dark, heavy bread. It looks " +
        "very wholesome and nutricious.\n");
    add_food(
        ({"haunch", "goat haunch", "roasted goat haunch"}),
        ({"haunch", "goat haunch", "roasted goat haunch"}),
        ({"roasted", "goat"}), 150,70, "roasted goat haunch",
        "roasted goat haunches",
        "A haunch of tender goat meat, dark-brown and " +
        "roasted to perfection.\n");
    add_food(
        ({"pie", "blueberry pie"}), ({"pie", "blueberry pie"}),
        ({"blueberry"}), 25, 25, "blueberry pie", "blueberry pies",
        "A blueberry pie. A tender light-brown crust " +
        "surrounds a filling of luscious blueberries.\n");
    add_drink(
        ({"flagon of mead", "mead", "flagon", "flagon of golden mead"}),
        ({"flagon of mead", "mead", "flagon", "flagon of golden mead"}),
        ({"golden"}), 100, 20, 30, "flagon of golden mead",
        "flagons of golden mead",
        "A flagon of rich golden mead, brewed from " +
        "the honey of Ten Alders' bees.\n", "");
    add_drink(
        ({"dark brew", "frosty dark brew", "frosty brew",
        "brew"}), ({"dark brew", "frosty dark brew", "frosty brew",
        "brew"}), ({"frosty", "dark"}), 100, 10, 35,
        "frosty dark brew", "frosty dark brews",
        "A local brew, frosty and dark, something between " +
        "beer and ale.\n", "");
    add_drink(
      ({"old buzzard rye whiskey", "Old Buzzard rye whiskey",
      "rye whiskey", "whiskey", "old buzzard whiskey"}),
      ({"old buzzard rye whiskey", "Old Buzzard rye whiskey",
      "rye whiskey", "whiskey", "old buzzard whiskey"}),
      ({"old", "buzzard", "rye", "Old", "Buzzard"}),
      100, 50, 75, "Old Buzzard rye whiskey",
      "Old Buzzard rye whiskeys",
      "A strong rye whiskey, tasting like they threw a " +
      "dead buzzard into the distillation vat.\n", "");
    set_tell_time(100);
    add_tell("The fire crackles as juices from the " +
        "roasting meat drip into it.\n");
    add_tell("The aroma of roasting meat and herbs makes " +
        "your mouth water.\n");
    add_tell("The glowing fire casts shadows around the room.\n");
    add_tell("Some locals get up from a table, pay their " +
        "bill, and leave.\n");
    reset_room();
    door = clone_object("/d/Earthsea/gont/tenalders/obj/doors/pub_door_in");
    door->move(this_object());
}

public void
reset_room()
{
    if(!objectp(tender))
    {
        tender = clone_object("/d/Earthsea/gont/tenalders/npc/bar_tender");
        tender->arm_me();
        tender->move(this_object());
        tender->command("emote arrives.");
    }
}

public int
read_sign(string str)
{
    if(str == "sign" || str == "menu" || str == "pricelist")
    {
        write("You read the following: \n" +
          "\n\n" +
          "            THE RANDY GOAT PUB\n\n" +
          "            E-e-i-l, proprietor and bar tender\n" +
          "            ^^^^^^^                           \n" +
          "            Killian                           \n\n" +
          "      BEVERAGES:\n\n" +
          "            Flagon of mead   30cc\n" +
          "            Frosty dark brew 35cc\n" +
          "            Old Buzzard rye whiskey  75cc\n" +
          "            Goat milk     20cc\n" +
          "            strong Gontish coffee   75cc\n" +
          "           \n\n" +
          "     VICTUALS:\n\n" +
          "            Goat cheese  25cc\n" +
          "            Loaf of black bread  30cc\n" +
          "            Roasted goat haunch  70cc\n" +
          "            Herb salad  300cc\n" +
          "            Blueberry pie   25cc\n" +
          "            Some golden honey   25cc\n" +
          "\n\n");
        return 1;
    }

    return 0;
}

public int
buy_special(string str)
{
    object stuff, tp = this_player(), to = this_object();
    int num = 0, i, price;
    string items;

    if(!tender || !present(tender, to))
    {
        write("The bar tender is not here now to serve you!\n");
        return 1;
    }

    if(!str)
    {
        return 0;
    }

    if(!(i = parse_command(str, to, "%d %s", num, items)))
    {
        num = 1;
        items = str;
    }

    if(num > 10)
    {
        tender->command("say That's too many! it will break my " +
            "back!");
        return 1;
    }

    setuid();
    seteuid(getuid(to));

    switch(items)
    {
        case "goat milk":
        case "goat milks":
        case "milk":
        case "milks":
            price = MILK_PRICE * num;
            stuff = clone_object(MILK);
            stuff->set_heap_size(num);
        break;
        case "Gontish coffee":
        case "gontish coffee":
        case "coffee":
        case "coffees":
        case "Gontish coffees":
        case "gontish coffees":
            price = COFFEE_PRICE * num;
            stuff = clone_object(COFFEE);
            stuff->set_heap_size(num);
        break;
        case "salad":
        case "salads":
        case "herb salad":
        case "herb salads":
            price = SALAD_PRICE * num;
            stuff = clone_object(SALAD);
            stuff->set_heap_size(num);
        break;
        default:
            return 0;
        break;
    }

    if(!(take_money(tp, price)))
    {
        stuff->remove_object();
        tender->command("frown");
        tender->command("ask " + lower_case(tp->query_name()) +
            " Come back when you are a little richer.");
        tender->command("emote goes about his business.");
        return 1;
    }

    if(stuff->move(tp))
    {
        write("You pay the bar tender, but can't seem " +
            "to carry everything.\n");
        tell_room(to, "The bar tender places " + LANG_ASHORT(stuff) +
            " on the counter.\n");
        stuff->move(to);
        return 1;
    }

    write("You pay the bar tender.\nThe bar tender hands you " +
        LANG_ASHORT(stuff) + ".\n");
    tell_room(to, "The bar tender hands " +
        QTNAME(tp) + " " + LANG_ASHORT(stuff) + ".\n", ({ tp }));
    return 1;
}

public void
init()
{
    ::init();
    init_pub();
    add_action(read_sign, "read");
    add_action(buy_special, "buy");
}
