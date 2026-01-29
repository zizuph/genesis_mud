/*
 * the shop's storage room
 * Boreaulam, April 2012
 */
#pragma save_binary
#pragma strict_types

inherit "/std/room";
inherit "/lib/store_support";

#include "defs.h"


/*
 * Function name:		enter_inv
 * Description  :
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    store_update(ob);
} /* enter_inv */

/*
 * Function name:		create_room
 * Description  :		creates room
 */
void
create_room()
{
    set_short("The shop's store room");
    set_long("This is the store room for the shop.\n\n");
    set_default_stock( ({EQUIP_DIR + "lsword", 3}));
} /* create_room */

