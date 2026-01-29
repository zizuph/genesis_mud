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

#define PRICELIST_ID  ({"pricelist","list","prices", "menu", "wine list"})

void add_stuff();

static object isenrain;

 
void
create_indoor_room()
{
    add_prop(ROOM_S_MAP_FILE, "faerie_map.txt");
    set_short("Winery of Green Oaks");
    set_long("This is the " + short() + ". A fruity aroma fills the air. " +
        "The room is separated by a wide wooden counter. Behind the " +
        "counter are shelves holding bottles of wine available. Posted " +
        "on the wall is a wine list.\n"); 

    set_add_ceiling_flat("");
    add_item(({"counter"}),
        "It is a wide piece of polished wood. It is about waist high and " +
        "runs the width of the winery. It is dark brown and clean.\n");
    add_item(({"polished wood", "wood", "dark brown wood"}),
        "The wood is very wide and polished to a deep color. It is free " +
        "of scratches and looks like it has been taken care of.\n");
    add_item(({"shelves", "wooden shelves"}),
        "They are made of sturdy wood planks and secured to the wall " +
        "behind the counter. On the shelves are wine racks which hold " +
        "many wine bottles\n");
    add_item(({"rack", "wine racks"}),
        "They are individual compartments built into the shelves behind " +
        "the counter. There are lots of them and they look well used. " +
        "They hold bottles of wine on their sides.\n");
    add_item(({"compartments"}),
        "They hold bottles of wine on the wine racks.\n");
    add_item(({"wood planks", "planks"}),
        "They are lengths of wood used to make the wine racks.\n");
    add_item(({"bottles", "wine bottles"}),
        "They are made of glass and are dark colored. The bottles are " +
        "stored in the wine racks behind the counter.\n");
    add_item(({"wine", "wines"}),
        "It's an alcoholic drink made from fruits. Many wines are for " +
        "sale here in the winery. See the wine list for more details.\n");
    
    

    add_exit(GO_DIR + "road10", "south");

    add_item(PRICELIST_ID, "@@pricelist_desc");
    reset_room();
    configure_shire_inn();


}

void reset_room() 
{ 

    if (!isenrain)
        isenrain = clone_object(NPC_DIR + "vintner");
        isenrain->move(this_object());

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
    "\t|   Winelist                                 |\n" +
    "\t|   ======================================   |\n" +
    "\t|   Apple . . . . . . . . . . . . .  70 cc   |\n" +
    "\t|   - Made with fresh apples with a cool,    |\n" +
    "\t|     crisp taste                            |\n" +
    "\t|   Wild Berry. . . . . . . . . . .  80 cc   |\n" +
    "\t|   - An intense tasting wine made with      |\n" +
    "\t|     combinations of wild fruits            |\n" +
    "\t|   Elderberry . .  . . . . . . . . 120 cc   |\n" +
    "\t|   - Favored by elves, this is one of       |\n" +
    "\t|     the strongest wines available          |\n" +
    "\t|   Plum . .  . . . . . . . . . . .  90 cc   |\n" +
    "\t|   - Distilled from fresh plum with a       |\n" +
    "\t|     hint of almond taste                   |\n" +
    "\t|   Raspberry . . . . . . . . . . .  80 cc   |\n" +
    "\t|   - This sweet tasting wine sparkles       |\n" +
    "\t|     with a ruby red color                  |\n" +
    "\t|   Strawberry. . . . . . . . . . .  85 cc   |\n" +
    "\t|   - Sweet smelling, this rose colored      |\n" +
    "\t|     wine comes from wild strawberries      |\n" +
    "\t|   Wild Flower. . . . . . . . . . . 90 cc   |\n" +
    "\t|   - A combination of wild flowers make     |\n" +
    "\t|     up this unique tasting wine            |\n" +
    "\t|                                            |\n" +
    "\t+--------------------------------------------+\n" +
    "\n\n";
}

int
do_order(string str) 
{

    if (!isenrain || !present(isenrain))
    {
        notify_fail("There is no one here to buy anything from. The " +
            "vintner is gone for a few minutes.\n");
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
    case "apple wine":
    case "apple wines":
    case "apple":
    case "apples":
        order = clone_object(FOOD_DIR + "wine_apple");
        price = 70;
        break;
    case "wild berry wine":
    case "wild berry wines":
    case "wild berry":
    case "wild berries":
        order = clone_object(FOOD_DIR + "wine_berry");
        price = 80;
        break;
    case "elderberry wine":
    case "elderberry wines":
    case "elderberry":
    case "elderberries":
        order = clone_object(FOOD_DIR + "wine_elder");
        price = 120;
        break;
    case "plum wine":
    case "plum wines":
    case "plum":
    case "plums":
        order = clone_object(FOOD_DIR + "wine_plum");
        price = 90;
        break;
    case "raspberry wine":
    case "raspberry wines":
    case "raspberry":
    case "raspberries":
        order = clone_object(FOOD_DIR + "wine_raspberry");
        price = 80;
        break;
    case "strawberry wine":
    case "strawberry wines":
    case "strawberry":
    case "strawberries":
        order = clone_object(FOOD_DIR + "wine_straw");
        price = 85;
        break;
    case "wild flower wine":
    case "wild flower wines":
    case "wild flower":
    case "wild flowers":
        order = clone_object(FOOD_DIR + "wine_wild");
        price = 90;
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
