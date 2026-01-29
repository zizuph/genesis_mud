/*
 *	/d/Gondor/lebennin/road/wqroad5.c
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
    set_areadesc("box canyon");
    set_areatype(AREATYPE_ROCKY);
    set_area("northeastern");
    set_areaname("Lebennin");
    set_land("Gondor");
    set_grass("tangled, dark green");
    set_extraline(
        "Surrounded on three sides by unscalable mountains, choices "+
        "for travel are greatly reduced. The mountains climb into the sky, "+
        "nestling their rocky peaks amoung the softer clouds. A path "+
        "winds through the canyon like a river, flowing south.");
    add_exit(LEB_DIR+"road/wqroad5", "south", 0, 3);
    add_item(({"peaks","peak","white mountains","ered nimrais",
        "mountains","mountain"}), BSN(
        "Though you crane your neck to follow their bulk to the top, "+
        "you cannot see the tops of the mountains that trap you here. "+
        "They appear too high for even an eagle to see from this point, "+
        "even if they were not shrouded in the ever present clouds."));
    add_item( ({ "cloud", "clouds" }), BSN(
        "The tops of the mountains disappear into the clouds."));
    add_item(({"road","path"}), BSN(
         "More of a path than a road, it is overgrown with grass. "+
         "The path ends here in this canyon, allowing travel only back " +
         "towards the hills."));
    add_item( ({ "box canyon", "canyon" }), BSN(
        "Peaks rise steeply on three sides; only to the south is "+
        "there a path."));
    add_item("ground","The ground here is dry and rocky.\n");
}
