/* /d/Faerun/guilds/warlocks/rooms/hall04.c
 *
 * Room in the guildhall.
 * Finwe, May 2017
 * Finalized by Nerull, 2018
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
    add_prop(ROOM_I_INSIDE, 1);

    set_short("In a dark hallway");
    set_long("This is a rather dark hallway in the eastern "
    +"part of the underground temple. Tapestries decorate "
    +"the walls in close vicinity to the burning sconces "
    +"while arches leads west and east into other adjacent "
    +"rooms.\n");
    
    add_item(({"walls", "wall"}),
        "The walls are smooth and made of marble with sets of large "
        +"windows. Large tapestries and sconces also decorate "
        +"the walls in this area.\n");
        
    add_item(({"windows", "window"}),
        "The windows are square shaped and set in the walls. They are " +
        "opaque, and glow with " + LIGHT_DESC + ".\n");

    add_flat_ceiling();
    add_ground_plain();
    add_sconces();
    add_doorways();

    add_indoor_tells();

    add_exit(WARLOCK_ROOMS_DIR + "hall03", "west");
    add_exit(WARLOCK_ROOMS_DIR + "start", "east");
    

    reset_faerun_room();
}


void
reset_faerun_room()
{
    ::reset_faerun_room();
}