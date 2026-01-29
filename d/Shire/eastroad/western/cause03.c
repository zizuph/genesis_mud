/*
 * The Causeway of East Farthing
 * -- Finwe, March 2005
 */

#pragma save_binary
#pragma strict_types

#include "local.h"

#define MAG_DIR     "/d/Shire/maggot/rooms/"

inherit BASE_COMMON;
inherit EAST_ROAD;

void
create_er_room()
{
    areadesc = "broad causeway";
    area = "along";
    areaname = "the Brandywine river";
    land = "Eriador";
    areatype = 0;

   
    extraline = "The causeway runs deeper south into the Shire, but is " +
    "inaccessible at this time. A lane meets up from the west, and " +
    "leads off into farmland. The river flows lazily to the east.";

    set_add_brandywine();
    set_add_causeway_top();

    
    add_exit(EAST_R_DIR + "cause02","north");
    add_exit(MAG_DIR + "maggotlane01","west", "@@down_off_cause@@");
    add_exit(MAG_DIR + "maggotlane01","down", "@@down_off_cause@@",2,1);


}
