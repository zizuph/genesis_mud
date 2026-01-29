/*
 * Updated to more modern rack code.
 * Arman, November 2021
 */

inherit "/d/Genesis/specials/guilds/objs/describable_rack";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <formulas.h>
#include <composite.h>

// Rack listing
inherit "/d/Ansalon/guild/pot/obj/rack_list";

void
create_rack()
{
    set_name("rack");
    set_adj("weapon");
    set_short("weapon rack");
    set_long("It is a weapon rack standing against the wall.\n");

    add_prop(OBJ_M_NO_GET, 1);
    add_prop(CONT_I_RIGID, 1);
    add_prop(CONT_I_WEIGHT, 15000);
    add_prop(CONT_I_VOLUME, 15000);
    add_prop(CONT_I_MAX_WEIGHT, 9000000);
    add_prop(CONT_I_MAX_VOLUME, 9000000);
    
    set_no_show_composite(1);
}

int
prevent_enter(object ob)
{
    if (!ob->check_weapon())
        return 1;
    
    return ::prevent_enter(ob);
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
          + "ntly stored items\n"
          + "   <list [item name]>  - Displays only items of the specifi"
          + "ed name stored\n"
          + "   <kick rack>         - Send all non-lasting items tumbling"
          + " to the floor\n");
}