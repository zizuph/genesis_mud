/* General store for Vingaard Keep by Morrigan, Jan 97       */
/* Taken from the Calia General store by Maniac and Mercade. */

#pragma save_binary

inherit "/lib/store_support";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include "../../local.h"

inherit IN_BASE;

#define CLONE_OBJECT(s) clone_object(s)->move(this_object())

/*
* This define defines the standard inventory that should be cloned every
* reset if the shop is not in full stock. The first entry is the function
    * that is used to create the object, the second its filename and the third
* is the number of objects that should be in stock.
*/

#define MINIMUM_INVENTORY  ({ })

/*
* Global variable
*/
mixed to_check = MINIMUM_INVENTORY;

/*
* extra = ({ function_name, filename }) ... given from reset_room()
*/
int
object_filter(string extra1, string extra2, object obj)
{
    return (function_exists(extra1, obj) == extra2);
}

void
reset_vin_room()
{
    object *all_inv = all_inventory(this_object());
    int    i, j, k;
    int    num_found;
    
    for (i = 0; i < sizeof(to_check); i++)
    if ((num_found = sizeof(filter(all_inv,
                        &object_filter(to_check[i][0], to_check[i][1]) )))
        < to_check[i][2])
    {
        for (j = num_found; j < to_check[i][2]; j++)
        CLONE_OBJECT(to_check[i][1]);
    }
}

void
create_vin_room()
{
    set_short("Storeroom of Vingaard Keep General Store");
    set_long("This is the storeroom of the General Store in Vingaard "+
        "Keep, used to store items that are sold there.\n");
    add_prop(ROOM_I_INSIDE, 1);
    
    reset_vin_room();
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}

