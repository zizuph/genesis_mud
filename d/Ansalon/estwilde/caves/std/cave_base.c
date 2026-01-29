/*
 * The base file for caves under Estwilde plains.
 * Contains standard descriptions of cave items and special events.
 * 
 * Written by Sir Xavier, 04-09-00
 *
 */

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <stdproperties.h>
#include <composite.h>
#include <ss_types.h>
#include <macros.h>
#include DL_CLOCK

/* Inherit the Ansalon room */
inherit AR_FILE

#define CREATE "create_cave_room"
#define RESET "reset_cave_room"

/*
 * IN NORMAL CASES YOU SHOULDN'T NEED TO CHANGE ANYTHING BELOW
 */

/*
 * This function is called from the main Krynn room. It checks
 * weather or not the room should be reseted.
 * The function returns TRUE if there should be a reset.
 */
nomask public int
query_reset()
{
    if (function_exists(RESET, TO))
        return 1;
    return 0;
}


/*
 * This function is called from the main Krynn room.
 */
nomask public void
create_krynn_room()
{
    setuid();
    seteuid(getuid());

    call_other(TO, CREATE);

    reset_room();
}

/*
 * This function is called from the main Krynn room.
 */
nomask public void
reset_krynn_room()
{
    call_other(TO, RESET);
}

varargs object
clone_npc(string file, int do_not_arm)
{
    object ob;

    if (!stringp(file) || (file == ""))
        return 0;

    ob = clone_object(file);
    if (!objectp(ob))
        return 0;

    if (!do_not_arm && function_exists("arm_me",ob))
        ob->arm_me();

    ob->move_living("xxx",this_object());

    return ob;
}
