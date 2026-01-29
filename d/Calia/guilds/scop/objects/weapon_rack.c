
/* 
 *  Weapon rack for the Spirit Circle of Psuchae
 *  July 29th, 2003
 *
 *  Petros - September 2008
 *    Changed the rack to use a describable rack system so that one
 *    can list objects by type and see it in a nicely formatted list.
 */

inherit "/d/Genesis/specials/guilds/objs/weapon_rack";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <formulas.h>
#include <composite.h>

#include "defs.h"

void
create_rack()
{
    set_name("chest");
    add_name("weapons chest");
    set_adj("weapons");
    add_adj("large");
    set_short("large weapons chest");
    set_long("This large weapons chest sits against the north wall of "+
      "the armoury.  It is made from polished metal and looks like it "+
      "might hold a lot of weapons. If you wanted, you could kick it "+
      "to remove things that will not save. <kick weapons chest>\n"); 

    add_prop(CONT_I_MAX_WEIGHT, 5000000);
    add_prop(CONT_I_MAX_VOLUME, 5000000);
    add_prop(CONT_I_WEIGHT, 500000);
    add_prop(CONT_I_VOLUME, 500000);
    add_prop(CONT_I_RIGID, 1);
    add_prop(OBJ_M_NO_GET, "The large weapons chest can't be taken, it is "+
        "entirely too heavy.\n");
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
          + "   <list [weapontype]> - Displays only items of the specifi"
          + "ed type in stock\n"
          + "   <kick chest>         - Send all non-lasting items tumbling"
          + " to the floor\n");    
}
