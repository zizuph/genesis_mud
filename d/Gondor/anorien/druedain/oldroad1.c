/*
 *	/d/Gondor/anorien/druedain/oldroad1.c
 *
 *	Coded by Elessar.
 *
 *	Modification log:
 *	27-Jan-1997, Olorin:	Changed inheritance,
 *				general revision.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public string  check_tracking();
public string  exa_path();

public void
create_area_room()
{
    set_areatype(7);
    set_areadesc("forgotten road");
    set_area("south");
    set_areaname("Anorien");
    set_land("Gondor");
    set_grass("soft, green");
    set_treetype("grey");
    set_forest_density(9);
    set_extraline("All around you there are more grey trees all sheltering this "+
		  "forgotten road in the Druedain Forest in southern Anorien. "+
		  "The undergrowth of the forest makes it hard to see where the "+
		  "old road once went, but you figure it continues in a southeast-ward "+
		  "direction."+check_tracking());

    add_item("road", BSN("The road was once broad enough to run a wagon along. "
      + "You guess that the ancient Dunedain used this road frequently before "
      + "the Great Plague that visited Gondor many centuries ago. Now the road "
      + "is quite covered up by the undergrowth."));
    add_item("path", exa_path);

    add_exit(ANO_DIR + "road/wr7",         "north",     test_track, 2, 0);
    add_exit(DRUEDAIN_DIR + "forest2",     "east",      test_loc,   2, 1);
    add_exit(DRUEDAIN_DIR + "oldroad2",    "southeast", test_track, 2, 0);
    add_exit(DRUEDAIN_DIR + "rangerpath1", "south",     test_track, 2, 1);
    add_exit(DRUEDAIN_DIR + "forest1",     "west",      test_loc,   2, 1);
}

public string
check_tracking()
{
    if (TP->query_skill(SS_AWARENESS) > forest_density)
	return " You also notice an old path leading south.";
    else return "";
}

public string
exa_path()
{
    if (TP->query_skill(SS_AWARENESS) > forest_density)
	return "The path seems somewhat concealed on purpose, as if someone\n"+
	    "has tried to cover it up.\n";
    else return "Your unable to find any paths here, except the old road.\n";
}
