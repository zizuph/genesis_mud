/* /d/Earthsea/std/room.c
 */

#pragma strict_types
#pragma no_clone

inherit "/std/room";

#include <stdproperties.h>

public void create_earthsea_room() { }

public nomask void
create_room()
{
    ::create_room();
    create_earthsea_room();
}
