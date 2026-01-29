/*
 * Bree Tack Shop (horse riding supplies)
 * Modified from Finwe's Holiday shop, Only sells things, does not buy anything
 * -- Palmer, December 2002
 */
inherit "/d/Shire/std/room";
inherit "/d/Shire/lib/inn";

#include "/d/Shire/defs.h"
#include "bree_stables.h"
#include <stdproperties.h>
#include <macros.h>
#include <money.h>

#define PRICELIST_ID  ({"pricelist","list","prices"})

/* Prototype */
void reset_shire_room();

static object kalrin;

void
create_shire_room()
{
    set_short("The Bree Tack Shop");
    set_long("You have entered Bree's Tack Shop. A strong smell " +
        "of leather permeates the room. Saddles, bridles and other " +
        "riding equipment sit on shelves on the wall above the counter. A sign is posted on one wall, " +
        "and a poster on another.\n");
    add_item(({"saddle", "saddles"}), "Fine leather saddles sit on shelves on the wall.\n");
    add_item(({"bridle", "bridles"}), "A few leather bridles sit on shelves on the wall.\n");
    add_item(({"equipment", "riding equipment"}), "Leather saddles and bridles sit on shelves on the wall.\n");
    add_item(({"chair", "chairs"}), "The chairs are made out of wood.\n");
    add_item(({"ground", "floor"}), "The stone floor is smooth and clean.\n");
    add_item(({"shelves", "shelf"}), "Large wooden shelves with riding equipment sitting on them.\n");
    add_item("ceiling", "The ceiling is made of rough hewn beams.\n");
    add_item("counter", "The counter runs the width of the shop. It is wide and made of one piece of wood. " +
            "The counter has knicks and scratches on its surface from where heavy items have " +
            "been dropped and dragged across it.\n");
    add_item(({"walls", "wall"}), "The walls are simple, made of wood with a sign on one.\n");
    add_item(({"sign", "poster"}), "There is some writing on it. Maybe " +
        "you should read it.\n");
    add_cmd_item("sign", "read", "@@pricelist_desc@@");
    add_cmd_item("poster", "read", "@@poster_desc@@");

    add_prop(ROOM_I_INSIDE,1);
    add_exit("stable_yard.c","north");

    set_alarm(1.0, 0.0, reset_shire_room);
    configure_shire_inn();
    add_prop(ROOM_I_NO_CLEANUP,1);
}

// Sign
string
pricelist_desc()
{
    return "\n"+
        "\t+----------------------------------------------------+\n"+
        "\t|                                                    |\n"+
        "\t|   *                                            *   |\n"+
        "\t|                 Bree Tack Shop                     |\n"+
        "\t|                                                    |\n"+
        "\t|    Below are the items sold here. Items cannot be  |\n"+
        "\t|    returned or sold back here                      |\n"+
        "\t|                                                    |\n"+
        "\t|    ============================================    |\n"+
        "\t|    Saddlebag . . . . . . . . . .  12 g 6 sc        |\n"+
        "\t|    Spacious, rugged, all-leather.                  |\n"+
        "\t|                                                    |\n"+
        "\t|    Ankle bells. . . . . . . . .    1g  6 sc        |\n"+
        "\t|    Heavy duty bells to make your horse jingle      |\n"+
        "\t|    ============================================    |\n"+
        "\t|                                                    |\n"+
        "\t|    Apple. . . . . . . . . . . .        5 sc        |\n"+
        "\t|    Basket of apples . . . . . .        2 gc        |\n"+
        "\t|    Sugar cube . . . . . . . . .        1 sc        |\n"+
        "\t|    Bag of sugar cubes . . . . .        1 gc        |\n"+
        "\t|    Bag of oats. . . . . . . . .        5 sc        |\n"+
        "\t|    Bundle of hay. . . . . . . .        1 gc        |\n"+
        "\t|    Bale of hay. . . . . . . . .        6 gc        |\n"+
        "\t+----------------------------------------------------+\n\n";
}


