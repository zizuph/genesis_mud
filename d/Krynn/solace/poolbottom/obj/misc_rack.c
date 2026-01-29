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
    set_adj("miscellaneous");
    add_adj("misc");
    add_adj("junk");
    set_short("@@short_fun");
    set_long("This shelf seems to hold almost anything that doesn't "
        + "fit in the other racks.\n");
}

public string
short_fun()
{
    if (sizeof(all_inventory(this_object())) >= 1)
	return "miscellaneous shelf";
    return "empty miscellaneous shelf";
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

    if (obj->query_name() == "wand")
    {
        write("Wands can go on the wand shelf.\n");
        return 0;
    }
    
    return 1;
}
