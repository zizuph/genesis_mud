/*
 * The Causeway of East Farthing
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

   
    extraline = "The causeway is well travelled, as seen by the worn " +
    "stones. It runs parallel to the river to the east. Fields on that " +
    "side of the causeway look wet yet full of plants. On the west " +
    "are well tended and orderly farms.";

    set_add_brandywine();
    set_add_causeway_top();

    
    add_exit(EAST_R_DIR + "cause01","north");
    add_exit(EAST_R_DIR + "cause03","south");


}
