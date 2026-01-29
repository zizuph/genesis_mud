/*
 * WoHS Weapon Rack
 */

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <formulas.h>
#include <composite.h>
 
inherit "/d/Krynn/wayreth/tower/rack/rack";

void
create_rack()
{
    set_name("rack");
    add_adj( ({"mahogany", "staff", "polearm"}) );
    set_short("@@short_fun");
    set_long("This rack is affixed to the tower wall. "+
	"It has small circular holes in the bottom, and leather "+
	"straps at the top for holding staves and other polearms "+
	"steady. See <rackhelp> for instructions on how to use it.\n");
}

public string
short_fun()
{
    if (sizeof(all_inventory(this_object())) >= 1)
	return "mahogany staff rack";
    return "empty mahogany staff rack";
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
        write("This rack is for staves and poles. The " + 
            obj->short() + " will not fit in the " + short() + ".\n");
        return 0;
    }

    if (!(obj->query_wt() == W_POLEARM))
    {
        write("This rack is for staves and poles. The " + 
            obj->short() + " will not fit in the " + short() + ".\n");
        return 0;
    }
    
    return 1;
} /* valid_item_for_rack */