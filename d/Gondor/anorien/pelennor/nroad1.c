/*
 *	/d/Gondor/anorien/pelennor/nroad1.c
 *
 *	Coded by Elessar.
 *
 *	Modification log:
 *	30-Jan-1997, Olorin:	Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";
inherit "/d/Gondor/common/lib/drink_water.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_area_room() 
{
    set_area("southwestern");
    set_areaname("Pelennor");
    set_land("Gondor");
    set_grass("long, soft, light green");
    set_areatype(8);
    set_areadesc("grassy field");
    set_extraline("The road you are on runs south towards the First Gate "+
  "of Minas Tirith. North will take you to the northern gate of the "+
  "Rammas Echor, the great wall that surrounds the Fields of Pelennor. "+
  "A little stream runs here, coming from the mighty White Mountains to "+
  "the west, and running towards the great river Anduin to the east.");

    add_exit(PEL_DIR + "nroad2",   "north", 0, 2);
    add_exit(PEL_DIR + "citygate", "south", 0, 2);

    add_item("stream", BSN("It is just a little stream, with cold melt-water " +
	"from the snowy slopes of Mount Mindolluin. It runs under a little " +
	"bridge here, on its way towards the river Anduin."));
    add_prop(OBJ_I_CONTAIN_WATER, 1000000);
    set_drink_from("stream");
    add_item( ({ "bridge", "stone bridge", }), 
	BSN("The bridge is wide enough for " +
	"carriages and spans the little stream with a single arch. " +
        "It was built from the same stone that was used for the Rammas " +
        "Echor."));
    add_item( ({ "road", "ground", }), BSN("The road is running over " +
	"the fields of the Pelennor from the First Gate of Minas Tirith " +
        "in the south to the northern gate of the Rammas Echor. It crosses " +
        "a small stream here on a stone bridge."));
}

public void
init()
{
    ::init();

    init_drink();
}

void
drink_message(string from)
{
    write("You drink some cold water from the "+from+".\n"
       +  "You feel refreshed.\n");
    say(QCTNAME(TP) + " drinks some water from the "+from+".\n");
}

