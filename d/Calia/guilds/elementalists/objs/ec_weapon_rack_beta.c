/* 
 * Weapon Rack for Elementalist Guilds of Calia
 *  
 * Created by Petros, April 2010
 */

inherit "/d/Genesis/specials/guilds/objs/weapon_rack";
#include "defs.h"

public void
create_rack()
{
    remove_name("rack");
    set_name("chest");
    add_name("_temple_weapons_chest");
    set_adj("weapons");
    add_adj("large");
    add_adj("wooden");
    set_short("large wooden chest");
    set_long("This large chest is made of solid oak. The chest "
        + "is so large that it takes up almost the length of the "
        + "wall that it sits against. Inside the chest are guards "
        + "which can help fasten various types of weapons so that "
        + "they can be stored properly without harming other weapons "
        + "inside.\n\n"); 
        
    set_no_show_composite(1);
    set_enable_logging(1);
    set_rack_log_file(ELEMENTALIST_LOGS + "ec_beta_weapon_rack_log");
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
          + "   <list chest>        - An organized display of the curre"
          + "ntly stocked items\n"
          + "   <list [item name]>  - Displays only items of the specifi"
          + "ed name in stock\n"
          + "   <list [weapontype]> - Displays only items of the specifi"
          + "ed type in stock\n"
          + "   <kick chest>        - Send all non-lasting items tumbling"
          + " to the floor\n");    
}

