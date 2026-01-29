inherit "/d/Shire/std/room";

#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <macros.h>

//** Global Variables **//

//** Prototypes **//
void start_flood();

void
create_shire_room()
{
    FIXEUID

    set_short("Within a spacious cavern");
    set_long("You stand within a spacious cavern :P.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_M_NO_TELEPORT_FROM, "You are probably too far "+
        "underground to do that.\n");

    add_exit("/d/Shire/common/trollsh/new/tt","east");
}

void
start_flood()
{
    object flood = clone_object("/d/Shire/glaurung/f1");

    flood->move(TO,1);
    flood->flood_here();
}
