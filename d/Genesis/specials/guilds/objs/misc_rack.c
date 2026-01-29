/* 
 * General Miscellaneous Rack for the Guilds of Genesis
 *  
 * This misc rack is based on the describable rack system. It holds
 * items that are neither weapons nor armours.
 *
 * Created by Petros, July 2009
 */

inherit "/d/Genesis/specials/guilds/objs/describable_rack";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <formulas.h>
#include <composite.h>

void
create_rack()
{
    remove_name("rack");
    set_name("shelf");
    add_name("steel shelf");
    set_adj("long");
    add_adj("steel");
    set_short("long steel shelf");
    set_long("This shelf seems to hold almost anything that doesn't "
        + "fit in the other racks.\n");
}

/*
 * Function:    valid_item_for_rack
 * Description: Mask this to indicate what type of items can actually
 *              enter the racks.
 */
public int
valid_item_for_rack(object obj)
{
    if (obj->query_prop(OBJ_I_BROKEN))
    {
        write("Why would you want to put broken things in the " + short() 
            + "?\n");
        return 0;
    }

    if (obj->check_armour() || obj->check_weapon())
    {
        write("The " + obj->short() + " will not fit in the " + short() 
            + ".\n");
        return 0;
    }
    
    return 1;
}
