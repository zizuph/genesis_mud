/* /d/Faerun/guilds/warlocks/rooms/hall05.c
 *
 * Room in the guildhall.
 * Finwe, May 2017
 *
 */

#include "/d/Faerun/defs.h"
#include "defs.h";
#include "../guild.h";
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <composite.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <tasks.h>
#include <macros.h>

inherit WARLOCK_STD_ROOM;

/*
 * Function name: create_warlock_room
 * Description  : Constructor, redefine this to configure your room
 */
public void
create_warlock_room()
{
    object board;

    add_prop(ROOM_I_INSIDE, 1);

    set_short("A dark hallway");
    set_long("This is a dark hallway in the west side of the guild. It " +
        "is empty, and echoes all sounds. Tapestries hang on the walls, " +
        "and sconces line the top of the walls. Arches lead north, south, " +
        "east, and west to other rooms in the guild.\n");

    add_flat_ceiling();
    add_walls();
    add_ground_plain();
    add_sconces();
    add_doorways();

    add_indoor_tells();

	add_exit(WARLOCK_ROOMS_DIR + "hall04", "south");

    reset_faerun_room();
}


void
reset_faerun_room()
{
    ::reset_faerun_room();
}