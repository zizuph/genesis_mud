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
    remove_name("rack");
    set_name("chest");
    add_name("armour chest");
    set_adj("armour");
    add_adj("wooden");
    set_short("@@short_fun");
    set_long("This large chest is made from polished wood and is used "+
        "by students to store clothing and armour. If you wanted, you "+
        "could kick it to remove things that will not save. <kick armour "+
        "chest>\n");
}

public string
short_fun()
{
    if (sizeof(all_inventory(this_object())) >= 1)
	return "wooden armour chest";
    return "empty wooden armour chest";
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
