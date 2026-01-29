/*
 *	/d/Gondor/arnor/greenway/nr4.c
 *
 *	Coded by Olorin.
 *
 *	Modification log:
 *	 6-Feb-1997, Olorin:	Changed inheritance.
 *  28-Apr-2002, By Finwe of the Shire, updated for new Bree recode
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include "/d/Gondor/defs.h"

public void
create_area_room() 
{
    set_areadesc("empty plain");
    set_areatype(8);
    set_area("northern");
    set_areaname("the Greenway");
    set_land("the lost realm of Arnor");
    set_mountain("");
    set_grass("long grass");

    set_extraline("To the north, you can see the North Downs rising. " +
        "This is a lonely, wild land where the wind " +
        "sighs through tall dark green grass. Bushes and bracken " +
        "grow along the road and encroach upon it.");
   
    add_item(({"north downs","hill","hills"}), BSN(
        "The North Downs provide a welcome break to the monotonous plain "+
        "you see all around you."));
    add_item(({"plains","plain"}), BSN(
        "These plains stretch out for many green leagues, and you " +
        "see nothing other than beautiful grass on them."));

   add_item (({"grass","green grass"}), 
         "The grass is long and green and covers the plains all around you.\n");
   add_exit(ARNOR_DIR + "greenway/nr5", "north",     0, 3);
   add_exit(ARNOR_DIR + "greenway/nr3", "southeast" ,0, 3);
   
   add_item(({"greenway","road","ground"}), BSN(
       "The road is the northern part of the Greenway, which in the old days " +
       "was built by the men of Gondor and Arnor to connect the two " +
       "kingdoms. It runs from the Gap of Rohan to Fornost. Since Arnor " +
       "has fallen and is already almost forgotten, the road has fallen " +
       "into disrepair and is overgrown. "));
}
