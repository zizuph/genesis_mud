/*
 *	/d/Gondor/arnor/greenway/nr2.c
 *
 *	Coded by Olorin.
 *
 *	Modification log:
 *	 6-Feb-1997, Olorin:	Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include "/d/Gondor/defs.h"

public void
create_area_room() 
{
    set_areadesc("marshy field");
    set_areatype(8);
    set_area("northern");
    set_areaname("the Greenway");
    set_land("the lost realm of Arnor");
    set_mountain("");
    set_grass("long, dark green grass");
    set_forest("Chetwood");
    set_extraline("The dark shadows of Chetwood are to the southeast. " +
        "The Greenway continues south close to the edge of the Chetwood " +
        "to meet the old east road at Bree. To the northwest, it runs " +
        "over a desolate plain towards some hills visible on the horizon.");

    add_item("chetwood","This dark forest begins to the southeast.\n");
    add_item(({"bree","bree-hill","bree hill"}), BSN(
         "This is the hill upon which a town is built. You know it to be Bree, "+
         "though you cannot make out enough details to tell for certain."));
    add_item("forest","The dark forest to the southeast is known as the Chetwood.\n");
    add_item( ({ "hills", "hill", }), 
         "These hills off in the distance are the North Downs.\n");
    add_exit(ARNOR_DIR + "greenway/nr3", "northwest", 0, 3);
    add_exit(ARNOR_DIR + "greenway/nr1", "south",     0, 3);
   
    add_item(({"greenway","road","ground"}), BSN(
    "The road is the northern part of the Greenway, which in the old days " +
    "was built by the men of Gondor and Arnor to connect the two " +
    "kingdoms. It runs from the Gap of Rohan to Fornost. Since Arnor " +
    "has fallen and is already almost forgotten, the road has fallen " +
    "into disrepair and is overgrown. "));

}
