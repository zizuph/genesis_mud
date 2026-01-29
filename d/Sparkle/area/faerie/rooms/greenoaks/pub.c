/*
 * Pub for Green Oaks
 * Based on the Prancing Pony Inn in Bree
 * -- Finwe, March 2005
 */
#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

inherit "/d/Shire/lib/inn";
inherit INDOORS_BASE;

#define PRICELIST_ID  ({"pricelist","list","prices", "menu"})

void add_stuff();

static object aralea;

 
void
create_indoor_room()
{
    add_prop(ROOM_S_MAP_FILE, "faerie_map.txt");
    set_short("Pub of Green Oaks");
    set_long("This is the Pub of Green Oaks. A wide counter stretches " +
        "across one wall. The pub is clean even with all the visitors " +
        "that come here. Chairs and tables scattered around the room " +
        "were patrons can sit and enjoy each other's company. A menu " +
        "is attached to a wall.\n"); 

    set_add_ceiling_flat("");
    add_item(({"counter"}),
        "It is a wide piece of polished wood. It is about waist high " +
        "and runs the width of the pub. Light scratches are visible " +
        "from items slid across the surface.\n");

    add_item(({"tables", "table", "round tables", "round table", 
            "round wooden tables", "round wooden table"}),
        "The tables are round and made of heavy oak. They are different " +
        "sizes and are scattered about the room. Scratches and dents are " +
        "visible on the table's surfaces. Chairs are set around the " +
        "tables.\n");

    add_item(({"chairs", "wooden chairs", "wooden chairs", "chair"}),
        "They are made of wood with high backs. They are set around " +
        "the table.\n");
    add_item(({"scratches", "dents"}),
        "They are shallow cuts and marks in the surface. Most likely " +
        "they are there from patrons who leaped on top of the tables " +
        "and danced. \n");

    add_exit(GO_DIR + "road15", "north");
    add_exit(GO_DIR + "road22", "southwest");

    add_item(PRICELIST_ID, "@@pricelist_desc");
    reset_room();
    configure_shire_inn();


}

void reset_room() 
{ 
    if (!aralea)
        aralea = clone_object(NPC_DIR + "pubkeeper");
        aralea->move(this_object());
}



void
add_stuff()
{

}


void
init()
{
    ::init();
    init_shire_inn();
    add_action("do_read", "read", 0);


}

string
pricelist_desc()
{
    return "\n" +
    "\t+--------------------------------------------+\n" +
    "\t|                                            |\n" +
    "\t|   Drinks                                   |\n" +
    "\t|   ======================================   |\n" +
    "\t|   Water . . . . . . . . . . . . .   6 cc   |\n" +
    "\t|   Fruit Tea . . . . . . . . . . .  12 cc   |\n" +
    "\t|   Nectar. . . . . . . . . . . . .  20 cc   |\n" +
    "\t|   Fresh Golden Mead . . . . . . .  40 cc   |\n" +
    "\t|                                            |\n" +
    "\t|   Food                                     |\n" +
    "\t|   ======================================   |\n" +
    "\t|   Sweet Bread . . . . . . . . . .  12 cc   |\n" +
    "\t|   Fresh Berries . . . . . . . . .  25 cc   |\n" +
    "\t|   Wild Nuts . . . . . . . . . . .  36 cc   |\n" +
    "\t|   Brick of Cheese . . . . . . . .  50 cc   |\n" +
    "\t|   Fresh Vegetables. . . . . . . .  70 cc   |\n" +
    "\t|                                            |\n" +
    "\t+--------------------------------------------+\n" +
"\n\n";
}

int
do_order(string str) 
{

    if (!aralea || !present(aralea))
    {
        notify_fail("There is no one here to buy anything from. The " +
            "pubkeeper is away for the time being.\n");
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
    case "water":
    case "waters":
    case "glass of water":
        order = clone_object(FOOD_DIR + "water");
        price = 6;
        break;
    case "tea":
    case "fruit tea":
    case "fruit teas":
    case "teas":
        order = clone_object(FOOD_DIR + "tea");
        price = 12;
        break;
    case "nectar":
    case "nectars":
        order = clone_object(FOOD_DIR + "nectar");
        price = 20;
        break;
    case "mead":
    case "fresh mead":
    case "fresh golden mead":
    case "meads":
    case "fresh meads":
    case "fresh golden meads":
        order = clone_object(FOOD_DIR + "mead");
        price = 40;
        break;
    case "bread":
    case "sweet bread":
    case "breads":
    case "sweet breads":
        order = clone_object(FOOD_DIR + "sbread");
        price = 12;
        break;
    case "berries":
    case "fresh berries":
        order = clone_object(FOOD_DIR + "berries");
        price = 25;
        break;
    case "nuts":
    case "wild nuts":
        order = clone_object(FOOD_DIR + "nuts");
        //price = 38;
        price = 36;
        break;
    case "cheese":
    case "brick of cheese":
    case "cheeses":
    case "bricks of cheese":
        order = clone_object(FOOD_DIR + "cheese");
        price = 50;
        break;
    case "vegetables":
    case "fresh vegetables":
        order = clone_object(FOOD_DIR + "vegetables");
        price = 70;
        break;
    }
    return (({order}) + ({price}));
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
