/*
 *	/d/Gondor/rohan/road/helmsroad.c
 *
 *	Coded by ???.
 *
 *	Modification log:
 *	28-Jan-1997, Olorin:	Changed inheritance,
 *				general revision.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/roads.c";

#include "/d/Gondor/defs.h"

public void
create_roads() 
{
    set_street("well-travelled, dirty road");
    set_where("northwest");
    set_county("Westmark");
    set_land("Rohan");
    set_mountain("Ered Nimrais");
    set_vegetation("green, spicy, long grass");
    set_extraline("A valley opens in front of you to the southwest, steep "+
        "mountainsides sloping down from tall peaks west and south of "+
        "here. Two roads merge here, entering from the north and east, "+
        "joining to continue into the valley in the White Mountains. "+
        "A stream gently flows down beside the road.");
    add_exit(ROH_DIR + "road/wr5", "east",  0, 3);
    add_exit(ROH_DIR + "road/wr6", "north", 0, 3);
    add_exit(ROH_DIR + "horn/coomb/low_vale", "southwest", 0, 2);
}

