/*
 * Nov hut to sell foods and drinks
 * -- Finwe, November 2007
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <macros.h>
#include <money.h>
#include <stdproperties.h>
#include <terrain.h>

inherit FAERUN_INDOORS_BASE;
inherit "/d/Shire/lib/inn";

#define PRICELIST_ID  ({"pricelist","list","prices", "menu"})

#define FIREKNIVES_MASTER "/d/Faerun/guilds/fire_knives/master/occ_fireknives_master"

#define VAMP_NPC_DIR  "/d/Faerun/guilds/vampires/npc/"

static object hut_npc;

public int
block_check()
{
    if (FIREKNIVES_MASTER->is_occ_fireknife(this_player()->query_name()) == 0 
    && FIREKNIVES_MASTER->is_crow(this_player()->query_name()) == 0)
    {
        if (!this_player()->query_wiz_level())
        {
            write("The withered old human blocks you "
			+"from going in there!\n");
			
            return 1;
        }
    }
	
	return 0;
}


void
create_indoor_room()
{
    add_prop(ROOM_S_MAP_FILE, "sword_mt_map.txt");

    set_short("inside a small hut");
    set_extraline("The wooden walls have chinks in them where the wind whistles through, and provides some light. Dead animals and a single lamp hang from the ceiling. Some shelves line one wall, and a menu is attached to another.");

    add_item(({"walls"}),
        "They are made of wood stacked on top of each other. There are chinks in the walls where cold air blows through. The walls look sturdy and have some shelves against them. There is a menu on another wall.\n");
    add_item(({"roof", "ceiling"}),
        "The ceiling is peaked and supported by strong beams. Hanging from the beams is a single lamp and some dead animals.\n");
    add_item(({"beams"}),
        "They are squared logs and support the ceiling. Hanging from the beams is a single lamp and some dead animals.\n");
    add_item(({"logs", "squared logs"}),
        "They are large and were hauled up here from the mountains. They are square and support the ceiling.\n");
    add_item(({"animals", "dead animals"}),
        "These are animals that have been hunted and are now curing, ready to be eaten. They hang from the beams above.\n");
    add_item(({"lamp"}),
        "The lamp hangs from the ceiling, casting a warm glow around the room. The lamp is large and and unusually bright.\n");
    add_item(({"stove"}),
        "It sits in one corner of the room. The stove is the only source of heat in the hut. It warms the room and used to cook food.\n");
    add_item(({"pots", "pans", "pots and pans"}),
        "They sit on the stove, bubbling and cooking various foods. They fill the room with a warm fragrance.\n");
    add_item(({"shelves"}),
        "The shelves are set against the wall. They hold various items for the lady living here.\n");
    add_item(({"floor", "ground"}),
        "The floor is swept clean. It is made of hard-packed dirt and is oddly warm.\n");

    add_prop(ROOM_I_NO_ALLOW_STEED, 1);
    add_item(PRICELIST_ID, "@@pricelist_desc");

    set_room_tell_time(300);
    add_room_tell("The lamp swings overhead, casting shadows around the room.");
    add_room_tell("Something pops in a pan on the stove.");
    add_room_tell("Something bubbles in a pot on the stove.");
    add_room_tell("A cold breeze blows through a chink in the walls.");


    configure_shire_inn();

    add_exit(HR_DIR + "htr14", "southwest");
	add_exit(HR_DIR + "crows", "north", block_check);
    add_exit(HR_DIR + "backroom", "east");
    
    add_npc(VAMP_NPC_DIR + "van_henriksen", 1);

    reset_faerun_room();
}

string
pricelist_desc()
{
    return "\nDrinks:\n"+
    "    A glass of water. . . . . . . . .  5 cc\n"+
    "    A cup of tea. . . . . . . . . . .  20 cc\n"+
    "    A glass of cider. . . . . . . . .  20 cc\n"+
    "    A pint of beer. . . . . . . . . .  80 cc\n"+
    "    A glass of white wine . . . . . . 180 cc\n"+
    "\nFood:\n"+
    "    A hard-boiled quail egg . . . . .  50 cc\n"+
    "    A smoked sausage. . . . . . . . .  75 cc\n"+
    "    Squirrel stew. .  . . . . . . . . 100 cc\n"+
    "    Roasted pheasant. . . . . . . . . 160 cc\n\n";
}

void
reset_faerun_room()
{
    if (!hut_npc)
        hut_npc = clone_object(NPC_DIR + "hut_food");
    if (!present(hut_npc,this_object()))
        hut_npc->move(this_object());
}

void
init()
{
    ::init();
    init_shire_inn();
    add_action("do_read", "read", 0);
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

    if (!hut_npc || !present(hut_npc))
    {
        notify_fail("There is no one here to buy anything from.\n"+
          "She is gone for now.\n");
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
// drinks
    case "water":
    case "waters":
    case "glass of water":
    case "glasses of water":
        order = clone_object(FOOD_DIR + "water");
        price = 5;
        break;
    case "beer":
    case "pint of beer":
    case "pints of beer":
    case "beers":
        order = clone_object(FOOD_DIR + "beer");
        price = 80;
        break;
    case "tea":
    case "cup of tea":
    case "cups of tea":
    case "cup of teas":
        order = clone_object(FOOD_DIR + "tea");
        price = 20;
        break;
    case "wine":
    case "white wine":
    case "glass of wine":
    case "wines":
    case "white wines":
    case "glass of white wines":
    case "glasses of white wine":
        order = clone_object(FOOD_DIR + "wine");
        price = 180;
        break;
    case "cider":
    case "glass of cider":
    case "glasses of cider":
    case "glass of ciders":
    case "ciders":
        order = clone_object(FOOD_DIR + "cider");
        price = 20;
        break;
// foods
    case "egg":
    case "eggs":
    case "quail egg":
    case "quail eggs":
    case "hard-boiled quail egg":
    case "hard-boiled quail eggs":
        order = clone_object(FOOD_DIR + "qegg");
        price = 50;
        break;
    case "sausage":
    case "sausages":
    case "smoked sausage":
    case "smoked sausages":
        order = clone_object(FOOD_DIR + "sausage");
        price = 75;
        break;
    case "stew":
    case "stews":
    case "squirrel stew":
    case "squirrel stews":
        order = clone_object(FOOD_DIR + "stew");
        price = 100;
        break;
    case "pheasant":
    case "pheasants":
    case "roasted pheasant":
    case "roasted pheasants":
        order = clone_object(FOOD_DIR + "pheasant");
        price = 160;
        break;
    }
    return (({order}) + ({price}));
}


int
block_room()
{
    if (this_player()->query_wiz_level()) return 0;

        write("You cannot go there yet.\n");
    return 1;
}
