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
    remove_name("rack");
    set_name("shelf");
    add_name("wand shelf");
    set_adj("elaborate");
    add_adj("wand");
    set_short("@@short_fun");
    set_long("This elaborately carved shelf is designed with small " +
        "attachments to hold wands specifically.\n");
}

public string
short_fun()
{
    if (sizeof(all_inventory(this_object())) >= 1)
	return "elaborate wand shelf";
    return "empty wand shelf";
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
          + "   <list shelf>         - An organized display of the curre"
          + "ntly stocked items\n"
          + "   <list [item name]>  - Displays only items of the specifi"
          + "ed name in stock\n"
          + "   <kick shelf>         - Send all non-lasting items tumbling"
          + " to the floor\n");    
} /* hook_list_commands */

public void
init()
{
    ::init();
    add_action(do_help, "shelfhelp");
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

    if (obj->query_name() != "wand")
    {
        write("Only wands can fit on this shelf.\n");
        return 0;
    }
    
    return 1;
} /* valid_item_for_rack */