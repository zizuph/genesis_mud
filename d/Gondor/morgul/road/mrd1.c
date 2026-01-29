/*
 *	/d/Gondor/morgul/road/mrd1.c
 *
 *	Coded by Olorin.
 *
 *	Modification log:
 *	30-Jan-1997, Olorin:	Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/morgul/road/mroad.c";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"

public void
create_area_room()
{
    set_areatype(8);
    set_areadesc("field");
    set_area("central eastern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_extraline("The long straight road leads west towards a ring of trees, "+
    "while turns southeast-wards in the other direction, rounding under a "+
    "great shoulder of the dark mountains that dominate the eastern horizon. "+
    "The grassy fields stretch out north and south in the shadowy slopes of "+
    "the mountains, and you notice that a foul smell comes from the river "+
    "that runs further south.");
    add_item("shoulder", BSN("The great shoulder of rock looms black and " +
	"forbidding before you to the east, and the road runs southeast " +
        "around it."));
    add_item(({"mountains","mountain-range","mountain","ephel duath"}),
	BSN("The mountains named Ephel Duath are standing right before " +
	    "you. You are quite unable to see the tallest peaks."));
    add_item("cleft","You don't see much of it from this distance; it is a deep\n"+
    "gulf of shadow, and whatever is in there lies hidden in the darkness.\n"+
    "Your guess is that this is the Imlad Morgul, the Valley of Dark Sorcery.\n");
    add_item("road", BSN("The long straight road continues towards a belt " +
	"of trees to the west, while it turns southeast in the other " +
        "direction. The road is well crafted, cobbled with stones and " +
        "lined with high banks."));
    add_item(({"trees","ring of trees","belt of trees"}),
    "Not far ahead to the west, looming up like a black wall, you see a\n"+
    "belt of trees, vast of size, very ancient, and placed in a ring.\n");
    add_item(({"forest","forests","woods","flowers","bushes"}),
    "The forests are far away to the northwest.\n");
    add_item(({"river","morgulduin","stream"}),
    "The Morgulduin runs from the accursed Morgul valley, and is\n"+
    "dark and foul to look upon, and there is a wrenching smell from it.\n");
    add_exit(ITH_DIR + "road/crossroads", "west",      stop_escape, 2);
    add_exit(MORGUL_DIR + "road/mrd2",    "southeast", check_allow, 2);

    set_up_herbs( ({ HERB_DIR + "morgurth", HERB_DIR + "angurth" }), 
        ({"bank", "flat", "ground", "meadow"}), 3);

    reset_room();
    enable_reset(200);
}

