/* /d/Faerun/guilds/warlocks/rooms/shop.c
 *
 * Guild Shop
 * Nerull 2018
 *
 */

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "../guild.h";
#include "/d/Faerun/sys/shop_items.h"

inherit "/d/Faerun/sys/shop_items.c";
inherit WARLOCK_STD_ROOM;


/*
 * Function name: create_warlock_room
 * Description  : Constructor, redefine this to configure your room
 */
public void
create_warlock_room()
{
    add_prop(ROOM_I_INSIDE, 1);

    set_short("Inside a partly collapsed claystone tunnel");
    
    set_long("Inside a partly collapsed claystone tunnel. Large "
    +"segments of the ceiling lie scattered about at the "
    +"northern exit, forming tiny cracks and crevices that "
    +"leads further north but too small to enter for anyone except " 
    +"maybe snakes, rats and insects. Improvised shelves of old wooden "
    +"boards are bolted to the walls, which contain wares and "
    +"special merchandise used by warlocks for creating magical "
    +"charms. The old grumpy clerk guarding the inventory of this "
    +"rough improvised shop will also buy and sell regular items. An "
    +"iron brazier hanging from the ceiling illuminates the tunnel.\n");
    
    add_item(({"ceiling", "roof"}),
    "The ceiling is party collapsed on the north end of the "
    +"tunnel, revealing large jagged holes in the claystone. An "
    +"iron brazier hangs from the ceiling, providing some illumination "
    +"to the area.\n");
    
    add_item(({"tunnel"}),
    "This claystone tunnel leads to adjacent areas north and south "
    +"from here. Though, the passage to the north is blocked by "
    +"large segments of claystone blocks.\n");
    
    add_item(({"wall", "walls"}),
    "The walls of each side of the tunnel are filled with old wooden "
    +"shelves that contain items for warlocks to buy.\n");
    
    add_item(({"ground", "floor"}),
    "The ground is filled with dust and small claystone pebbles that "
    +"probably originated from the collapse of the ceiling. The old "
    +"grumpy clerk doesn't seem to care much about tidiness here.\n");
    
    add_item(({"brazier", "iron brazier", "chain", "iron chain"}),
    "The iron brazier is square shaped and made of cast iron. It hangs "
    +"from the ceiling, attached to a small iron chain that is anchored "
    +"to the ceiling. The iron brazier gives off some illumination to "
    +"the tunnel.\n");
    
    add_item(({"large segments", "segments", "large segments of ceiling",
    "segments of ceiling", "large blocks", "blocks"}),
    "Probably by some natural event or natural erosion, large blocks of "
    +"claystone has collapsed from the ceiling and blocks the north "
    +"exit entirely, effectively making the tunnel a dead end.\n");
    
    add_item(({"northern exit", "north exit"}),
    "The north exit of the tunnel is completely blocked by large claystone "
    +"segments that has collapsed from the ceiling.\n");
    
    add_item(({"old grumpy clerk", "clerk", "grumpy clerk"}),
    "This old warlock function as the shopkeeper of this improvised "
    +"shop. Wearing an old tattered beige hooded robe, you barely "
    +"see the white beard hidden in the shadows of the hood.\n");

    add_item(({"shelves", "shelf"}),
    "They are made primarily of old wood boards, firmly bolted to "
    +"the walls. They hold various items and special merchandise "
    +"for sale.\n");

    config_default_trade();
    set_money_greed_sell(100);
    set_money_greed_buy(100);
    set_store_room(STORE_ROOM);

    // this sets standard equipment when morts do 'list equipment'
    // see /d/Faerun/sys/shop_items.h to see what items are available.
    set_standard_equip(WARLOCK_EQUIP);

    add_exit(WARLOCK_ROOMS_DIR + "hall02", "south");

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
