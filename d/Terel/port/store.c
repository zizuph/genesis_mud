/* This comment tells emacs to use c++-mode -*- C++ -*- */

/* The Fisherman shop's store room. Mortricia 920927 */

#include "/d/Terel/include/Terel.h"
inherit "/std/room";
inherit "/lib/store_support";

#include <ss_types.h>
#include <wa_types.h>
#include <money.h>

/*
 * Function name: enter_inv
 * Description:   Called when objects enter this container or when an
 *                object has just changed its weight/volume/light status.
 * Arguments:     ob: The object that just entered this inventory
 *                from: The object from which it came.
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}

/*
 * Function name: reset_room
 * Description:   clone a knife if necessary
 */
public void
reset_room()
{
    object knife, shovel;

    if (!present("knife")) {
        knife = clone_object(PORT_DIR + "weapon/knife");
        knife->move(TO);
    }
    if (!present("shovel")) {
        shovel = clone_object(PORT_DIR + "obj/shovel");
        shovel->move(TO);
    }
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    set_short("Store room of Fisherman's shop");
    set_long("The store room of the Fisherman's Shop.  What are you " +
	     "doing here?.\n");
    
    INSIDE;

    add_exit(PORT_DIR + "shop", "north", 0);

    clone_object(PORT_DIR + "weapon/plain_sword")->move(TO);
    reset_room();
}
