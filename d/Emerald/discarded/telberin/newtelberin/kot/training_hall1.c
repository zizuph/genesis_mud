#include "../defs.h";

inherit TELBERIN_ROOM;

#include <stdproperties.h>

void
create_telberin_room()
{
    set_short("KoT training hall");

    add_prop(ROOM_I_INSIDE, 1);

    add_exit("training_hall2", "north");
    add_exit("entrance", "west");
}
