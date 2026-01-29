/* 
 *	/d/Gondor/tharbad/ford/f01.c
 *
 *	Coded by Zephram.
 *
 *	Modification log:
 *	27-Jan-1997, Olorin:	Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/roads.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define HARD_TO_CLIMB  4 /* how hard is it to climb the slope? */

public int    climb();

public void
create_roads() 
{
    set_street("old stone road");
    set_where("southeast");
    set_county("Tharbad");
    set_land("Enedwaith");
    set_vegetation("hanging green moss and purple lichen");
    set_extraline("The ruins stand less dense here, probably because "
        + "this was a large square before the city decayed. The old "
        + "stone road is running through the ruins of Tharbad towards "
        + "a river to the northwest. To the southeast, the road is "
        + "running towards the old city gates. What remains " 
        + "of the harbour of Tharbad lies to the southwest, where a few "
        + "stone piers are visible. In the middle of the old square "
        + "a stone obelisk is standing.");

    add_exit(THARBAD_DIR + "ford/f02",   "northwest", climb, 3);
    add_exit(THARBAD_DIR + "road/r27",   "southeast", climb, 3);
    add_exit(THARBAD_DIR + "pier/pier1", "southwest", climb, 1);

    add_item( ({ "ruins", "city", "tharbad", }), BSN("All that "
        + "remains of the city of Tharbad are ruins. Of most houses, "
        + "there is no more left than the foundations and large "
        + "heaps of stone."));
    add_item( ({ "road", "old south road", "south road", 
                     "old stone road", }), 
        BSN("The old South Road is almost blocked by rubble from the "
            + "ruins of the city, but a narrow winding path has been "
            + "kept clear in the middle of the old road. The road "
            + "runs from the old city gates in the southeast to the "
            + "river to the northwest."));
    add_item( ({ "harbour", "piers", }), BSN("The harbour of Tharbad "
        + "is as ruinous as the rest of the city. It was built "
        + "southwest of here, and the large piers built into the "
        + "Greyflood are clearly visible from this point."));
    add_item( "square", BSN("Only the fact that the ruins are "
        + "slightly less dense than elsewhere makes you think that "
        + "this may have been a square before the city feel into "
        + "ruins. If so, then the South Road must have crossed the "
        + "square from the southeast to the northwest, while another "
        + "street went southwest to the harbour."));
    add_item( ({ "gates", "city gates", "gate", "city gate", }), BSN(
        "The city gates lie in ruins like the rest of the city. Their "
            + "remains can be seen a little off to the southeast to "
            + "both sides off the road."));
    add_item( ({"stone", "marker", "obelisk"}), BSN("This is a black "
        + "inscribed obelisk of some incredibly hard vitreous "
        + "stone. The stone says:") 
        + "\tHere is established the border of the City of Tharbad.\n"
        + "\tBy order of Tar-Aldarion of Numenor.\n");
}

/*
 * Function name: climb 
 * Description  : This function is run every time someone tries to climb 
 */
public int
climb()
{   
    object tp = TP;
    int    climb_try = (HARD_TO_CLIMB / 2 + random(HARD_TO_CLIMB) + 1),
           skill = tp->query_skill(SS_CLIMB);

    if (skill < climb_try)
    {
	tp->reduce_hit_point(climb_try - skill);
	write("You stumble and momentarily lose your footing.\n");
        say(QCTNAME(tp) + " stumbles.\n");
        return 1;
    }

    write("You climb over the rubble.\n");
    return 0;
}



