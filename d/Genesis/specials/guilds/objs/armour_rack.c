/* 
 * General Armour Rack for the Guilds of Genesis
 *  
 * This weapon rack is based on the describable rack system.
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
    add_name("armour rack");
    set_adj("armour");
    add_adj("wooden");
    set_short("wooden armour rack");
    set_long("This large armour rack is made from polished metal and look "+
        "like it might hold alot of sets of armour. If you wanted, you "+
        "could kick it to remove things that will not save. <kick armour "+
        "rack>\n");
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

    if (!(obj->check_armour()))
    {
        write("The " + obj->short() + " will not fit in the " + short() 
            + ".\n");
        return 0;
    }
    
    return 1;
}
