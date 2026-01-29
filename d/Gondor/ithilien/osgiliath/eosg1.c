#pragma strict_types

inherit "/d/Gondor/ithilien/osgiliath/eosg_std";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_area_room()
{
    set_areatype(0);
    set_areadesc("street");
    set_area("eastern");
    set_areaname("Osgiliath");
    set_land("Ithilien");
    set_extraline("You are standing in the eastern edge of Osgiliath, and to the "+
    "east you see an old road climbing the slopes, winding further into the "+
    "lost land of Ithilien. A dark and scaring river comes flowing south of "+
    "the road, out of the East and into the Anduin somewhere south the city. "+
    "To the northeast start the green forests of Ithilien. The street you "+
    "are standing on leads into the ruins of Osgiliath to the west.");
    add_item("river", BSN("This is the river Morgulduin, which has its sources "+
    "in the feared valley of Imlad Morgul, where Minas Morgul lies. You notice "+
    "that the river seems to glow with a pale, evil light, as if it was "+
    "enchanted by flowing past Minas Morgul."));
    add_item("forest",BSN("The green forests of Ithilien look fair and inviting, "+
    "with great ilexes of huge girth, hoary ash-trees and giant oaks."));
    add_item(({"ruins","osgiliath","city"}), BSN(
    "The ruined city Osgiliath lies to the west, its empty streets and "+
    "houses witness of a time long gone; of peace and thriving trade. "+
    "A street runs west into the city."));
    add_exit(ITH_DIR + "osgiliath/eosg2", "west",           0, 1);
    add_exit(ITH_DIR + "road/er1",        "east", check_allow, 1);
}

