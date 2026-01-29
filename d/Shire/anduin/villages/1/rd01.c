/*
 * Village road in the Vales of anduin
 * By Finwe, August 2005
 */
 
#pragma strict_types
 
#include "local.h"

inherit "/d/Shire/anduin/base_villages";


void
create_vil_room()
{
    areadesc = "broad road";
    area = "in";
    areaname = "the village";
    land = "Wilderland";
    areatype = 0;
   
    extraline = "The road crosses through meadows, running east and west. " +
        "Bushes and trees grow on either side of it. Tall mountains loom " +
        "in the distance to the west.";

    set_add_road();
    set_add_all_rooms();
    set_add_mirk_far();
    reset_shire_room();

    add_exit("square", "west");
    add_exit("rd02", "east");
}

void reset_shire_room()
{
}
