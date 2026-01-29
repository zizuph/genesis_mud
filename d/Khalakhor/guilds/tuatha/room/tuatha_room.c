/* File         : /d/Khalakhor/guilds/tuatha/room/tuatha_room.c
 * Creator      : Teth@Genesis
 * Copyright:   : Daniel Mosquin
 * Date         : March 16, 1999
 * Purpose      : This is the base room for all rooms in the Tuatha guild
 *                area.
 * Related Files: /d/Khalakhor/std/room.c
 * Comments     :
 * Modifications:
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Khalakhor/std/room";

#include <files.h>
#include <std.h>
#include <stdproperties.h>

#include "../guild.h"

/*
 * Function    : create_tuatha_room
 * Description : Initializes and creates the tuatha room.
 * Arguments   : n/a
 * Returns     : n/a
 */
public void
create_tuatha_room()
{
}

/*
 * Function    : create_khalakhor_room (MASK)
 * Description : A masked version of the Khalakhor room creation function.
 * Arguments   : n/a
 * Returns     : n/a
 */
nomask public void
create_khalakhor_room()
{
}

/*
 * Function name: enter_inv (MASK)
 * Description  : This function is called each time an object enters a
 *                Tuatha room.
 * Arguments    : object ob  - the object entering our inventory.
 *                object old - wherever 'ob' came from. This can be 0.
 */
public void
enter_inv(object ob, object old)
{
    int level;
    string name;

    ::enter_inv(ob, old);

    if (!objectp(ob) || !interactive(ob))
        return;

    name = ob->query_real_name();

/* Add the following in when the area is opened to mortals.
    if (!(level = SECURITY->query_wiz_rank(name)))
        return;
*/
    if (SECURITY->query_wiz_dom(name) == "Khalakhor")
        return;

    if ((level = SECURITY->query_wiz_rank(name)) > WIZ_LORD)
        return;

    log_file("tuatha/violations", ctime(time()) + " " + capitalize(name) +
             " inspected:\n    " + file_name(environment(ob))+ ".\n");

    ob->catch_msg("Your presence here has been logged. Please leave now.\n");
}

