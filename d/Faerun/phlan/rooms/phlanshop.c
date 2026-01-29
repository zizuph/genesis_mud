/* /d/Faerun/phlan/rooms/phlanshop.c
 *
 * 
 * Nerull 2019
 *
 * Modified by Tharizdun 2021
 */

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include <defs.h>

#include "/d/Faerun/sys/shop_items.h"

inherit "/d/Faerun/sys/shop_items.c";

inherit BASE_PHLAN_INDOOR;


/*
 * Function name: create_warlock_room
 * Description  : Constructor, redefine this to configure your room
 */

public void
create_phlan_room()
{
    add_prop(ROOM_I_INSIDE, 1);

    set_short("The Phlan shop");
    
    set_long("Shelves line the walls of this well-maintained shop."
    +" Centered in the eastern wall is a window allowing in light."
    +" The floors are swept clean and everything seems well organized."
    +" Behind a wooden counter an older man with a broad chest and"
    +" grey hair dusting the displays. It is obvious he takes pride"
    +" in his business. A plaque with instructions is mounted unob"
    +"trusively on the wall.\n");

    add_item(({"shelf", "shelves"}),
    "The shelves contain various items of use to both the common"
    +" citizen as well as the prospective adventurer. Examining the"
    +" plaque would be useful to see how best to sort through them.\n");
    
    add_item(({"wall", "walls"}),
    "The walls are of knotty pine, both attractive and fragrant. Many"
    +" shelves of the same material line them displaying the wares for"
    +" sale.\n");
    
    add_item(({"floor", "floors", "ground"}),
    "The floors are wooden and cleanly swept.\n");
    
    add_item(({"items"}),
    "The items have been carefully organized by the shopkeeper. Perhaps"
    +" reading the intructions on the plaque could give you more infor"
    +"mation on how to examine them.\n");
    
    add_item(({"counter"}),
    "The counter is clean and polished.\n");
    
    add_item(({"window"}),
    "The window looks out across the harbour to the Moonsea to the east.\n");    
    
    add_item(({"harbour", "sea", "moonsea", "waters"}),
        "The Moonsea extends westward inland in the Phlan harbour. The "
        +"waters are dark blue and smell fresh and clean.\n");    
    
    add_item(({"plaque"}),
    "Please 'list equipment' to see what is currently in stock.\n");
    
     add_cmd_item( ({ "plaque", "the plaque" }),
                  ({ "read", }), 
    "Please 'list' to see what is in store. For the right price, "
    +"you may also sell items or buy available merchandize.\n");
    

    config_default_trade();
    set_money_greed_sell(100);
    set_money_greed_buy(100);
    set_store_room(ROOM_DIR + "storephlan");
    

    add_exit(ROOM_DIR + "road10", "west");

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
}
