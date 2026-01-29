/*
 *	/d/Gondor/anorien/pelennor/lebennin.c
 *
 *	Coded by Elessar.
 *
 *	Modification log:
 *	30-Jan-1997, Olorin:	Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_area_room()
{
    set_area("southern");
    set_areaname("the Harlond");
    set_land("Gondor");
    set_areatype(9);
    set_areadesc("harbour-area");
    set_grass("light green");

    add_exit(PEL_DIR + "harlond",  "east", 0, 2);
    add_exit(LEB_DIR + "road/nr1", "west", 0, 2);
    set_extraline("You can see the great river Anduin flow by here, turning "+
    "from the northeast to the south. "+
    "To the east are the Rammas Echor, the great outer wall of Minas Tirith. "+
    "A long road leads west along the river here, lined by trees on both "+
    "sides. "+
    "To the east are the piers of Harlond, the harbour of Minas Tirith. ");

    add_item(({"pier","piers"}), BSN(
    "The piers of the Harlond are to the south. The "+
    "southbound river-traffic and some ships from farther away use the "+
    "piers for loading and unloading. "));
    add_item(({"wall","rammas","rammas echor"}), BSN(
    "To the northeast, you can see the great outer wall of Minas " +
    "Tirith, the Rammas Echor, surrounding the city and the Pelennor " +
    "fields. "));
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
    add_item(({"tree","trees"}), 
    "The trees are tall and straight, growing on either side of the road.\n");
    add_item("road", BSN(
    "This is the ancient road running from Pelargir in the south to Minas "+
    "Tirith, the Capital of Gondor."));
}

string
query_dir_to_gate()
{
    return "east";
}

