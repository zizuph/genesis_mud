/* d/Gondor/guilds/defenders/rooms/std/def_std_room.c
 *
 * Standardroom for the Defenders of the Westlands.
 *
 * Nerull 2016.
 */

#include <stdproperties.h>
#include <macros.h>
#include <time.h>
#include <ss_types.h>
#include "defs.h";

inherit "/d/Gondor/std/room.c";


/*
 * Function name: create_def_room
 * Description  : Constructor, redefine this to configure your room
 */
public void
create_def_room(void)
{
    //add_prop(ROOM_S_MAP_FILE, "defender_map.txt");
    // Redefine this
}


/*
 * Function name: create_room
 * Description  : Constructor, redefined so we can set some default properties
 */
public void
create_gondor(void)
{
   
    // The default room is an outdoor location.
    add_prop(ROOM_I_INSIDE, 1);
	add_prop(ROOM_I_LIGHT, 1);

    create_def_room();
}
