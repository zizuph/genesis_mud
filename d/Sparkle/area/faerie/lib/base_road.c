/*
 * Base file for road in Faerie
 * By Finwe, August 2004
 */

#include "defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

inherit "/std/room";
inherit S_LIB_CLOCK;
inherit COMMON_BASE;

void create_road_room() {}
void reset_room();
 
int room_num;
  
public void
create_room()
{

    reset_room();    
    set_long("Bad room long description");

    add_item(({"road", "street", "boulevard"}),
        "The road is made of white and red blocks of stone, " +
        "criss-crossing each other in a diamond pattern.\n");
    add_item("trees",
        "The trees are large with branches that form a canopy " +
        "across the road. The trees look unfamiliar, but " +
        "they are straight and tall. The leaves are large " +
        "and oval shaped. The bark is smooth to the touch " +
        "and a silver color. A dim glow surrounds each tree.\n");
/*
     add_item("sky",
        "You can make the sky from between the canopy of trees. " +
        "It's a deep azure blue without a sign of any clouds.\n");
*/
    add_item("ground",
        "You see a wide road.\n");
    add_item(({"castle"}),
        "The castle rises in the distance. It sparkles in " +
        "the sunlight and its tower rise gracefully above it.\n");
 
    create_road_room();
 
    add_prop(ROOM_I_INSIDE, 0); // This is an outdoor room
 
}

 
void
reset_room()
{
    room_num = random(4);
}
 

string vil_rd_desc1()
{
    return s_desc_sky_outside_sky() + "This is a wide, clean road, made " +
        "of stone and arranged in a geometric pattern. A row of tall " +
        "trees grows along both sides of the road shading the area " +
        "beneath its great branches. ";
}
string vil_rd_desc2()
{
    return s_desc_sky_outside_sky() + "Tall trees grow along the road " +
        "here. They shade you and create a cool area. The large road " +
        "is made of marble stones and runs through the city. The stones " +
        "are arranged in a geometric pattern. "; //A large castle rises in the distance. ";
}
string vil_rd_desc3()
{
    return s_desc_sky_outside_sky() + "This is a busy road in a large " +
        "town. The road is clean and wide, and nicely decorated by a " +
        "column of trees on either side of it. ";
}
string vil_rd_desc4()
{
    return s_desc_sky_outside_sky() + "Some tall trees that grow " +
        "alongside the road. It is wide and clean, despite the number " +
        "of elves that use it daily";
}
string vil_rd_desc5()
{
    return s_desc_sky_outside_sky() + "The road is wide. Tall trees " +
        "grow alongside it, creating a fence that is broken only by " +
        "buildings. The crowns of the tree reach up to the sky and " +
        "the branchs spread out over the road, shading all beneath " +
        "its branches.";
}
