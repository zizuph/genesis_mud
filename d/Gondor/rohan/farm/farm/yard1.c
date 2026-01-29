/*
 *	/d/Gondor/olorin/farm/farm/yard1.c
 *	It belongs to a small farm in the Ered Nimrais
 *	Olorin, Nov 1992
 *	Last mod: Olorin, July 1995
 *  Modification Log:
 * 
 *  Cleaned up code: Finwe, February 2018
 */
inherit "/d/Gondor/common/lib/area_room.c";

#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void
create_area_room() 
{
    set_areadesc("farm yard");
    set_areatype(7);
    set_area("west");
    set_areaname("the White Mountains");
    set_land("Gondor");
    set_grass("dark green");
    set_treetype("oak");
    set_extraline("South of the yard is a cottage and two stables are "
      + "to the east and the west. To the north, a path disappears into "
      + "the forest. On either side of the cottage is a path. The door "
      + "of the cottage has been broken with great force.");

    add_item(({"path", "paths", }), 
        "One path is leading southwest, into what looks like a garden. "
      + "The other path, leading southeast, looks as if it has been used "
      + "a lot by horses and cattle.\n");

    add_item(({"cottage", "farm house", "house", }),
        "The cottage is a simple farm house, built from grey rocks that "
      + "probably were hewn in a quarry in the Ered Nimrais. The roof is "
      + "covered by wooden shingles. The door leading into the cottage "
      + "is broken.\n");

    add_item(({"farm", "farm yard", "yard", "clearing", }), 
        "This farm is in a small clearing in the middle of the forest. "
      + "To the southeast, the clearing seems to continue. The farm yard "
      + "lies between three buildings: the cottage to the south, and the "
      + "two stables on the west and the east.\n");

    add_item(({"stable", "stables", }), 
        "Large wooden buildings on both sides of the farm yard. They "
      + "were built from wooden boards, rather simple but efficient.\n");

    add_item("door", 
        "It is a wooden door, broken by force. Someone "
      + "probably used a heavy axe to smash it.\n");

    add_exit(FARM_DIR + "farm/path2", "north");
    add_exit(FARM_DIR + "farm/house1", "south");
    add_exit(FARM_DIR + "farm/stable1", "east");
    add_exit(FARM_DIR + "farm/stable2", "west"); 
    add_exit(FARM_DIR + "farm/garden1", "southwest");
    add_exit(FARM_DIR + "farm/path4", "southeast");
    clone_object(FARM_DIR + "farm/yardgate")->move(this_object());
//    set_noshow_obvious(1);
}