// Poster
string
poster_desc()
{
    return "\n"+
        "\t+----------------------------------------------------+\n"+
        "\t|                                                    |\n"+
        "\t|   *                                            *   |\n"+
        "\t|                                                    |\n"+
        "\t|     Don't forget to feed your steed!               |\n"+
        "\t|                                                    |\n"+
        "\t|     Saddlebag commands:                            |\n"+
        "\t|                                                    |\n"+
        "\t|     strap saddlebag on horse/pony                  |\n"+
        "\t|     unstrap saddlebag on horse/pony                |\n"+
        "\t|     fill saddlebag on horse/pony                   |\n"+
        "\t|     open saddlebag on horse/pony                   |\n"+
        "\t|     close saddlebag on horse/pony                  |\n"+
        "\t|     empty saddlebag on horse/pony                  |\n"+
        "\t|     hpack (see contents of pack)                   |\n"+
        "\t|   *                                            *   |\n"+
        "\t|                                                    |\n"+
        "\t+----------------------------------------------------+\n\n";
}


void
reset_shire_room()
{

    if (!kalrin)
        kalrin = clone_object(BREE_STABLES_DIR + "npc/kalrin");
    if (!present(kalrin,this_object()))
        kalrin->move(this_object());

}

void
init()
{
    ::init();
    init_shire_inn();
}

int
do_read(string str)
{
    if (!str)
        return 0;
    if (member_array(str, PRICELIST_ID) == -1)
        return 0;
    write(pricelist_desc());
    return 1;
}

int
do_order(string str)
{
    if (!kalrin || !present(kalrin))
    {
        notify_fail("There is no one here to buy anything from. " +
          "The shopkeeper has left to get more supplies.\n");
        return 0;
    }
    return ::do_order(str);
}


mixed *
get_order(string item_name)
{
    object order;
    int price;

    setuid(); seteuid(getuid());
    switch (item_name)
    {
    case "saddlebag":
    case "saddlebags":
        order = clone_object(BREE_STABLES_DIR + "obj/saddlebag");
// price 450
        price = 1800;
        break;
    case "bells":
    case "horse bells":
    case "horsebells":
    case "ankle bells":
    case "anklebells":
        order = clone_object(BREE_STABLES_DIR + "obj/bells");
        price = 216;
// price = 5;
        break;

    case "bag of oats":
    case "bags of oats":
    case "oats":
        order = clone_object(BREE_STABLES_DIR + "obj/oats_bag");
        price = 60;
//price = 72;
        break;

    case "sugar":
    case "sugarcube":
    case "sugar cube":
    case "sugarcubes":
    case "sugar cubes":

        order = clone_object(BREE_STABLES_DIR + "obj/sugar");
        price = 12;
//price = 12;
        break;

    case "bag of sugarcubes":
    case "bag of sugar cubes":
    case "bags of sugarcubes":
    case "bags of sugar cubes":

        order = clone_object(BREE_STABLES_DIR + "obj/sugar_bag");
        price = 144;
        break;

    case "basket of apples":
    case "baskets of apples":
        order = clone_object(BREE_STABLES_DIR + "obj/apple_basket");
        price = 288;
//price = 36;
        break;

    case "apple":   
    case "apples":
    order = clone_object("/d/Shire/bree/food/apple");
        price = 60;
//price = 72;
        break;

    case "bundle of hay":
    case "bundles of hay":
        order = clone_object(BREE_STABLES_DIR + "obj/hay");
         price = 144; 
//price = 36; // 1 gold
        break;

    case "bale of hay":
    case "bale":
    case "bales of hay":
    case "bales":
        order = clone_object(BREE_STABLES_DIR + "obj/hay_bale");
         price = 864; 
//price = 36; // 1 gold
        break;



    }
    return (({order}) + ({price}));
}
