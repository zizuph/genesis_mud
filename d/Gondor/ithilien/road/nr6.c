/*
 *	/d/Gondor/ithilien/road/nr6.c
 *
 *	Coded by Olorin, 1993
 *
 *	Modification log:
 *	 1-Feb-1997, Olorin:	Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/ithilien/road/road.c";

#include "/d/Gondor/defs.h"

public void
create_area_room()
{
    set_areatype(8);
    set_areadesc("forest");
    set_area("northern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_extraline("The road cuts its way through a hillside slope that comes " +
        "running down from the mountains to the east and continues to the west. " +
        "Heather and trees and bracken scramble down and overhang the banks and " +
        "sprawl out over the old paving stones still lurking amid weeds and moss.\n");
    add_mountains(1, "only about a league");
    add_road(3);
    add_forest(2);
    add_item(({"slope","bank","banks"}),
  	"The gentle slope comes down from the Ephel Duath and continues to the " +
  	"west. It is overgrown with thickets and bushes and an occasional tree. " +
  	"The road cuts its way right through it. The banks left and right " +
  	"of the road are too steep to climb, and several large boulders seem " +
  	"to have tumbled down from them onto the road in recent times.\n");
    add_item(({"weed","weeds","moss","stones","paving stones"}), 
        "Weeds and moss are overgrowing the old paving stone of the road. " +
        "In ancient times these stones must have seen lots of traffic, " +
        "but now the road has fallen into disrepair and you are wondering " +
        "who is marching here nowadays.\n");
    add_item(({"heather","bracken","trees"}), 
        "Heather and trees and bracken scramble down from the slopes to both " +
        "sides of the road, overhanging the banks and sprawling out over " +
        "the road itself. In some places they hardly leave enough room " +
        "for a carriage or an oxen cart to pass, in other places the trees " +
        "on the slopes have been hewn randomly, the wood either burnt in " +
        "large fires or disfigured by crude runes.\n");
    add_exit(ITH_DIR + "road/nr7", "north", test_exit, 3);
    add_exit(ITH_DIR + "road/nr5", "south", test_exit, 3);
}
