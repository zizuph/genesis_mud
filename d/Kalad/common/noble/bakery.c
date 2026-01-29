#include "defs.h"
inherit "/d/Kalad/room_std";
inherit "/lib/pub";

void
create_room()
{
    ::create_room();
    INSIDE;
    set_short("Noble district Bakery");
    set_long("You have entered a clean, fresh smelling shop. "+
    "All around you, delicious cakes, pastries and breads "+
    "are on display. Behind the counter in front of you, "+
    "a flour-covered baker stands, waiting to take your order. "+
    "A white sign is located on the wall, for you to read.\n");
    add_item(({"sign", "menu"}), "It has words on it.\n");
    add_cmd_item(({"sign", "menu"}), "read", "@@menu@@");
    add_exit(NOBLE(gateway/s4),"north",0,-1,-1);

    // id, names, adj, amount, price, short, pshort, long
    add_food(({"powder doughnut", "powder doughnuts", "doughnut", "doughnuts"}),
        "doughnut",
        "powder",
        10,
        10,
        "powder doughnut",
        "powder doughnuts",
        "A small doughnut covered with white powdered sugar.\n"
        );
    add_food(({"jelly-filled doughnut", "jelly-filled doughnuts"}),
        "doughnut",
        "jelly-filled",
        18,
        12,
        "jelly-filled doughnut",
        "jelly-filled doughnuts",
        "A small doughnut filled with jelly substance.\n"
        );
    add_food(({"cream cheese pastry", "cream cheese pastries", "pastry",
                "pastries"}),
        "pastry",
        ({"cream", "cheese"}),
        25,
        15,
        "cream cheese pastry",
        "cream cheese pastries",
        "A delicious pastry filled with cream cheese and topped " +
                "with fruit jelly.\n"
        );
    add_food(({"maple bar", "maple bars", "bar", "bars"}),
        "bar",
        "maple",
        18,
        15,
        "maple bar",
        "maple bars",
        "A maple covered block of bread.\n"
        );
    add_food(({"chocolate chip cookie", "chocolate chip cookies", "cookie",
                "cookies"}),
        "cookie",
        ({"chocolate", "chip"}),
        20,
        16,
        "chocolate chip cookie",
        "chocolate chip cookies",
        "A huge cookie filled with giant chocolate chips.\n"
        );
    add_food(({"oatmeal cookie", "oatmeal cookies"}),
        "cookie",
        "oatmeal",
        20,
        16,
        "oatmeal cookie",
        "oatmeal cookies",
        "A huge cookie made out of oatmeal.\n"
        );
    add_food(({"cream puff", "cream puffs", "puff", "puffs"}),
        "puff",
        "cream",
        25,
        20,
        "cream puff",
        "cream puffs",
        "This cream puff is oozing with yummy cream.\n"
        );
    add_food(({"cream pie", "cream pies", "pie", "pies"}),
        "pie",
        "cream",
        28,
        22,
        "cream pie",
        "cream pies",
        "This is a small pie filled with custard cream.\n"
        );
    add_food(({"lemon pie", "lemon pies"}),
        "pie",
        "lemon",
        28,
        22,
        "lemon pie",
        "lemon pies",
        "This is a small pie filled with lemon cream.\n"
        );
    add_food(({"carrot cake", "carrot cakes", "cake", "cakes"}),
        "cake",
        "carrot",
        40,
        30,
        "carrot cake",
        "carrot cakes",
        "A big cake made of carrot bread with cream cheese frosting.\n"
        );
    add_food(({"chocolate cake", "chocolate cakes"}),
        "cake",
        "chocolate",
        65,
        50,
        "chocolate cake",
        "chocolate cakes",
        "A huge cake made of chocolate cream.\n"
        );
     add_food(({"fudge cake", "fudge cakes"}),
        "cake",
        "fudge",
        75,
        60,
        "fudge cake",
        "fudge cakes",
        "A huge cake made of chocolate fudge.\n"
        );
     add_food(({"Kabal supreme cake", "Kabal supreme cakes", "Kabal cake",
                 "Kabal cakes", "supreme cake", "supreme cakes",
                 "kabal supreme cake", "kabal supreme cakes", "kabal cake",
                 "kabal cakes"}),
        "cake",
        ({"kabal", "supreme"}),
        105,
        100,
        "Kabal supreme cake",
        "Kabal supreme cakes",
        "A huge cake made of fudge, with nuts, white cream filling, " +
                "and candy decorations.\n"
        );
    add_food(({"Kabal peasant bread", "Kabal peasant breads", "Kabal bread", 
                "Kabal breads", "peasant bread", "peasant breads", "bread",
                "breads", "kabal peasant bread", "kabal peasant breads",
                "kabal bread", "kabal breads"}),
        "bread",
        ({"kabal", "peasant"}),
        25,
        20,
        "Kabal peasant bread",
        "Kabal peasant breads",
        "A fair size loaf of wheat bread.\n"
        );
    add_food(({"deluxe rye bread", "deluxe rye breads"}),
        "bread",
        ({"deluxe", "rye"}),
        30,
        25,
        "deluxe rye bread",
        "deluxe rye breads",
        "A fair size loaf of rye bread.\n"
        );
    add_food(({"sweet bread", "sweet breads"}),
        "bread",
        "sweet",
        30,
        25,
        "sweet bread",
        "sweet breads",
        "A loaf of soft, honey-covered bread.\n"
        );
}

string
menu()
{
    return 
    "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n"+
    "@              KABAL BAKERY             @\n"+
    "@---------------------------------------@\n"+
    "@                                       @\n"+
    "@ Powder doughnut       -     10 cc     @\n"+
    "@ Jelly-filled doughnut -     12 cc     @\n"+
    "@ Cream cheese pastry   -     15 cc     @\n"+
    "@ Maple bar             -     15 cc     @\n"+
    "@ Chocolate chip cookie -     16 cc     @\n"+
    "@ Oatmeal cookie        -     16 cc     @\n"+
    "@ Cream puff            -     20 cc     @\n"+
    "@ Cream pie             -     22 cc     @\n"+
    "@ Lemon pie             -     22 cc     @\n"+
    "@ Carrot cake           -     30 cc     @\n"+
    "@ Chocolate cake        -     50 cc     @\n"+
    "@ Fudge cake            -     60 cc     @\n"+
    "@ Kabal supreme cake    -    100 cc     @\n"+
    "@ Kabal peasant bread   -     20 cc     @\n"+
    "@ Deluxe rye bread      -     25 cc     @\n"+
    "@ Sweet bread           -     25 cc     @\n"+
    "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
}

int
pub_hook_ordered_too_many(int num)
{
    notify_fail("You cannot buy more than 20 items at a time.\n");
    return 0;
}

public void
init()
{
    ::init();
    init_pub();
}

