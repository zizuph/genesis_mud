/*
 * WoHS Leftover Cabinet
 */
 
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <formulas.h>
#include <composite.h>

inherit "/d/Krynn/wayreth/tower/rack/rack";

public void
create_rack()
{
    remove_name("rack");
    set_name("cabinet");
    add_name("leftover cabinet");
    set_adj("leftover");
    add_adj("chilled");
    set_short("@@short_fun");
    set_long("This cabinet is icy to touch, enchanted to keep leftovers " +
        "stored within it from decaying. See <cabinethelp> for " +
        "instructions on how to use it.\n");
}

public string
short_fun()
{
    if (sizeof(all_inventory(this_object())) >= 1)
	return "chilled leftover cabinet";
    return "empty leftover cabinet";
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
          + "   <list cabinet>      - An organized display of the curre"
          + "ntly stocked items\n"
          + "   <list [item name]>  - Displays only items of the specifi"
          + "ed name in stock\n"
          + "   <kick cabinet>      - Send all non-lasting items tumbling"
          + " to the floor\n");
}

public void
init()
{
    ::init();
    add_action(do_help, "cabinethelp");
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

    if (!IS_LEFTOVER_OBJECT(obj))
    {
        write("This cabinet is only for leftovers.\n");
        return 0;
    }
    
    return 1;
} /* valid_item_for_rack */