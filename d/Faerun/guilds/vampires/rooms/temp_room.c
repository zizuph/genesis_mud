/* /d/Faerun/guilds/vampires/rooms/temp_room.c
 *
 * Nerull 2020
 *
 */

inherit "/d/Faerun/guilds/vampires/rooms/std/vampires_std_room";

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "../guild.h";


/*
 * Function name: create_vampires_room
 * Description  : Constructor, redefine this to configure your room
 */

public void
create_vampires_room()
{
    add_prop(ROOM_I_INSIDE, 0);

    set_short("vampire-presence parkingroom");
    
    set_long("vampire-presence parkingroom.\n");
}
