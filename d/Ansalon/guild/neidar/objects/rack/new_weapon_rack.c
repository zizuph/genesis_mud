/*
 * Neidar Weapon Rack
 */

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <formulas.h>
#include <composite.h>
 
inherit "/d/Ansalon/guild/neidar/objects/rack/new_rack";

void
create_rack()
{
    set_adj("large");
    set_adj("weapon");
    set_short("weapon rack");
    set_long("This large rack, skillfully crafted " 
        + "from a dark wood native to these areas, "
        + "is used by the clan warriors to store their "
        + "weapons for later use. See <rackhelp> for "
        + "instructions on how to use it.\n");
}

/*
 * Function:    hook_list_commands
 * Description: The list of available commands will be listed after the
 *              contents of the rack. Customize this for each specific
 *              rack for their commands.
 */
public void
hook_list_commands(object for_obj)
{
    for_obj->catch_tell(
            "                         ----> [Commands for Use] <----\n\n"
          + "   <list rack>         - An organized display of the curre"
          + "ntly stocked items\n"
          + "   <list [item name]>  - Displays only items of the specifi"
          + "ed name in stock\n"
          + "   <kick rack>         - Send all non-lasting items tumbling"
          + " to the floor\n");    
} /* hook_list_commands */

public void
init()
{
    ::init();
    add_action(do_help, "rackhelp");
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

    if (!(obj->check_weapon()))
    {
        write("The " + obj->short() + " will not fit in the " + short() 
            + ".\n");
        return 0;
    }
    
    return 1;
} /* valid_item_for_rack */