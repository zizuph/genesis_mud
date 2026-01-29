/*
 * Shop
 * Boreaulam, April 2012
 */
#include "defs.h"
#pragma save_binary
#pragma strict_types

inherit L1_BASE_ROOM;
inherit "/lib/shop";

#include <stdproperties.h>

/*
 * Function name:		create_room
 * Description  :		creates room
 */
void
create_room()
{
	::create_room();
    set_short("Shop");
    set_long("You are in the goblin shop. There is a small " +
             "sign on one of the walls, just above a large counter, behind " +
             "which the shopkeeper sits.\n\n");

    config_default_trade();

    add_exit ("roomg", "south");

	add_item("shop", long());
    add_item("counter", "It's a large counter made of stone.\n");
    add_item("shopkeeper",
             "He looks as if he wouldn't mind taking your money.\n");
    add_item("shelves", "The shelves are filled with items.\n");
    add_item("items", "Use <list> to check staff for sale.\n");
    add_item(({"sign", "small sign"}),
             "You should <read sign>.\n");

    set_store_room(ROOMS_DIR+"level1/store");
} /* create_room */

/*
 * Function name:		init
 * Description  :		init room
 */
void
init()
{
  ::init();

  init_shop();
} /* init */

