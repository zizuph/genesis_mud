/*
 * /d/Gondor/pelargir/docks/dock2.c
 *
 * Modification log:
 * Olorin, 20-Jan-97: added ROOM_I_NO_CLEANUP
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/room.c";
inherit "/d/Gondor/pelargir/city_items.c";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/common/lib/gs_include.c"

#include "/d/Gondor/defs.h"

inherit "/d/Genesis/gsl_ships/lib/pier";

static object  Ship;

public void
reset_room()
{
  /*
    if (objectp(Ship))
        return;

    Ship = clone_object(SHIP_DIR + "ship7");
    Ship->start_ship();
  */
}
    
void
create_room()
{
    object  sign;

    set_short("amid the vast docks of Pelargir");
    set_long(BSN("You are on an aged dock stretching out into the "
      + "river Anduin. The port city of Pelargir lies to the west, and "
      + "there are more docks to the north and south. The river "
      + "gurgles below, as the water swirls from the Sirith joining the "
      + "Anduin past the dock north of here. East the river Anduin "
      + "expands almost beyond your vision, speckled only by a few "
      + "travelling ships."));
    add_dockships();
    add_anduin("docks");
    add_lighthouse("bay");
    add_admiral("harbour");
    add_towers();
    add_exit(PELAR_DIR + "docks/dock1","north",0);
    add_exit(PELAR_DIR + "docks/dock3","south",0);
    add_exit(PELAR_DIR + "streets/shipwright04", "west", 0);

    // The room may not be unloaded:
    add_prop(ROOM_I_NO_CLEANUP, 1);
    //sign = clone_object(SHIP_DIR + "sparkle_sign");
    //sign->set_file(SHIP_DIR + "harlond.txt");
    //sign->move(TO);

    add_pier_entry(MASTER_OB(TO), "Pelargir", "Connection to Harlond");
    initialize_pier();
    reset_room();
}


