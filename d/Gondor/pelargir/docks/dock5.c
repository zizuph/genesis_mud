/*
 * /d/Gondor/pelargir/docks/dock5.c
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

static object  Sailor,
               Ship;

public void
reset_room()
{
    Sailor = add_citizen(Sailor, PELAR_DIR + "npc/sailor");
    /*
    if (objectp(Ship))
        return;

    Ship = clone_object(SHIP_DIR + "ship");
    Ship->start_ship();
    */
}

public void
create_room()
{
    set_short("amid the vast docks of Pelargir");
    set_long(BSN("You are on a very unstable dock. The boards here, "
      + "though they are good quality, jiggle when you step across them "
      + "and some may even be just rattling in the wind. The ships "
      + "that dock here must be piloted by less than sober captains "
      + "because it seems the end of the dock has been knocked off and "
      + "the sides battered a few times. The docks to the north and "
      + "south look much more sturdy and seem to be quite a bit "
      + "more decorative also. East lies the great Anduin river."));
    add_item(({"board","boards"}), BSN("These boards are chipped and "
      + "worn with age. Someone should enlist some of the sailors "
      + "wandering about to do some repair work."));
    add_dockships();
    add_anduin("docks");
    add_exit(PELAR_DIR + "docks/dock4","north",0);
    add_exit(PELAR_DIR + "docks/dock6","south",0);
    add_exit(PELAR_DIR + "streets/shipwright01", "west", 0);
    
    //clone_object(SHIP_DIR + "sparkle_sign")->move(TO);

    add_prop(ROOM_I_NO_CLEANUP,1);

    add_pier_entry(MASTER_OB(TO), "Pelargir", "Sparkle Line");
    initialize_pier();
    reset_room();
}

