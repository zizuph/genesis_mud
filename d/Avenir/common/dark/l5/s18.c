inherit "/std/room";
#include <stdproperties.h>
#include "../dark.h"

void reset_room()
{
    cleanup_loot();
}

void
create_room()
{
    set_short("Small chamber");
    set_long("This small side chamber looks as though it was once"
	+" used for storage.  The only way out is back into the"
	+" tunnel.\n");

    add_exit(L5 + "s7","east",0);
    add_prop(ROOM_I_LIGHT,0);
    IN
}
