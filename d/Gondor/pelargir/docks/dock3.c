/*
 * /d/Gondor/pelargir/docks/dock3.c
 *
 * Modification log:
 * Olorin, 20-Jan-97: added ROOM_I_NO_CLEANUP
 * Earendil's ship temporarily disabled (will be reused a bit later
 * Tapakah, 05/2009
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/room";
inherit "/d/Gondor/pelargir/city_items.c";
inherit "/d/Genesis/gsl_ships/lib/pier";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/common/lib/gs_include.c"

#include "/d/Gondor/defs.h"

object  Sailor,
        Ship;

void
reset_room()
{
    Sailor = add_citizen(Sailor, PELAR_DIR + "npc/sailor");
    /* will be resumed soon, I hope - Tapakah
    if (objectp(Ship))
        return;
    Ship = clone_object(SHIP_DIR + "ship2");
    Ship->start_ship();
    */
}

public void
create_room()
{
    set_short("amid the vast docks of Pelargir");
    set_long(BSN("You are standing on a sturdy dock on the eastern "
      + "edge of Pelargir. This dock is relatively clean and free of "
      + "debris so you might guess that it is well travelled. Below, "
      + "under the dock, you can hear the lapping of the river waters on "
      + "the supports. To the north and south you can see ships at other "
      + "docks, and the great Anduin river flows smoothly by to the east."));
    add_dockships();
    add_anduin("docks");
    add_exit(PELAR_DIR + "docks/dock2","north",0);
    add_exit(PELAR_DIR + "docks/dock4","south",0);
    add_exit(PELAR_DIR + "streets/shipwright03", "west", 0);

    //clone_object(SHIP_DIR + "faerie_sign")->move(TO);

    // The room may not be unloaded:
    add_prop(ROOM_I_NO_CLEANUP, 1);

    reset_room();
	add_pier_entry(MASTER_OB(TO), "Pelargir", "Newbie Line D");
	initialize_pier();
}
