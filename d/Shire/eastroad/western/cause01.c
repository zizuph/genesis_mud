/*
 * Road leading to Causeway from Great East Road
 * -- Finwe, March 2005
 */

#pragma save_binary
#pragma strict_types

#include "local.h"

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

   
    extraline = "The causeway runs north and south. It is broad and " +
    "looks well travelled. Fields are on either side of the causeway. " +
    "The east fields look wet while the farmlands on the west side look " +
    "well tended. It slopes downward to a country lane.";

    set_add_road();
    set_add_brandywine();
    set_add_causeway_top();

    
    add_exit(EAST_R_DIR + "er21s5","north","@@down_off_cause@@");
    add_exit(EAST_R_DIR + "er21s5","down","@@down_off_cause@@",2,1);
    add_exit(EAST_R_DIR + "cause02","south");


}
