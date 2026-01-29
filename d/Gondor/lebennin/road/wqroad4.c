/*
 *	/d/Gondor/lebennin/road/wqroad4.c
 *
 *	Coded by Mayhem.
 *
 *	Modification log:
 *	 5-Feb-1997, Olorin:	Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_area_room()
{
    set_areadesc("verdant grassland");
    set_areatype(8);
    set_area("northeastern");
    set_areaname("Lebennin");
    set_land("Gondor");
    set_grass("tangled, dark green");
    set_extraline("Grass surrounds you entirely at this point. The White "+
    "Mountains grow out of the plains across the northern horizon, "+
    "like gigantic grey and white blades of grass. A path cleaves "+
    "the vegetation like a knife, slashing north and southeast.");
    add_exit(LEB_DIR+"road/wqroad5",   "north",     0, 3);
    add_exit(LEB_DIR+"road/wqroad3",   "southeast", 0, 3);
    add_exit(LEB_DIR +"road/wqfield4", "west",      0, 2);
    add_item(({"peaks","peak","white mountains","ered nimrais","mountains","mountain"}),
    BSN("Most of the peaks of the Ered Nimrais are visible from here, "+
    "drawing closer like giants marching out of the northwest heading to Mordor."));
    add_item("grass", "Terribly overgrown and tangled, this is normal grass.\n");
    add_item(({"road","path"}), BSN(
         "More of a path than a road, it is overgrown with grass. "+
         "The path winds its way towards the mountains and back towards the river."));
    add_item("ground","The ground here is fairly dry but firm.\n");
}
