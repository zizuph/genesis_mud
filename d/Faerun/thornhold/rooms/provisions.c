/*
 * Thornhold
 * -- Twire/Gnim June 2016
 */
//#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"

inherit BASE_KEEP;

#include "/d/Faerun/sys/shop_items.h"
#include "/d/Faerun/sys/shop_items.c"
#include <stdproperties.h>
#include <const.h>

#define STORE_ROOM "/d/Faerun/thornhold/rooms/pro_stock"

#define THORN_EQUIP      ({ TORCH, BACKPACK, HERB_JAR})


object durlar_npc;

void
create_house()
{
    set_short("Durlar's Provisions");
    set_long("This cramped provisions shop has every nook, cranny, and " +
             "corner stocked with various goods needed by caravans and " +
             "travellers who come to the hold for resupply. Barrels of " +
             "fresh water and crates of travel rations line the walls, and " +
             "every manner of adventuring gear fills the space. A counter " +
             "made of wood is set against the north wall, and a movable " +
             "wooden stepstool on wheels is here to enable the dwarven " +
             "provisioner to reach anything requested for purchase. To the " +
             "east, a narrow doorway leads to a storeroom packed with more " +
             "goods, and to the south you can return to the courtyard.\n");
             
    add_item(({ "barrels", "water", "fresh water" }),
                "Rustic barrels containing water are lined up against the " +
                "back wall, used for washing and refilling the water " +
                "supply of visiting caravans.\n");

    add_item(({ "gear" }),
                "Most of the gear is stacked tidly in crates and marked " +
                "for delivery for those passing through Thornhold on their " +
                "journeys.\n");
                
    add_item(({ "crates", "rations", "provisions", "items", "goods" }),
                "Several varieties travel rations are here, hearty fare " +
                "of the type purchased by long-distance travellers and " +
                "caravans. Bulk foods are in crates, while various other " +
                "preserved sundries are in bundles, jars, and boxes on " +
                "the high shelves.\n");

    add_item(({ "counter" }),
                "This thick rustic counter is a slab of hewn pine, scuffed " +
                "and dented from the years of various transactions.\n");

    add_item(({ "shelves" }),
                "Thick shelves are built into the walls and are richly " +
                "stocked with various provisions.\n");
                
    add_item(({ "stepstool" , "stool"}),
                "The little wooden stepstool is out of your reach against " +
                "the back wall. It has one set of broad wooden wheels and " +
                "two stationary legs, and is the ideal height for lifting " +
                "a vertically-challenged dwarf to the proper height to " +
                "retrieve provisions from the higher shelves.\n");
                
    add_item(({ "walls" }),
                "The walls are hewn of the same thick stone as the rest of " +
                "the fortress, but lined with stacked provisions and build " +
                "with high shelves to store various items.\n");
    
    add_item(({ "narrow doorway" }), "The southern exit leads to the " +
    			"courtyard.\n");

    add_exit(ROOM_DIR + "courtyard_north",  "south");
    add_exit(ROOM_DIR + "storehouse",  "east");

    config_default_trade();
    set_standard_equip(THORN_EQUIP);
    set_money_greed_sell(98);
    set_money_greed_buy(90);
    set_store_room(STORE_ROOM);

    reset_room();
}

void
reset_room()
{
   ::reset_room();

   setuid();
   seteuid(getuid());

    if ((!durlar_npc))
    {
        durlar_npc = clone_object(NPC_DIR + "durlar");
        durlar_npc->move(this_object());
    }
}

/*
 * Function name:	init
 * Description	:
 */
public void
init()
{
    ::init();

    init_shop();
}

