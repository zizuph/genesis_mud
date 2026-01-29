/*
 * Leather shop for Faerie
 * Modified from Bree inn
 * Only sells things, does not buy anything
 * -- Finwe, April 2005
 */

#pragma strict_types

#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

inherit INDOORS_BASE;
inherit "/d/Shire/lib/inn";

#define PRICELIST_ID    ({"pricelist","list","prices", "sign"})

static object ingvane;

//void add_stuff();

void
create_indoor_room()
{
    setuid(); seteuid(getuid());

    string boots_descr = "/d/Sparkle/area/faerie/arm/sh_lboot.c"->query_long();
    string cloak_descr = "/d/Sparkle/area/faerie/arm/sh_lcloak.c"->query_long();
    string hat_descr = "/d/Sparkle/area/faerie/arm/sh_lhat.c"->query_long();
    string sandals_descr = "/d/Sparkle/area/faerie/arm/sh_lsandals.c"->query_long();
    string shoes_descr = "/d/Sparkle/area/faerie/arm/sh_lshoes.c"->query_long();
    string skirt_descr = "/d/Sparkle/area/faerie/arm/sh_lskirt.c"->query_long();
    string slippers_descr = "/d/Sparkle/area/faerie/arm/sh_lslippers.c"->query_long();
    string vest_descr = "/d/Sparkle/area/faerie/arm/sh_lvest.c"->query_long();
    string scab_s_descr = "/d/Sparkle/area/faerie/arm/sh_scab_s.c"->query_long();

    set_short("Leather Shop of Green Oaks");
    set_long("You are in the " + short() + ". It is wide and clean. " +
        "A large wooden counter stretches along the back wall. Leather " +
        "items are spread around the shop. Behind the counter hang " +
        "leather items for sale. A sign hangs on the wall.\n");

    set_add_ceiling_flat("The ceiling is white and undecorated.");
    add_item(({"dummy", "clothes dummy", "mannequin"}),
        "They are life-size figures of elves. They are used for displaying " +
        "clothes.\n");
    add_item(({"boots", "pair of leather boots", "leather boots"}),
       "They are set on a shelf behind the counter. Beneath the boots " +
       "is a plaque that describes them. It reads: " + boots_descr + "\n");
    add_item(({"cloak"}),
        "It id draped over a mannequin and looks nice. Next to it is " +
        "a plaque. It reads: " + cloak_descr +"\n");
    add_item(({"hat", "cowhide hat"}),
        "It hangs on a hook behind the counter. Beside the hook is a " +
        "plaque. It reads: " + hat_descr +"\n");
    add_item(({"sandals", "pair of sandals", "pair of leather sandals"}),
        "The sandals sit on a shelf behind the counter. Under it is " +
        "a plaque. It reads: " + sandals_descr +"\n");
    add_item(({"black shoes", "pair of black shoes"}),
        "They are aranged neatly on a shelf. Beneath the shelf is a " +
        "plaque. It reads: " + shoes_descr +"\n");
    add_item(({"skirt", "cowhide skirt"}),
        "It is draped on a mannequin behind the counter. Alongside " +
        "it is a plaque. It reads: " + skirt_descr +"\n");
    add_item(({"vest", "cowhide vest"}),
        "It is on a mannequin behind the counter. Next to it is a " +
        "plaque. It reads: " + vest_descr +"\n");
    add_item(({"scabbard", "sword scabbard"}),
        "It is propped up on a shelf behind the counter. Below the " +
        "shelf is a plaque. It reads: " + scab_s_descr +"\n");
    add_item(({"slippers", "pair of slippers"}),
        "They are arranged behind the counter on a shelf. On the shelf " +
        "is a plaque. It reads: " + slippers_descr +"\n");
    add_item(({"shelves", "wooden shelves"}),
        "They are behind the counter and made of wood. On the shelves " +
        "are exhibits of leather items you may purchase here.\n");
    add_item(({"exhibits"}),
        "They are leather items for sale. They are behind the counter " +
        "on shelves and mannequins. There are vests, shoes, sandals " +
        "and other things mentioned on the sign.\n");


    add_exit(GO_DIR + "road14", "west");
    add_item(PRICELIST_ID, "@@pricelist_desc");
    configure_shire_inn();

}
void reset_room()
{

    if(!present(ingvane))
    {
        ingvane = clone_object(NPC_DIR + "tanner");
        ingvane->move(TO);
    }
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
    "\t|       L E A T H E R   S H O P   O F        |\n" +
    "\t|            G R E E N   O A K S             |\n" +
    "\t|                                            |\n" +
    "\t|  Welcome to the Shop. We are proud to      |\n" +
    "\t|  offer you the best leather products any-  |\n" +
    "\t|  where. Be sure to look at the mannequins  |\n" +
    "\t|  for description of each item available    |\n" +
    "\t|  before you purchase it. We only sell      |\n" +
    "\t|  things here, and don't purchase them back |\n" +
    "\t|  if you made a wrong choice.               |\n" +
    "\t|                                            |\n" +
    "\t|   Clothing                                 |\n" +
    "\t|   ======================================   |\n" +
    "\t|   Dark Travellers Cloak . . . . . 300 cc   |\n" +
    "\t|   Cowhide Skirt . . . . . . . . . 150 cc   |\n" +
    "\t|   Cowhide Hat . . . . . . . . . .  75 cc   |\n" +
    "\t|   Cowhide Vest. . . . . . . . . . 125 cc   |\n" +
    "\t|   Leather Boots . . . . . . . . . 100 cc   |\n" +
    "\t|   Leather Sandals . . . . . . . .  80 cc   |\n" +
    "\t|   Black Shoes . . . . . . . . . .  90 cc   |\n" +
    "\t|   Slippers. . . . . . . . . . . .  50 cc   |\n" +
    "\t|                                            |\n" +
    "\t|   Miscellaneous                            |\n" +
    "\t|   ======================================   |\n" +
    "\t|   Backpack. . . . . . . . . . . . 432 cc   |\n" +
    "\t|   Sword Scabbard. . . . . . . . . 300 cc   |\n" +
    "\t|   Herb Pouch. . . . . . . . . . . 100 cc   |\n" +
    "\t|   Herbing Gloves. . . . . . . . . 110 cc   |\n" +
    "\t|   Money Purse . . . . . . . . . . 120 cc   |\n" +
    "\t|                                            |\n" +
    "\t+--------------------------------------------+\n" +
"\n\n";
}

