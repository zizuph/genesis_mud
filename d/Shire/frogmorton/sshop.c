/*
 * Frogmorton Supply Shop
 * Modified the Holiday shop of Bree. Only sells things
 * -- Finwe, February 2003
 */
inherit "/d/Shire/std/room";
inherit "/d/Shire/lib/inn";

#include "defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <money.h>

#define PRICELIST_ID  ({"pricelist","list","prices"})
#define OBJ_DIR "/d/Shire/frogmorton/obj/"
#define STAND_OBJ "/d/Shire/common/obj/"
#define GONDOR_STAND "/d/Gondor/common/obj/"

/* Prototype */
void reset_shire_room();

static object rosie ;

void
create_shire_room()
{
    set_short("The Frogmorton Supply Shop");
    set_long("This is the Frogmorton Supply Shop. Many hobbits come " +
        "here to pick up supplies from around the Shire for when they " + 
        "pass through. The Watch especially pick up things here before " +
        "they travel about the land. Only items may be purchased here. " +
        "A sign is posted on one wall.\n");
    add_item("counter", "It's made out of wood. There is a hobbit standing "+
      "behind it.\n");
    add_item("walls", 
        "The walls are simple, made of wood with a sign on one.\n");
    add_item(({"floor", "ground",}),
        "The ground is swept clean and looks spotless.");
    add_item(({"up", "ceiling"}),
        "The ceiling is flat and plain looking.");
//    add_item(PRICELIST_ID, "@@pricelist_desc");
    add_cmd_item("sign", "read", "@@pricelist_desc@@");


    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_NO_ALLOW_STEED, 1);
    add_exit(FROG_DIR + "shop","down");

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
        "\t|               Frogmorton Supply Shop               |\n"+
        "\t|                                                    |\n"+
        "\t|    Supplies you may purchase are listed below. As  |\n"+
        "\t|    demand changes, so will the items below:        |\n"+
        "\t|                                                    |\n"+
        "\t|    A shoulder bag . . . . . . 2 gc  2 sc  1 cc     |\n"+
        "\t|    Useful for carrying things as you travel.       |\n"+ 
        "\t|                                                    |\n"+
        "\t|    A leather pouch. . . . . .      8 sc   7 cc     |\n"+
        "\t|    Designed to hold herbs collected.               |\n"+
        "\t|                                                    |\n"+
        "\t|    A pair of herbing gloves .       6 sc 10 cc     |\n"+
        "\t|    Gloves to protect your fingers while herbing.   |\n"+
        "\t|                                                    |\n"+
        "\t|    A iron lamp. . . . . . . . 2 gc  0 sc  0 cc     |\n"+
        "\t|    A lamp to see in the dark.                      |\n"+
        "\t|                                                    |\n"+
        "\t|    A flask of oil . . . . . . 2 gc  8 sc  0 cc     |\n"+
        "\t|    Used with lamps.                                |\n"+
        "\t|                                                    |\n"+
        "\t|    A herb wrap  . . . . . . .       3 sc  0 cc     |\n"+
        "\t|    A strip of cloth to wrap herbs together with.   |\n"+
        "\t|                                                    |\n"+
        "\t|    A brown cloak. . . . . . .                      |\n"+
        "\t|    A nice travel cloak                             |\n"+
        "\t|                                                    |\n"+
        "\t|    A glass bottle . . . . . . 1 gc  0 sc  6 cc     |\n"+
        "\t|    A green square glass bottle to hold drinks.     |\n"+
        "\t|                                                    |\n"+
        "\t+----------------------------------------------------+\n\n";
}



void
reset_shire_room()
{
    if (!rosie)
        rosie = clone_object(FNPC_DIR + "rosie");
    if (!present(rosie,this_object()))
        rosie->move(this_object());

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
    if (!rosie || !present(rosie))
    {
        notify_fail("There is no one here to buy anything from. " +
          "The shopkeeper has left to get more supplies.\n");
        return 0;
    }
    return ::do_order(str);
}

/*******************************************************************************
 * Shop Items
 *******************************************************************************/

mixed *
get_order(string item_name)
{
    object order;
    int price;

    setuid(); seteuid(getuid());
    switch (item_name)
    {
    case "pack":
    case "packs":
    case "shoulder bag":
    case "shoulder bags":
        order = clone_object(STAND_OBJ + "shoulderbag");
        price = 313;
        break;
    case "pouch":
    case "pouches":
    case "leather pouch":
    case "leather pouches":
        order = clone_object(STAND_OBJ + "pouch");
        price = 103;
        break;
    case "gloves":
    case "pair of gloves":
    case "pairs of gloves":
    case "pair of leather gloves":
    case "pairs of leather gloves":
        order = clone_object(OBJ_DIR + "herb_gloves");
        price = 82;
        break;
    case "lamp":
    case "lamps":
    case "iron lamp":
    case "iron lamps":
        order = clone_object(GONDOR_STAND + "oil_lamp");
        price = 288;
        break;
    case "flask":
    case "flasks":
    case "oil":
    case "oils":
    case "flask of oil":
    case "flasks of oil":
        order = clone_object(GONDOR_STAND + "oilflask");
        price = 144;
        break;
    case "wrap":
    case "wraps":
    case "herb wrap":
    case "herb wraps":
        order = clone_object(OBJ_DIR + "");
        price = 36;
        break;
    case "bottle":
    case "bottles":
    case "square bottle":
    case "square bottles":
    case "green square bottle":
    case "green square bottles":
        order = clone_object(OBJ_DIR + "");
        price = 200;
        break;
    
    }
    return (({order}) + ({price}));
}

