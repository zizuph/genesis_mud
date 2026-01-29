/* /d/Faerun/guilds/fire_knives/rooms/o4.c
 *
 * 
 * Nerull 2019
 */

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "../guild.h";
#include "/d/Faerun/sys/shop_items.h"

inherit "/d/Faerun/sys/shop_items.c";

inherit FIREKNIVES_STD_ROOM;

object merchant;



/*
 * Function name: create_warlock_room
 * Description  : Constructor, redefine this to configure your room
 */

public void
create_fireknives_room()
{
    add_prop(ROOM_I_INSIDE, 1);

    set_short("The Trader's Alcove");
    
    set_long("Inside a small, well-kept room lined whose stone "
    +"cold walls are lined with display cases and shelves full "
    +"of miscellaneous items there is a pragmatic atmosphere of "
    +"trade. Though most of the items seen at first glance are all "
    +"common, some of them stand out due to their rarity. At the "
    +"far south of the room is a simple wooden counter behind which "
    +"the trader conducts his business, and above which is a "
    +"plaque with instructions you can read.\n");

    add_item(({"cases"}),
    "The cases contain various items, some common while others not "
    +"so. Examining the plaque above the counter would be useful to "
    +"see how best to sort through them.\n");
    
    add_item(({"wall", "walls"}),
    "The walls are cold and rough, devoid of protection or coverings. "
    +"Along their lengths are shelves and cases in which various "
    +"items are displayed.\n");
    
    add_item(({"shelves"}),
    "The shelves contain various items, some common while "
    +"others not so. Examining the plaque above the counter would "
    +"be useful to see how best to sort through them.\n");
    
    add_item(({"items"}),
    "There are manifold items around the room. Perhaps reading the "
    +"instructions on the plaque could provide more information on "
    +"how best to examine them?\n");
    
    add_item(({"counter"}),
    "The counter is simple and bare, clean and devoid of rubble "
    +"all the best to conduct transactions in.\n");
    
    add_item(({"plaque"}),
    "Please 'list equipment' to see what is in store. For the right price, "
    +"you may also sell items or buy available merchandize.\n");
    
     add_cmd_item( ({ "plaque", "the plaque" }),
                  ({ "read", }), 
    "Please 'list' to see what is in store. For the right price, "
    +"you may also sell items or buy available merchandize.\n");
    

    config_default_trade();
    set_money_greed_sell(100);
    set_money_greed_buy(100);
    set_store_room(FIREKNIVES_ROOMS_DIR + "store");

    add_exit(FIREKNIVES_ROOMS_DIR + "o4.c", "north");
	
	room_add_object(FIREKNIVES_OBJ_DIR + "magical_trash_can");

    reset_faerun_room();
}


void
init()
{
    ::init();
    init_shop();
}


void
reset_faerun_room()
{
    ::reset_faerun_room();
    
    if (!merchant)
    {
        merchant = clone_object(FIREKNIVES_GUILD_DIR + "npc/merchant");
        merchant->move(this_object(), 1);
    }
}
