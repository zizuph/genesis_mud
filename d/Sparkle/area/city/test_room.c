inherit "/std/room";

#include <stdproperties.h>


public void
create_room()
{
    set_short("a test room");
    set_long("This is a test room for the map.\n");

    add_prop(ROOM_S_MAP_FILE, "test_map.txt");
}
