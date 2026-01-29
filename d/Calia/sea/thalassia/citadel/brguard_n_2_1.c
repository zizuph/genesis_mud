
/* 	Bridge Guardhouse in Thalassia

    coder(s):   Jaacar

    history:    15. 7.03    room coded                      Jaacar

*/

#pragma save_binary
#pragma strict_types

inherit "/d/Calia/std/water_room";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

void
create_water_room()
{
    set_short("In the bridge guard tower");
    set_long("You are at the bottom of the tower crowning the "+
        "bridge between these two sections of the city. On the "+
        "floor below you is a hole leading back down to the "+
        "bridge below. Starting here is a large spiral staircase "+
        "leading to another room above.\n");
    add_item("hole","The hole in the floor leads back out to the "+
        "bridge below.  You could swim down there quite easily.\n");
    add_item(({"stairs","staircase","spiral staircase",
        "large spiral staircase"}),"These white marble stairs run "+
        "in a spiral pattern up to the room above you.\n");
    add_swim_exit(THALC+"brguard_n_3_1","up",0,1);
    add_swim_exit(THALC+"brguard_n_1_1","down",0,1);
}
