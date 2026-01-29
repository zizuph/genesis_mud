/*
 * Imladris Tack Shop (horse riding supplies)
 * Modified from Bree Tack Shop by Palmer
 * -- Finwe, January 2003
 */
inherit "/d/Shire/std/room";
inherit "/d/Shire/lib/inn";

#include "/d/Shire/sys/defs.h"
//#include "bree_stables.h"
#include "local.h"
#include <stdproperties.h>
#include <macros.h>
#include <money.h>

#define PRICELIST_ID  ({"pricelist","list","prices"})
#define BREE_STABLES_DIR "/d/Shire/bree/rooms/town/stable/"

/* Prototype */
void reset_shire_room();

static object eleithiel;

void
create_shire_room()
{
    set_short("The Tack shop of Imladris");
    set_long("This is the Tack Shop of Imladris. Elves come here to " +
        "purchase equipment needed for their steeds. Bridles, saddles " +
        "and other riding equipment sit on shelves on the walls and " +
        "above the counter. A sign is posted on the wall next to the " +
        "door.\n");
    add_item(({"saddle", "saddles"}),
        "Fine leather saddles sit on shelves on the wall. They are made " +
        "from the finest leather and are tooled exquisitely in fine " +
        "detail.\n");
    add_item(({"bridle", "bridles"}), 
        "A few leather bridles sit on shelves on the wall. They are " +
        "headgear which are worn over a horse's head, enabling the " +
        "rider to lead the horse or direct it when riding.\n");
    add_item(({"equipment", "riding equipment"}), 
        "They are leather saddles and bridles which sit on shelves on " +
        "the wall.\n");
    add_item(({"ground", "floor"}), 
        "The stone floor is smooth and clean.\n");
    add_item(({"shelves", "shelf"}), 
        "Large wooden shelves with riding equipment sitting on them.\n");
    add_item("ceiling", 
        "The ceiling is made of rough hewn beams.\n");
    add_item("counter", 
        "The counter runs the width of the shop. It is wide and made of " +
        "one piece of wood. It has knicks and scratches on the surface " +
        "from where heavy items have been dropped and dragged across it.\n");
    add_item(({"walls", "wall"}), 
        "The walls are simple, made of wood with a sign on one.\n");
//  add_item(({"sign", "poster"}), 
//      "There is some writing on it. Maybe you should read it.\n");
    add_cmd_item("sign", "read", "@@pricelist_desc@@");
//  add_cmd_item("poster", "read", "@@poster_desc@@");

    add_prop(ROOM_I_INSIDE,1);
    add_exit(VALLEY_DIR + "stable", "east");

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
        "\t|   o                                            o   |\n"+
        "\t|      T A C K   S H O P   O F   I M L A D R I S     |\n"+
        "\t|    --------------------------------------------    |\n"+
        "\t|                                                    |\n"+
        "\t|    Below are the items sold here. They are sold by |\n"+
        "\t|    Eleithiel by he will not purchase them back.    |\n"+
        "\t|                                                    |\n"+
        "\t|    Saddlebag. . . . . . . . . .  12 g  6 sc        |\n"+
        "\t|      Spacious, rugged, all-leather saddlebag used  |\n"+
        "\t|      to carry supplies for the rider.              |\n"+
        "\t|    Ankle bells. . . . . . . . .    1g  6 sc        |\n"+
        "\t|      Bells attached to horses ankles that jingle   |\n"+
        "\t|      when the horse travels.                       |\n"+
        "\t|                                                    |\n"+
        "\t|    Food Supplies                                   |\n"+
        "\t|    ----------------------------------------------  |\n"+
        "\t|    Apple. . . . . . . . . . . .        5 sc        |\n"+
        "\t|    Basket of apples . . . . . .        5 gc        |\n"+
        "\t|    Sugar cube . . . . . . . . .        1 sc        |\n"+
        "\t|    Bag of sugar cubes . . . . .        1 gc        |\n"+
        "\t|    Bag of oats. . . . . . . . .        5 sc        |\n"+
        "\t|    Bundle of hay. . . . . . . .        5 gc        |\n"+
        "\t+----------------------------------------------------+\n\n";
}


// Poster
/*
string
poster_desc()
{
    return "\n"+
        "\t+-----------------------------------------------+\n"+
        "\t|                                               |\n"+
        "\t|   *                                       *   |\n"+
        "\t|     Saddlebag commands:                       |\n"+
        "\t|     --------------------------------------    |\n"+
        "\t|     drape saddlebag on horse                  |\n"+
        "\t|     remove saddlebag from horse               |\n"+
        "\t|     fill saddlebag on horse                   |\n"+
        "\t|     open saddlebag on horse                   |\n"+
        "\t|     close saddlebag on horse                  |\n"+
        "\t|     empty saddlebag on horse                  |\n"+
        "\t|                                               |\n"+
        "\t|   *                                       *   |\n"+
        "\t|                                               |\n"+
        "\t+-----------------------------------------------+\n\n";
}
*/

void
reset_shire_room()
{

    if (!eleithiel)
        eleithiel = clone_object(RNPC_DIR + "eleithiel");
    if (!present(eleithiel,this_object()))
        eleithiel->move(this_object());

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
    if (!eleithiel || !present(eleithiel))
    {
        notify_fail("There is no one here to buy anything from. The " +
            "lorimer has left to get more supplies.\n");
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
        order = clone_object(ROBJ_DIR + "saddlebag");
        price = 450;
        break;
    case "bells":
    case "horse bells":
    case "horsebells":
    case "ankle bells":
    case "anklebells":
        order = clone_object(BREE_STABLES_DIR + "obj/bells");
        price = 5;
        break;

    case "bag of oats":
    case "oats":
    case "bags of oats":
        order = clone_object(BREE_STABLES_DIR + "obj/oats_bag");
        price = 72;
        break;

    case "sugar":
    case "sugarcube":
    case "sugar cube":
    case "sugars":
    case "sugarcubes":
    case "sugar cubes":
        order = clone_object(BREE_STABLES_DIR + "obj/sugar");
        price = 12;
        break;

    case "bag of sugarcubes":
    case "bag of sugar cubes":
    case "bags of sugarcubes":
    case "bags of sugar cubes":

        order = clone_object(BREE_STABLES_DIR + "obj/sugar_bag");
        price = 144;
        break;

    case "basket of apples":
    case "basketS of apples":
        order = clone_object(BREE_STABLES_DIR + "obj/apple_basket");
        price = 720;
        break;

    case "apple":
    case "apples":

        order = clone_object(FRUIT_DIR + "apple");
        price = 72;
        break;

    case "bundle of hay":
    case "bundle":
    case "hays":
    case "hay":
        order = clone_object(BREE_STABLES_DIR + "obj/hay");
        price = 720; // 5 gold
        break;


    }
    return (({order}) + ({price}));
}