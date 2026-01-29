// ROOM:  Dome - Arsenal Storeroom
//        DOME_ROOMS + arsenal_store

    /*  Calia Domain

        HISTORY
        31oct98 Created by Khon.
        Derived from /d/Genesis/doc/examples/trade/store.c

        PURPOSE
        This is the storeroom for the Arsenal store. It ensures
        unique club items are available every reboot.
 
        AREA HISTORY
        Not accessable from the grid, here for code purposes
        only.

    */

// INCLUSIONS AND DEFINITIONS

inherit "/std/room";
inherit "/lib/store_support";
    /* the default store-room support
     */

#include "defs.h"
#include <stdproperties.h>

#define ORN_RAPIER (DOME_WEAPONS + "orn_rapier")
#define ORN_DAGGER (DOME_WEAPONS + "orn_dagger")
#define SPLEN_RAPIER (DOME_WEAPONS + "splen_rapier")
#define SPLEN_DAGGER (DOME_WEAPONS + "splen_dagger")
#define DUEL_RAPIER (DOME_WEAPONS + "duel_rapier")
#define DUEL_DAGGER (DOME_WEAPONS + "duel_dagger")

// ROOM DEFINITION

void
create_room()
{

    /* DESCRIPTION */

    set_short("Pleasure Dome arsenal storeroom");

    set_long("The storeroom of the pleasure dome arsenal, " +
        "here for code reasons only.\n");

    /* ITEMS */

    /* EXITS */

    add_exit("arsenal", "down", 0, 01);

    /* PROPERTIES */

    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_HIDE, 10);
    add_prop(ROOM_I_INSIDE, 1);

    this_object()->reset_room();

    }

/*
 * You should always call store_update() if an object enters the
 * store-room to update it and let it be added to the stock.
 */
void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);

    store_update(obj);
}

/*
 * Here ends the necessary store-room code. If you want to have a
 * nifty feature, you might consider the code below. Every time the
 * function reset_room() is called, the store of the shop is checked
 * to see if a certain "default" stock is in stock and if not, if
 * will be supplied.
 */

/*
 * This global variable defines the standard inventory that should be
 * cloned every reset if the shop is not in full stock. The first
 * entry is the function that is used to create the object, the
 * second its filename and the third is the number of objects that
 * should be in stock.
 *
 * In this particular shop, a set number of whips will be in the
 * shop each time reset_room is called to update the shop. This may
 * of course mean that the shop can be sold out in the meantime. If
 * there are more than the set number when reset_room is called, the
 * surplus is not removed.
 */
mixed to_check = ({ ({ "create_weapon", ORN_RAPIER, 4 }),
                    ({ "create_weapon", ORN_DAGGER, 4 }),
                    ({ "create_weapon", SPLEN_RAPIER, 2 }),
                    ({ "create_weapon", SPLEN_DAGGER, 2 }),
                    ({ "create_weapon", DUEL_RAPIER, 1 }),
                    ({ "create_weapon", DUEL_DAGGER, 1 }),
                 });

void
reset_room()
{
    object *all_inv = all_inventory();
    int     i, j;
    int     num_found;

    for (i = 0; i < sizeof(to_check); i++)
    {
        num_found = sizeof(filter(all_inv, "object_filter",
            this_object(),
            ({ to_check[i][0], to_check[i][1] }) ));

        if (num_found < to_check[i][2])
        {
            for (j = num_found; j < to_check[i][2]; j++)
            {
                clone_object(to_check[i][1])->move(this_object(), 1);
            }
        }
    }
}

/*
 * This function is a support function that helps keeping the stock
 * full every time reset_room() is called.
 *
 * extra = ({ function_name, filename }) ... given from reset_room()
 */
int
object_filter(object obj, mixed extra)
{
    return (function_exists(extra[0], obj) == extra[1]);
}
