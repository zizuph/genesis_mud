/* /d/Faerun/guilds/fire_knives/rooms/g3.c
 *
 * Guarded exit down to the cellar.
 * 
 *
 * Nerull 2019
 *
 */

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "../guild.h";

inherit FIREKNIVES_STD_ROOM;


/*
 * Function name: create_warlock_room
 * Description  : Constructor, redefine this to configure your room
 */

public void
create_fireknives_room()
{
    add_prop(ROOM_I_INSIDE, 1);

    set_short("A guarded exit down to the cellar.");
    
    set_long(" "
    +""
    +".\n");
    
    add_item(({""}),
    " "
    +".\n");


    add_exit(FIREKNIVES_ROOMS_DIR + "c1.c", "down");
    add_exit(FIREKNIVES_ROOMS_DIR + "o0.c", "southwest");

    reset_faerun_room();
}


void
reset_faerun_room()
{
    ::reset_faerun_room();
}
