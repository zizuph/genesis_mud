/*
 *	/d/Gondor/anorien/pelennor/harlond.c
 *
 *	Coded by Elessar.
 *
 *	Modification log:
 *	30-Jan-1997, Olorin:	Changed inheritance.
 *
 *      10-Dec-1997, Gnadnar:   Removed the sign re the Pelargir
 *                              ferry. Confused players were waiting
 *                              for it here. :-)
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

static object  Fredor;

public void
create_area_room()
{
    set_area("southern");
    set_areaname("Pelennor");
    set_land("Gondor");
    set_areatype(9);
    set_areadesc("harbour-area");
    set_grass("light green");
    add_exit(PEL_DIR + "soutgate",           "north",     0, 2);
    add_exit(ANO_DIR + "road/rroad1",        "northeast", 0, 2);
    add_exit(MINAS_DIR + "harlond/harlond2", "south",     0, 2);
    add_exit(PEL_DIR + "lebennin",           "west",      0, 2);
    set_extraline("To the south and east are the piers and warehouses " +
	"of the Harlond, the harbour of Minas Tirith. The great river " +
	"Anduin is flowing by here, turning from the east to the south. " +
        "To the north is the Rammas Echor, the great outer wall of " +
	"Minas Tirith. A road leads northeast alongside the river.");
    add_item(({"harlond","harbour","pier","piers"}), BSN(
        "To the south, you see the piers of the harbour. There ships land that " +
        "come from Pelargir or go there. You can make out a few ocean-going " +
        "vessels, too!"));
    add_item(({"rammas","rammas echor","wall"}),BSN(
        "You can see the large wall the surround the Pelennor Fields to " +
        "the north. You can reach the southern gates by going north. "));
    add_item(({"river","anduin"}), BSN(
    "The mighty river Anduin is running by here. It comes from the east " +
    "and turns southward on his way to its mouths in the Bay of Belfalas. "+
    "In this bend lies the Harlond, the harbour of Minas Tirith."));
    reset_room();
}

public void
reset_room()
{
    Fredor = clone_npc(Fredor, COMMON_DIR + "quest/smuggler/fredor");
}

string
query_dir_to_gate()
{
    return "north";
}

