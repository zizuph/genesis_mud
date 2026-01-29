/*
 *	/d/Gondor/anorien/road/wr14.c
 *
 *	Coded 1992 by Elessar.
 *
 *	Modification log:
 *	30-Jan-1997, Olorin:	General revision.
 *
 *  Added exits into Anorien plains. 
 *  Varian 2016
 */

#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define HARD_TO_FIND  150

public string  standing_stone();

public void
create_area_room()
{
    set_areadesc("green forest field");
    set_areatype(8);
    set_area("west, northwest");
    set_areaname("Anorien");
    set_land("Gondor");
    set_grass("spicy, light green grass");
    set_forest("Firien Forest");
    set_extraline("You are in the middle of the " +forest+ ", surrounded by "
           + "trees and bushes. From the west an old road comes running in, "
           + "continuing towards the east.");
    add_item(({"stone","standing stone","marker"}), standing_stone);

    set_no_exit_msg(({"south","southeast"}),
        "The dense foliage of the Firien Wood is too thick here for " +
        "you to enter. You will probably have to follow the road from " +
        "here.\n");
    set_no_exit_msg(({"southwest","northwest"}),
        "You see the running waters of the Mering Stream blocking your " +
        "path in that direction. You will probably have to follow the road " +
        "west across the bridge to get to the other side.\n");

    add_exit(ROH_DIR + "road/mering", "west", 0, 3);
    add_exit(ANO_DIR + "road/wr13",   "east", 0, 3);
    add_exit(ANO_DIR + "plains/an1w2n","north",0,5,1);
    add_exit(ANO_DIR + "plains/an2w2n","northeast",0,5,1);
}

public string
standing_stone()
{
    object  tp = TP;
    int     awareness = tp->query_skill(SS_AWARENESS),
            tracking = tp->query_skill(SS_TRACKING),
            location = tp->query_skill(SS_LOC_SENSE),
            intelligence = tp->query_stat(SS_INT),
            seed,
            luck;

    sscanf(OB_NUM(tp),"%d", seed);
    luck = ( 100 - (1 + random(10, seed)) * (1 + random (10, seed))) * HARD_TO_FIND / 100;

    if ((intelligence + tracking + awareness + location) < (HARD_TO_FIND + luck))
        return "You find no stone.\n";
    return BSN("Hidden among bushes south of the road, you find a standing stone. " 
      + "It seems to be very ancient. You wonder what made someone erect this stone "
      + "here, for even though it is well hidden it is evident that it has been put "
      + "here with a purpose.");
}

/*
 This was used while the plains were under construction. Now open
 Varian - August 2016

int
block()
{
    if (this_player()->query_wiz_level()) return 0;

    write("You should be able to enter the plains of Anorien soon!\n");
    return 1;
}

*/