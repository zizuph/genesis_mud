// ROOM:  base_interior.c

    /*  Calia Domain

    HISTORY

    [99-06-16] created by Uhclem from
    [D:\CALIA\CENTRAL\BOG\INNER\LOW\BASE_INT.DOC].

    PURPOSE

    Just for testing.

    */

// INCLUSIONS AND DEFINITIONS

inherit "/d/Calia/central/bog/baseroom";

#include <stdproperties.h>
#include "defs.h"

// GLOBAL VARIABLES

string This_Location;

// FUNCTIONS

// Function:  create_interior(location, *adjacent_rooms)

/*

Purpose:  Create the room description and add standard attributes.

Arguments:  string containing the filename of this room.

Returns:  nothing.

*/

void
create_interior(string location, string *adjacent_rooms)

{

    set_long("Interior room " + location + ". This is a" +
        " balcony overlooking the fortress interior.\n");

    set_short("Interior room " + location);

    if (adjacent_rooms[0]) add_exit(adjacent_rooms[0], "north", 0, 1);
    if (adjacent_rooms[1]) add_exit(adjacent_rooms[1], "northeast", 0, 1);
    if (adjacent_rooms[2]) add_exit(adjacent_rooms[2], "east", 0, 1);
    if (adjacent_rooms[3]) add_exit(adjacent_rooms[3], "southeast", 0, 1);
    if (adjacent_rooms[4]) add_exit(adjacent_rooms[4], "south", 0, 1);
    if (adjacent_rooms[5]) add_exit(adjacent_rooms[5], "southwest", 0, 1);
    if (adjacent_rooms[6]) add_exit(adjacent_rooms[6], "west", 0, 1);
    if (adjacent_rooms[7]) add_exit(adjacent_rooms[7], "northwest", 0, 1);

    /*
     *  EXITS    
     */

    add_exit(BOG_INNER_MIDDLE + location, "up", 0, 4);

    /*
     *  PROPERTIES    
     */

    add_prop(ROOM_I_HIDE, 50);  /*  Some hiding places. */
    add_prop(ROOM_I_LIGHT, 3);  /*  Full sunlight. */

    /*
     *  "uid" settings required for cloning objects.    
     */

    setuid();
    seteuid(getuid());

    /*
     *  SPECIAL FUNCTION    
     */

    /*
     *  Tell the Sanctimonian central control room that this room has been 
     *  loaded.  Function is found in /d/Calia/central/bog/baseroom.c.    
     */

    register_room();

}
