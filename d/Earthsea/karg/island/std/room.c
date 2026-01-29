inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>

void create_island_room()
{
}


nomask
void create_room()
{
// ::create_room();
 remove_prop(ROOM_I_INSIDE);
 add_prop(ROOM_I_LIGHT,1);
 create_island_room();
}
