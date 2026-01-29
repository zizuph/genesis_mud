/* Original by Percy
 * New easier to handle Version of the dragon, by Aridor.
 * Completely rewritten by Aridor, 5/95
 */

#include "/d/Krynn/common/defs.h"
#include <macros.h>

string dragon_room_file;

/* Calls the dragon to this place.
 * Returns: 0  dragon can't come
 *          1  dragon will come
 *          2  dragon is already here
 */
int
call_dragon_to_here()
{
    return (dragon_room_file)->call_dragon(MASTER);
}

/* Same as above, but the dragon will come to TP instead of a room.
 * This file can be inherited in both objects and rooms. Use this
 * function to call from objects and the above to call from rooms.
 */
int
call_dragon_to_player()
{
    return (dragon_room_file)->call_dragon(file_name(E(TP)));
}

void
set_on_dragon_room_path(string path)
{
    if (!dragon_room_file)
      dragon_room_file = path;
}

