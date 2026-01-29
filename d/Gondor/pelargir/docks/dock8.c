/*
 * /d/Gondor/pelargir/docks/dock8.c
 *
 * Modification log:
 * Olorin, 20-Jan-97: added ROOM_I_NO_CLEANUP
 * Ship to Gont disabled - Tapakah, 05/2009
 * Used now for Kalaman - Gelan circle line
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

    Ship = clone_object(SHIP_DIR + "ship3");
    Ship->start_ship();
  */
}

public void
create_room()
{
    set_short("amid the vast docks of Pelargir");
    set_long(BSN("This is one of the more filthy docks of Pelargir. "
      + "The smell of fish is overpowering here from the fisherfolk "
      + "plying their trade. The boards here are covered with filth "
      + "and scales, as well as various fish entrails. How the "
      + "fishermen can stand it is amazing, though they do not even "
      + "seem to notice. A warehouse stands to the southwest. The "
      + "river is lapping at the dock posts below."));
    add_dockships();
    add_anduin("docks");
    add_item(({"filth","scales","entrails"}), BSN("Fish blood, guts, "
      + "and slime cover the boards of the dock, making it quite "
      + "slippery to walk on."));
    add_item("boards", BSN("They have wide cracks in some places, "
      + "though they are mostly covered in filth."));
    add_item(({"crack","cracks"}), BSN("Through the cracks at your "
      + "feet, upon close inspection you can make out an odd layer "
      + "of planks below the dock."));
    add_item("planks", "If you climbed down you could probably stand "
      + "on them.\n");
    add_item(({"house", "warehouse", }), BSN(
        "It is a large old warehouse and looks quite deserted. It "
      + "could need a few repairs, but judging from the appearances "
      + "there seems to be little demand for warehouses in Pelargir "
      + "at this time."));
    add_exit(PELAR_DIR + "docks/dock9",      "southeast", 0);
    add_exit(PELAR_DIR + "streets/peddlers03", "south",   0);
    add_exit(PELAR_DIR + "docks/warehouse8", "southwest", 0);
    add_exit(PELAR_DIR + "docks/dock7",      "west",      0);

    add_prop(ROOM_I_NO_CLEANUP,1);

    //    clone_object(SHIP_DIR + "gont_sign")->move(TO);
    reset_room();
    add_pier_entry(MASTER_OB(TO), "Pelargir", "Kalaman - Gelan Circle");
	initialize_pier();
}

public int
climb_down(string str)
{
    string  vb = query_verb();

    NFN(CAP(vb) + " what?");
    if (vb == "down" && strlen(str))
        return 0;
    else if (vb == "climb" && str != "down")
        return 0;

    set_dircmd(str);

    TP->move_living("down", PELAR_DIR + "sewers/beldock");

    return 1;
}

public void
init()
{
    ::init();

    add_action(climb_down, "down");
    add_action(climb_down, "climb");
}

