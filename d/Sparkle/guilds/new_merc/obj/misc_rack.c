/*
 *  /d/Sparkle/guilds/new_merc/obj/misc_rack.c
 *
 *  This is the standard miscellaneous storage unit used in the three
 *  droproom locations of the Mercenary guild:
 *
 *      /d/Sparkle/guilds/new_merc/rooms/common_rack.c
 *      /d/Sparkle/guilds/new_merc/rooms/evil_rack.c
 *      /d/Sparkle/guilds/new_merc/rooms/good_rack.c
 *
 *  Created September 2009, by Cooper Sherry (Gorboth)
 *
 *  Special thanks to Petros for supplying the inherited code!
 */
#pragma strict_types
#include "../merc_defs.h"

inherit "/d/Genesis/specials/guilds/objs/misc_rack";


#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <formulas.h>
#include <composite.h>


/* Prototypes */
public void        create_rack();
public void        hook_print_empty_list(object for_obj);
public void        hook_list_commands(object for_obj);


/*
 * Function name:        create_rack
 * Description  :        the object constructor
 */
public void
create_rack()
{
    remove_name("rack");
    set_name("shelves");
    add_name( ({ "shelf", "number" }) );
    add_adj( ({ "many", "storage", "miscellaneous" }) );
    set_short("number of storage shelves");
    set_long("\nShelves line the walls of the room, providing ample"
      + " space to store miscellaneous items.\n\n");
} /* create_rack */


/*
 * Function:    hook_print_empty_list
 * Description: This gets called when the rack is empty.
 */
public void
hook_print_empty_list(object for_obj)
{
    for_obj->catch_tell("There is currently nothing stored on the"
      + " shelves.\n");
} /* hook_print_empty_list */


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
} /* hook_list_commands */