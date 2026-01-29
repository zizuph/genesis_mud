/*
 *	/d/Gondor/lebennin/road/wqroad2.c
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
    set_areadesc("overgrown riverside");
    set_areatype(8);
    set_area("northeastern");
    set_areaname("Lebennin");
    set_land("Gondor");
    set_grass("tangled, dark green");
    set_extraline("The river Erui slowly flows by to the east of here "+
        "under a bridge. The peaks of the White Mountains loom above the tall, "+
	"tangled grass surrounding you. The path meanders slowly through the " +
        "grass, leading west and southeast.");
    add_exit(LEB_DIR+"road/wqroad1", "southeast", 0, 3);
    add_exit(LEB_DIR+"road/wqroad3", "west",      0, 3);
    add_item(({"peaks","peak","white mountains","ered nimrais","mountains","mountain"}),
        BSN("A few of the peaks of the Ered Nimrais are visible from here, "+
        "like giants marching out of the northwest heading to Mordor."));
    add_item("grass", "Terribly overgrown and tangled, this is normal grass.\n");
    add_item(({"bridge"}), BSN(
         "Difficult to make out in the distance, it seems to be a heavy "+
         "stone affair arching over the Erui."));
    add_item(({"river","erui",}), BSN(
         "The Erui is a clear blue stream, flowing generally southwest "+
         "into the Great River Anduin."));
   add_item(({"road","path"}), BSN(
         "More of a path than a road, it is overgrown with grass. "+
         "The path winds its way towards the mountains and back towards the river."));
   add_item("ground","The ground here is fairly dry but firm.\n");
}
