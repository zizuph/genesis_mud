/*
 *   The storage room of the weapon shop
 */

inherit "/std/room";
inherit "/lib/store_support";

#include "/d/Faerun/defs.h"
#include </sys/stdproperties.h>


public void
create_room() {
    set_short("Example storage room");
    set_long("This is a basic storage room. Weapons bought/sold are stored " +
        "here. Mortals never see this room.\n");
    set_max_values(70, 7);
    reset_store();

    add_prop(ROOM_I_INSIDE, 1);  /* This is an inside room */
    reset_room();
}

reset_room() 
{
   reset_store();
}