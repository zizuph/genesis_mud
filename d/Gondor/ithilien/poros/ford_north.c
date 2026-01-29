/*
 *	/d/Gondor/ithilien/poros/ford_north.c
 *
 *	Coded by Olorin.
 *
 *	Modification log:
 *	 3-Feb-1997, Olorin:	Changed inheritance.
 *
 *  24-Aug-2006, Toby:      Changed room south to support the
 *                          new area Harondor.
 */
#pragma strict_types

inherit "/d/Gondor/ithilien/road/road.c";

#include "/d/Gondor/defs.h"

/* block_exit() removed to allow access to river.
public int
block_exit()
{
    write("\n\nThe fords are closed by order of the Steward of Gondor!\n\n");
    return 1;
}
*/

public void
create_area_room()
{
    set_areatype(8);
    set_areadesc("plains");
    set_area("southern");
    set_areaname("Ithilien");
    set_land("Gondor");

    add_mountains(2);
    add_road(-3);

    set_extraline("The road crosses the river Poros to the south "
      + "on the Fords of Poros. Southwest of here, there is a pier "
      + "reaching out into the river.");

    add_exit(ITH_DIR + "road/sr10",  "north",          0, 4);
    add_exit("/d/Gondor/harondor/room/road00s", "south", 0, 4);
    add_exit(ITH_DIR + "poros/pier", "southwest",      0, 2);
    add_exit(POROS_DIR + "p1",       "west",           0, 2);

    add_item(({"pier", "dock"}), BSN(
        "Southwest of the fords, a pier reaches out into the river. "
      + "You wonder who might sail up the river to reach the pier "
      + "in this desolate country."));
    add_item(({"river", "poros", "river poros", }), BSN(
        "The river Poros is the southern border of Ithilien. On the "
      + "other bank lies South Gondor which is now a debatable and "
      + "desert land. Here at the fords, the ancient Harad road is "
      + "crossing the river. The river is "
      + "running down from the southern mountains of the Ephel Duath "
      + "visible to the east to the Ethir Anduin in the west."));
    add_item(({"ford", "fords", "fords of poros", }), BSN(
        "These are the famous Fords of Poros. Here the south army of "
      + "Gondor won an important victory of the Haradrim in the year "
      + "2885 of the Third Age, but there does not seem to be anything "
      + "left to commemorate the battle. The fords themselves are "
      + "rather shallow, preventing all river traffic from going "
      + "further upriver."));
    add_item(({"road", "harad road", }), BSN(
        "The ancient trade road from Gondor to Harad, the Harad "
      + "road, is crossing the Poros at these fords. The road continues "
      + "north into southern Ithilien."));
    add_item(({"mountains", "ephel duath", "east", }), BSN(
        "The southern ranges of the Ephel Duath, the Mountains of Shadow "
      + "that are the western border of the land of Mordor, are rising "
      + "in the east. The river Poros is coming down from these mountains, "
      + "flowing rapidly to the Mouths of the Anduin in the west."));
    add_item(({"ethir anduin", "mouths of the anduin", "anduin", }), BSN(
        "To the west lie the Ethir Anduin, the Mouths of the Anduin, "
      + "where the river Anduin enter the Bay of Belfalas."));
}
