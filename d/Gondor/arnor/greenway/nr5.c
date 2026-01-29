/*
 *	/d/Gondor/arnor/greenway/nr5.c
 *
 *	Coded by Olorin.
 *
 *	Modification log:
 *	 6-Feb-1997, Olorin:	Changed inheritance.
 *  28-Apr-2002, By Finwe of the Shire, updated for new Bree recode

 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include "/d/Gondor/defs.h"

public void
create_area_room() 
{
    set_areadesc("barren plain");
    set_areatype(8);
    set_area("northern");
    set_areaname("the Greenway");
    set_land("the lost realm of Arnor");
    set_mountain("");
    set_grass("long grass");
//    set_forest("Chetwood");
    set_extraline("The bleak and treeless hills of the North Downs " +
        "are rising north of you. The road continues north over a dike into " +
        "a field of ruins. To the south, it runs across the marshy plain and " +
        "dwindles in the distance.");

    add_exit(ARNOR_DIR + "fornost/dike",   "north", 0, 3);
    add_exit(ARNOR_DIR + "greenway/swamp", "east",  0, 3);
    add_exit(ARNOR_DIR + "greenway/nr4",   "south" ,0, 3);
 
    add_item(({"hill","hills","north downs","downs"}), BSN(
    "The North Downs form a line of hills running from the northeast to " +
    "the southwest. Here, at its southern end, the ridge splits up into two " +
    "branches, and in-between, there lies a small valley. "));
    add_item(({"fornost","valley","field","ruins","field of ruins"}), BSN(
    "In the small valley lying between the southern hills of the North " +
    "Downs once must have stood a mighty fortress. All that is left now " +
    "are the overgrown ruins of wide walls, great halls, and many homes. " +
    "The road enters the field of ruins to your north, running over a dike " +
    "to what long ago must have been the gates to the fortress. "));
    add_item(({"dike","gates"}), BSN(
    "Across the swamp at the foot of the hills runs an ancient dike " +
    "across what once must have been the gates of the fortress. "));
    add_item(({"plain","plains","marsh","swamp"}), BSN(
    "The marshy plain extends to the south as far as one can see. To the " +
    "north and east, at the foot of the hills, it turns into a swamp. Over the many " +
    "puddles and pools dark clouds of insects are swarming. The road " +
    "crosses the swamp over a long dike running right into the ruins. "));
    add_item(({"greenway","road","ground", "highway"}), BSN(
    "The road is the northern part of the Greenway, which in the old days " +
    "was built by the men of Gondor and Arnor to connect the two " +
    "kingdoms. It runs from the Gap of Rohan to the ruins of " +
    "Fornost lying north of the dike. Since Arnor " +
    "has fallen and is already almost forgotten, the road has fallen " +
    "into disrepair and is overgrown. "));
}
