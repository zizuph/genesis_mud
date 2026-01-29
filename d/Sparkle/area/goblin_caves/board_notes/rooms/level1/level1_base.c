/*
 * Base room for level 1 of Sparkle goblin caves
 * - Boreaulam, August 2012
 */
inherit "/std/room";

#include <stdproperties.h>
#include "defs.h"
inherit BASE_ROOM;

/*
 * Function name:		create_room
 * Description  :		creates room
 */
void
create_room()
{
    ::create_room();
    add_prop(ROOM_S_MAP_FILE, "goblin_caves_level1.txt");

} /* create_room */