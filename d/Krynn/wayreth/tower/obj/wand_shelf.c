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
    add_name("wand shelf");
    set_adj("elaborate");
    add_adj("wand");
    set_short("@@short_fun");
    set_long("This elaborately carved shelf is designed with small attachments to " +
        "hold wands specifically.\n");
}

public string
short_fun()
{
    if (sizeof(all_inventory(this_object())) >= 1)
	return "elaborate wand shelf";
    return "empty wand shelf";
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
        write("Why would you want to put broken things on the " + short() 
            + "?\n");
        return 0;
    }

    if (obj->check_armour() || obj->check_weapon())
    {
        write("Only wands can fit on this shelf.\n");
        return 0;
    }

    if (!obj->id("wand"))
    {
        write("Only wands can fit on this shelf.\n");
        return 0;
    }
    
    return 1;
}
