#include "defs.h"
#include "/d/Genesis/gsl_ships/ships.h"
#include <macros.h>

inherit THWIL_BASE_ROOM;
inherit LIBPIER;

public void
create_thwil_room()
{
    set_short("Pier");
    set_long("You are farthest east of the pier in Thwil. " +
        "The breeze carries the sound of seagulls and playing "+
        "children with it. The warm sun and the healthy sea " +
        "air fills your travel bruised body with new energy. "+ 
        "This is where the boat to Gont lands. To the west the pier " +
        "continues towards land.\nA sign is here sticking out of the " +
        "pier.\n");
    add_exit(THWIL+"h6","west",0);
    BEACH;
    add_pier_entry(MASTER_OB(TO), "Thwil", "Boat to Gont");
    initialize_pier();
}

