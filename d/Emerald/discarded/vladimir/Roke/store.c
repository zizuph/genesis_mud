/*
 * Coders : Mercade and Maniac
 *
 * This is the store-room of the hardware shop of the  
 * crystalline palace.  Adapted from the original code
 * by Mercade for the dwarven race guild store.
 *
 * Created 2/2/94 by Maniac
 *
 * Revision history:
 */

/* inherit "/d/Gondor/common/room"; */

inherit "/lib/store_support";
inherit "/std/room";

#include <macros.h>
#include <stdproperties.h>
#include "defs.h"

#define HARDWARE_SHOP            (PALACE_DIR + "hardware_shop")
#define HARDWARE_DIR     "/d/Calia/tmp/glykron/palace/hardware_store/"

#define CLONE_OBJECT(s) clone_object(s)->move(TO)

/*
 * This define defines the standard inventory that should be cloned every
 * reset if the shop is not in full stock. The first entry is the function
 * that is used to create the object, the second its filename and the third
 * is the number of objects that should be in stock.
 */
#define MINIMUM_INVENTORY                      \
  ({ ({ "create_torch",     (HARDWARE_DIR + "standard_torch"), 4 }), \
     ({ "create_torch",     (HARDWARE_DIR + "quality_torch"), 4 }), \
     ({ "create_rope",      (HARDWARE_DIR + "rope"), 2 }), \
     ({ "create_container", (HARDWARE_DIR + "sack"), 4 }), \
     ({ "create_container", (HARDWARE_DIR + "backpack"),  6 }), \
  })

/*
 * Prototype
 */
void reset_room();

/*
 * Global variable
 */
mixed to_check = MINIMUM_INVENTORY;

void
create_room() 
{
    set_short("the store-room of hardware shop in crystalline palace");
    set_long("This store-room is used to store all items that are for " +
        "sale in the hardware shop in the crystalline " +
        "palace.\n");

    add_exit(HARDWARE_SHOP, "southeast");

    add_prop(ROOM_I_INSIDE, 1);

    reset_room();
}



void
reset_room()
{
    object *all_inv = all_inventory();
    int    i, j;
    int    num_found;

    for (i = 0; i < sizeof(to_check); i++)
    {
        if ((num_found = sizeof(filter(all_inv, "object_filter", TO,
            ({ to_check[i][0], to_check[i][1] }) ))) < to_check[i][2])
        {
            for (j = num_found; j < to_check[i][2]; j++)
            {
                CLONE_OBJECT(to_check[i][1]);
            }
        }
    }
}



/*
 * extra = ({ function_name, filename }) ... given from reset_room()
 */
int
object_filter(object obj, mixed extra)
{
    return (function_exists(extra[0], obj) == extra[1]);
}


public void
enter_inv(object ob, object from)
{
   ::enter_inv(ob, from);
   store_update(ob);
}





