#pragma strict_types

inherit "/d/Gondor/ithilien/osgiliath/eosg_std";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public int
block_ithil()
{
    if (TP->id("_ithil_monster"))
        return 1;
    return 0;
}

public void
create_area_room()
{
    set_areatype(0);
    set_areadesc("street");
    set_area("eastern");
    set_areaname("Osgiliath");
    set_land("Ithilien");
    set_extraline("You are standing in the east end of Osgiliath, with " +
        "old ruined stone buildings all around. A street leads out of " +
        "the ancient city to the east, and another cobblestoned road " +
        "leads southeast towards a stone bridge.");
    add_item( ({ "stream", "river", "morgulduin", }), BSN(
        "This is the stream Morgulduin, which has its sources in the " +
        "feared valley of Imlad Morgul, where Minas Morgul lies. You notice "+
        "that the river seems to glow with a pale, evil light, as if it was "+
        "enchanted by flowing past Minas Morgul."));
    add_item("forest", BSN("The green forests of Ithilien look fair and inviting; " +
        "great ilexes of huge girth, hoary ash-trees and giant oaks."));
    add_item(({"ruins","osgiliath","city","buildings",}), BSN(
        "The ruined city Osgiliath lies to the west, its empty streets and "+
       "houses witness of a time long gone; of peace and thriving trade. "+
        "A street runs west into the city."));

    add_exit(ITH_DIR + "osgiliath/eosg1",    "east",      check_allow, 2);
    add_exit(ITH_DIR + "osgiliath/sbridge2", "southeast", block_ithil, 2);
    add_exit(ITH_DIR + "osgiliath/eosg5",    "west",      0, 2);
}
