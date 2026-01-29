/*
 * Thornhold Alehouse
 * -- Twire/Gnim June 2016
 */
 
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"

inherit BASE_KEEP;
inherit "/d/Faerun/lib/inn";
inherit "/d/Faerun/thornhold/rooms/nandc_gameboard";

#define PRICELIST_ID  ({"pricelist","list","prices", "menu", "sign"})

object kala_npc;
object brigid_npc;
object guard_npc;

void
create_house()
{
    set_short("The Thornhold Alehouse");
    set_long("This cozy alehouse affords a welcoming atmosphere. A " +
             "cheery fire burns in the stone hearth, sending warmth " +
             "and orange light dancing through the interior. A large " +
             "bearskin rug lays on the wood-planked floor before the " +
             "hearth, and a few stout oak tables with chairs are here " +
             "where patrons can rest and enjoy a meal. The back wall is " +
             "lined with casks of beer and ale, and on the wall hangs a " +
             "pricelist. Above the hearth hangs a boar's head mounted on " +
             "a wooden plaque, its face set into a fierce expression. To " +
             "the north, a narrow doorway leads to the alehouse lodging " +
             "area, and to the east you may return to the Thornhold " +
             "courtyard.\n");
             
	add_item(({ "boar", "head", "trophy", "boar's", 
				"boars head", "plaque"}),
             "The boar's head is a hunting trophy. Its face is set into " +
             "a fierce expression.\n");
             
	add_item(({ "thornhold", "Thornhold", "hold", 
			"fortress", "fort" }),
			"You are standing in the alehouse of Thornhold.\n");
             
	add_item(({ "rug", "bearskin", "bearskin" }),
              "The skin of a great brown bear has been tanned and " +
              "turned into a rug, paws outstretched to the four corners " +
              "of the room.\n");

    add_item(({ "floor" }),
              "The floor is built of sturdy oak planks, worn from " +
              "from the boots of innumeralble patrons.\n");
              
    add_item(({ "wall", "walls" }),
              "The walls are made of the same gray stone of which " +
              "entire fortress of Thornhold is constructed.\n");
    	
    add_item(({ "casks", "cask", "ale" }),
              "The casks of ale are stout oak barrels marked with the " +
              "faceted gem that is the symbol of Clan Stoneshaft.\n");
    
    add_item(({ "stout oak tables", "oak tables", "tables" }),
    		"Several wooden tables of various sizes and shapes, " +
    		"can be seen throughout the Alehouse.\n");
    
    add_item(({ "doorway", "narrow doorway" }),
    		"The exit leads to the east.\n");
    
	add_fireplace();

    add_item(PRICELIST_ID, "@@pricelist_desc");

    configure_faerun_inn();
    configure_game_table();

    add_exit(ROOM_DIR + "courtyard_north",  "east");
    add_exit(ROOM_DIR + "bunkhouse",  "north");

    add_cmd_item("game", ({"examine", "exa", "look"}), "@@look_board");
        
    reset_room();
}

string
pricelist_desc()
{
    return "\n" +
"+---------------------------------------------+\n" +
"|                                             |\n" +
"|             The Thornhold Alehouse          |\n" +
"|          ---------------------------        |\n" +
"|                                             |\n" +
"|   Drinks                                    |\n" +
"|   ------                                    |\n" +
"|   Glass of Water . . . . . 6 copper nibs    |\n" +
"|   Waterdhavian Beer .. . . 1 silver shard   |\n" +
"|   Stoneshaft Ale   . . . . 2 silver shards  |\n" +
"|                                             |\n" +
"|   Food                                      |\n" +
"|   ----                                      |\n" +
"|   Mushroom Skewer. . . . . 1 silver shard   |\n" +
"|   Onion Soup   . . . . . . 4 silver shards  |\n" +
"|   Roast Mutton . . . . . . 5 silver shards  |\n" +
"|                                             |\n" +
"|   Bunkhouse Lodging                         |\n" +
"|   -----------------                         |\n" +
"|   Bedding. . . . . . . . . 9 silver shards  |\n" +
"|                                             |\n" +
"+---------------------------------------------+\n\n";
}

void
reset_room()
{
   ::reset_room();

   setuid(); 
   seteuid(getuid());
 
    if ((!kala_npc))
    {
        kala_npc = clone_object(NPC_DIR + "kala");
        kala_npc->move(this_object());
    }
    
    if ((!brigid_npc))
    {
        brigid_npc = clone_object(NPC_DIR + "brigid");
        brigid_npc->move(this_object()); 
    }
    if ((!guard_npc))
    {
        guard_npc = clone_object(NPC_DIR + "dwarf_guard");
        guard_npc->move(this_object()); 
    } 
}

int
do_order(string str)
{
    return ::do_order(str);
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

void
init()
{
    ::init();
    init_faerun_inn();
    init_nandc_game();
    add_action("do_read", "read");
}

mixed *
get_order(string item_name)
{
    object order;
    int price;

    setuid(); seteuid(getuid());
    switch (item_name)
    {
    case "bedding":
    case "sheets":
        order = clone_object(OBJ_DIR + "bedding");
        price = 108;
        break;
    case "soup":
    case "onion":
        order = clone_object(OBJ_DIR + "onion_soup");
        price = 48;
        break;
    case "mutton":
    case "roast":
        order = clone_object(OBJ_DIR + "mutton.c");
        price = 60;
        break;
    case "skewer":
    case "mushroom":
        order = clone_object(OBJ_DIR + "mushroom_skewer.c");
        price = 12;
        break;
    case "water":
    case "glass":
        order = clone_object(OBJ_DIR + "water_glass.c");
        price = 6;
        break;
    case "Waterdhavian":
    case "waterdhavian":
    case "beer":
        order = clone_object(OBJ_DIR + "waterdhavian_beer.c");
        price = 12;
        break;
    case "stoneshaft":
    case "Stoneshaft":
    case "ale":
        order = clone_object(OBJ_DIR + "stoneshaft_ale.c");
        price = 24;
        break;
    }
    return (({order}) + ({price}));
}



