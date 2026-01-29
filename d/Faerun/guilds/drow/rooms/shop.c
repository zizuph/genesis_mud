/*
 * Drow Shop
 * By Finwe, May 2006
 */

#pragma strict_types

inherit "/d/Faerun/guilds/drow/rooms/base_room.c";

#include "/d/Faerun/defs.h"
#include "/d/Faerun/guilds/drow/race/guild.h"
#include "/d/Faerun/sys/shop_items.c"


//#include "/d/Shire/sys/shop_items.c"


#include <stdproperties.h>
#include <const.h>

#define STORE_ROOM "/d/Faerun/guilds/drow/rooms/store" 

void
create_drow_room()
{
    set_short("Equipment Trading Cave");
    set_long(short() + ". It is large with smooth walls. A tall shelf sits " +
        "against a wall and holds various items for sale. The floor is " +
        "swept clean. A wooden counter spans the width of the cave.\n");
    add_item(({"counter", "wooden counter"}),
        "It is wide and made of a single piece of wood. The counter is " +
        "polished smooth. There are scratches and knicks on the surface " +
        "from items that have been slid across it.\n");
    add_item(({"shelf", "tall shelf"}),
        "It is sturdy looking and made of wood. It sits behind the counter " +
        "and holds things for sale. You may 'list' to see what is on the shelf.\n");

    config_default_trade();
    set_money_greed_sell(95);
    set_money_greed_buy(95);
    set_store_room(STORE_ROOM);
    set_standard_equip(DROW_EQUIP);

    add_exit("join", "south");

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
