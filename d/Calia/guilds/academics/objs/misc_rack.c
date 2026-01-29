/* 
 * Miscellaneous Rack for the Academy of Elemental Arts
 *  
 * Created by Petros, September 2009
 */

#include <stdproperties.h>

inherit "/d/Genesis/specials/guilds/objs/misc_rack";

public void
create_rack()
{
    remove_name("rack");
    set_name("shelf");
    add_name("_academy_misc_shelf");
    set_adj("long");
    add_adj("glassy");
    set_short("long glassy shelf");
    set_long("This shelf spans the entire southern wall of this room. "
        + "What amazes you is that you can see completely through it! Upon "
        + "closer inspection, it looks like the shelf itself is made "
        + "out of ice. It's cold to the touch, but doesn't seem to be "
        + "melting at all. It looks like it can hold any sort of "
        + "miscellaneous items.\n\n");
    add_prop(CONT_I_ATTACH, 1); // allows things to be put "on" the shelf insteads
    
    set_no_show_composite(1);
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
          + "   <list shelf>        - An organized display of the curre"
          + "ntly stocked items\n"
          + "   <list [item name]>  - Displays only items of the specifi"
          + "ed name in stock\n"
          + "   <kick shelf>        - Send all non-lasting items tumbling"
          + " to the floor\n");    
}

