/*
 *	/d/Gondor/anorien/pelennor/harlond.c
 *
 *	Coded by Elessar.
 *
 *	Modification log:
 *	 4-Feb-1997, Olorin:	Changed inheritance,
 *				general revision.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_area_room()
{
    set_area("southern");
    set_areaname("Harlond");
    set_land("Gondor");
    set_areatype(9);
    set_areadesc("harbour-area");
    set_grass("light green");
    add_exit(PEL_DIR + "harlond",              "north", 0, 2);
    add_exit(MINAS_DIR + "harlond/pier",       "south", 0, 2);
    add_exit(MINAS_DIR + "harlond/warehouse4", "west",  0, 0);
    set_extraline("To the southeast and east are the piers of Harlond, " +
        "the harbour of Minas Tirith. The great river Anduin flows by " +
        "here, turning from the east to the south. To the west is a " +
        "warehouse and north is the Rammas Echor, the great outer wall " +
        "of Minas Tirith.");
    add_item(({"pier","piers"}), BSN(
        "The piers of the Harlond are to the south and east. The "+
        "southbound river-traffic and some ships from farther away use the "+
        "piers for loading and unloading."));
    add_item(({"wall","rammas","rammas echor"}), BSN(
        "To the north, you can see the great outer wall of Minas " +
        "Tirith, the Rammas Echor, surrounding the city and the Pelennor " +
        "fields."));
    add_item(({"harlond", "harbour", "warehouses"}), BSN(
        "The main harbour area is to the east. You can see many " +
        "piers there, and warehouses close to them, full of cargoes " +
        "brought to the Harlond from the great sea-port Pelargir, from " +
        "Lebennin, Belfalas, and countries farther away."));
    add_item(({"anduin","river","water"}), BSN(
        "The mighty river Anduin runs has a great bend here. It " +
        "flows down from the east, turning southwards to its mouths " +
        "in the Bay of Belfalas here. In this bend, there is the " +
        "Harlond, the harbour of Minas Tirith. The piers are built " +
        "far into the river, most of them running from west to east. "));
    add_item(({"warehouse"}), BSN(
        "To the west there is a warehouse. It does not look like it is " +
        "used to store cargo right now. "));
}

