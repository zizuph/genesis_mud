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
    set_name("cabinet");
    add_name("leftover cabinet");
    set_adj("leftover");
    add_adj("chilled");
    set_short("@@short_fun");
    set_long("This cabinet is icy to touch, enchanted to keep leftovers " +
       "stored within it from decaying.\n");
}

public string
short_fun()
{
    if (sizeof(all_inventory(this_object())) >= 1)
	return "chilled leftover cabinet";
    return "empty leftover cabinet";
}

/*
 * Function:    valid_item_for_rack
 * Description: Mask this to indicate what type of items can actually
 *              enter the racks.
 */
public int
valid_item_for_rack(object obj)
{

    if (!IS_LEFTOVER_OBJECT(obj))
    {
        write("This cabinet is only for leftovers.\n");
        return 0;
    }
    
    return 1;
}