int
do_order(string str)
{

    if (!ingvane || !present(ingvane))
    {
        notify_fail("There is tanner is gone, getting more supplies. " +
            "He should be back shortly.\n");
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
    case "cloak":
    case "cloaks":
    case "dark travellers cloak":
    case "dark travellers cloaks":
    case "travellers cloak":
    case "travellers cloaks":
        order = clone_object(ARM_DIR + "sh_lcloak");
        price = 300;
        break;
    case "skirt":
    case "skirts":
    case "cowhide skirt":
    case "cowhide skirts":
        order = clone_object(ARM_DIR + "sh_lskirt");
        price = 150;
        break;
    case "hat":
    case "hats":
    case "cowhide hat":
    case "cowhide hats":
        order = clone_object(ARM_DIR + "sh_lhat");
        price = 75;
        break;
    case "vest":
    case "vests":
    case "cowhide vest":
    case "cowhide vests":
        order = clone_object(ARM_DIR + "sh_lvest");
        price = 125;
        break;
    case "boots":
    case "pair of boots":
    case "pair of leather boots":
    case "leather boots":
    case "pairs of leather boots":
        order = clone_object(ARM_DIR + "sh_lboot");
        price = 100;
        break;
    case "sandals":
    case "leather sandals":
    case "pair of leather sandals":
    case "pairs of leather sandals":
        order = clone_object(ARM_DIR + "sh_lsandals");
        price = 80;
        break;
    case "shoes":
    case "black shoes":
    case "pair of black shoes":
    case "pairs of black shoes":
        order = clone_object(ARM_DIR + "sh_lshoes");
        price = 90;
        break;
    case "slippers":
    case "pairs of slippers":
    case "pair of leather slippers":
    case "pairs of leather slippers":
    case "pair of slippers":
        order = clone_object(ARM_DIR + "sh_lslippers");
        price = 50;
        break;
    case "backpack":
    case "backpacks":
    case "leather backpack":
    case "leather backpacks":
    case "soft leather backpack":
    case "soft leather backpacks":
    case "soft backpack":
    case "soft backpacks":
        order = clone_object(OBJ_DIR + "backpack");
        price = 432;
        break;

    case "scabbard":
    case "scabbards":
    case "sword scabbard":
    case "sword scabbards":
        order = clone_object(ARM_DIR + "sh_scab_s");
        price = 300;
        break;
    case "pouch":
    case "pouches":
    case "herb pouch":
    case "herb pouches":
    case "leather pouches":
    case "leather pouches":

        order = clone_object(SHOBJ_DIR + "herb_pouch");
        price = 100;
        break;

    case "gloves":
    case "herbing gloves":
    case "pair of herbing gloves":
    case "pairs of herbing gloves":
        order = clone_object(FROGOBJ_DIR + "herb_gloves");
        price = 110;
        break;
    case "purse":
    case "purses":
    case "money purse":
    case "money purses":
        order = clone_object(OBJ_DIR + "purse");
        price = 120;
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
