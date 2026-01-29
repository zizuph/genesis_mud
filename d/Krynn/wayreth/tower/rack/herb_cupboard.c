/*
 * WoHS Herb Cupboard
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
    set_name("cupboard");
    add_name("herb cupboard");
    set_adj("herb");
    set_short("@@short_fun");
    set_long("This cupboard has been built to store herbs in. " +
        "See <cupboardhelp> for instructions on how to use it.\n");
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
          + "   <list cupboard>      - An organized display of the curre"
          + "ntly stocked items\n"
          + "   <list [item name]>  - Displays only items of the specifi"
          + "ed name in stock\n"
          + "   <kick cupboard>      - Send all non-lasting items tumbling"
          + " to the floor\n");
}

public string
short_fun()
{
    if (sizeof(all_inventory(this_object())) >= 1)
	return "herb cupboard";
    return "empty herb cupboard";
}

public void
init()
{
    ::init();
    add_action(do_help, "cupboardhelp");
}

/*
 * Function:    format_list_item_row 
 * Description: Given the item information, it prints out a formatted
 *              row including whatever information it needs for the
 *              columns. It should match the number of columns that are
 *              printed in format_header_and_footer.
 *              The last argument "obj" can be used to glean more info
 *              to be printed.
 */
public string
format_list_item_row(string short_desc, int count, int recoverable, object obj)
{
    string row_content, prepend_text;

    if(strlen(obj->query_herb_name()) > 0)
        short_desc = obj->query_herb_name();
    
    if (recoverable == 1)
    {
        prepend_text = "+ ";
    }
    else
    {
        prepend_text = "  ";
    }
    
    return "\t" + sprintf("|  %-50s | %5d  |\n", prepend_text + short_desc, 
                        count);
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
        write("This cupboard is only for herbs.\n");
        return 0;
    }

    if (!IS_HERB_OBJECT(obj))
    {
        write("This cupboard is only for herbs.\n");
        return 0;
    }
    
    return 1;
} /* valid_item_for_rack */