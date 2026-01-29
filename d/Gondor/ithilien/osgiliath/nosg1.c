/*
 *	/d/Gondor/ithilien/osgiliath/nosg1.c
 *
 *	Coded by Elessar.
 *
 *	Modification log:
 *	 1-Feb-1997, Olorin: Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/ithilien/osgiliath/eosg_std.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_area_room()
{
    set_areatype(0);
    set_areadesc("street");
    set_area("northern");
    set_areaname("East Osgiliath");
    set_land("Ithilien");
    set_extraline("You are standing in the north end of East Osgiliath, " +
        "with old ruined stone buildings all around. A street leads " +
        "through the ancient city to the south. The street leading north " +
        "seems to end in a sudden appearance of undergrowth; it does " +
        "not look as if anyone has been maintaining the ruins for the " +
        "last few decades. Crumbled stone buildings still partly stand, " +
        "but have long since ceased to be used by civilized beings. To " +
        "the north and east are the forests of Ithilien.");
    add_item( ({ "undergrowth", "grass", }), BSN(
        "Tall wild grass, flowers and creeping bushes are making their way "+
        "into the ruins, inching their way year after year. You suspect the "+
        "once so large and glorious city will be overgrown in a century or so."));
    add_item("street", BSN(
        "The street is hardly a street anymore; green grass is growing between "+
        "the cobblestones as the undergrowth is slowly creeping into the ruins."));
    add_item( ({ "river", "anduin", }), BSN(
        "This is the river Anduin, the Great River, which has its sources in " +
	"the far north of the Middle-earth continent. It flows south through " +
        "Gondor until it comes to the Sea."));
    add_item( ({ "forest", "forests", }), BSN(
        "The green forests of Ithilien look fair and inviting, with " +
        "great ilexes of huge girth, hoary ash-trees and giant oaks."));
    add_item(({"ruins","osgiliath","city"}), BSN(
        "The ruined city Osgiliath is uninhabited, its empty streets and "+
        "houses witness of a time long gone; of peace and thriving trade. "+
        "A street runs north out of the city."));
    add_item(({"buildings","building","house","houses"}), BSN( 
        "The houses and buildings are not inhabitable anymore, all the roofs "+
        "have crashed in, and some even lack walls now."));
    add_exit(ITH_DIR + "road/rr1",        "north",           0, 2);
    add_exit(ITH_DIR + "osgiliath/eosg5", "south", check_allow, 2);
}
