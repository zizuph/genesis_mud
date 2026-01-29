/*
* a dummy base file
*
* Creator ......: Shadowlynx
* Date .........: 12/30/97
*/

inherit "/d/Krynn/std/room";

#include <stdproperties.h>

/*
 * Function name: create_cave_room
 * Description  : Empty constructor for the cave rooms. This function should
 *                be masked in the individual cave rooms.
 */
void
create_cave_room()
{
}
 
/*
 * Function name: create_krynn_room
 * Description  : This function is called when the room is loaded. We use it
 *                to set some standard things for all cave rooms and then
 *                call create_cave_room() for the things specific to the
 *                individual room.
 */
void
create_krynn_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
 
    create_cave_room();
}
