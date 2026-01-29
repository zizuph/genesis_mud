#include "local.h"
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/terrain.h"
#include "/d/Khalakhor/sys/properties.h"
#include <stdproperties.h>

inherit "/d/Khalakhor/std/room";

// Global Vars
static int gX, gY;

void create_clachdun() {}

nomask void
create_khalakhor_room()
{
    create_clachdun();
    
    if (!query_prop(ROOM_I_INSIDE))
	add_prop(ROOM_I_TWILIGHT, 1);
    reset_room();
}

int *
query_global_coords()
{
    return CLACHDUN_CORDS;
}

int *
query_local_coords()
{
    return ({gX, gY});
}

int
query_in_clachdun()
{
    return 1;
}
