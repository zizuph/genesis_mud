/* armrstor.c: The storeroom of the Tyr armour merchant
 * Updated to Raumdor standards
 * Damaris 5/2001
 */
inherit "/std/room";
inherit "/lib/store_support"; /* the default store-room support */
#include <stdproperties.h>    /* the properties                 */
#include "defs.h"

void create_room()
{
    set_short("the storeroom of the armour merchant");
    set_long("On racks hang all the armours bought and sold by "+
             "the armour merchant of Tyr.\n");
    INSIDE
    add_exit(TYR_CARAVAN+"armrmrch.c", "south", 0, 1);

    this_object()->reset_room();
}
/*
 * You should always call store_update() if an object enters the store-
 * room to update it and let it be added to the stock.
 */
void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);

    store_update(obj);
}

/*
 * Here ends the necessary store-room code. If you want to have a nifty
 * feature, you might consider the code below. Every time the function
 * reset_room() is called, the store of the shop is checked to see if
 * a certain "default" stock is in stock and if not, if will be supplied.
 */
#define LTHRJRKN (TYR_ARM+"body_lth")
#define STDDDVST (TYR_ARM+"body_std")

/*
 * This global variable defines the standard inventory that should be
 * cloned every reset if the shop is not in full stock. The first entry is
 * the function that is used to create the object, the second its filename
 * and the third is the number of objects that should be in stock.
 */
mixed to_check = ({ ({"create_armour", LTHRJRKN, 2}),
                    ({"create_armour", STDDDVST, 1}),
                 });

void
reset_room()
{
    object *all_inv = all_inventory();
    int     i, j;
    int     num_found;

    for (i = 0; i < sizeof(to_check); i++)
    {
        num_found = sizeof(filter(all_inv, "object_filter", this_object(),
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
