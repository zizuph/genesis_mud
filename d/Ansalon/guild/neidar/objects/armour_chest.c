/*
 * Neidar Armour Chest
 *
 */

#include <stdproperties.h>

inherit "/d/Genesis/specials/guilds/objs/armour_rack";

public void
create_rack()
{
    remove_name("rack");
    set_name("chest");
    set_adj("large");
    set_adj("stone");
    set_short("large stone chest");
    set_pshort("lange stone chests");
    set_long("This is a very large chest made of stone, " 
        + "used to hold all the armours left behind by the "
        + "dwarven warriors of the Neidar clan for other "
        + "clan members to use. See <chesthelp> for instructions "
        + "on how to use it.\n");
    add_prop(OBJ_I_VALUE, 0);
    add_prop(CONT_I_IN,1);
    add_prop(CONT_I_RIGID,0);
    add_prop(CONT_I_TRANSP,0);
    add_prop(OBJ_M_NO_GET, 1);
    add_prop(CONT_I_WEIGHT, 250000);
    add_prop(CONT_I_VOLUME, 75000);
    add_prop(CONT_I_MAX_WEIGHT, 90000000);
    add_prop(CONT_I_MAX_VOLUME, 90000000);
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
          + "   <list chest>         - An organized display of the curre"
          + "ntly stocked items\n"
          + "   <list [item name]>  - Displays only items of the specifi"
          + "ed name in stock\n"
          + "   <kick chest>         - Send all non-lasting items tumbling"
          + " to the floor\n");
}

public void
init()
{
    ::init();
    add_action(do_help, "chesthelp");
}

/*
 * Function:    hook_prepend_describe_contents
 * Description: Allows one to customize the text that goes above the
 *              listing of the contents in the rack object.
 */
public void
hook_prepend_describe_contents(object for_obj, object * obarr)
{
}

/*
 * Function:    hook_append_describe_contents
 * Description: Allows one to customize the text that goes after the
 *              listing of the contents in the rack object.
 */
public void
hook_append_describe_contents(object for_obj, object * obarr)
{
}