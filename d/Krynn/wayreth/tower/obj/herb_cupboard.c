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
#include <files.h>

void
create_rack()
{
    remove_name("rack");
    set_name("cupboard");
    add_name("herb cupboard");
    set_adj("herb");
    set_short("@@short_fun");
    set_long("This cupboard has been built to store herbs in.\n");
}

public string
short_fun()
{
    if (sizeof(all_inventory(this_object())) >= 1)
	return "herb cupboard";
    return "empty herb cupboard";
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
        write("This cupboard is only for herbs.\n");
        return 0;
    }

    if (!IS_HERB_OBJECT(obj))
    {
        write("This cupboard is only for herbs.\n");
        return 0;
    }
    
    return 1;
}
