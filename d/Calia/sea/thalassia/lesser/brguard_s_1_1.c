
/* 	Bridge Guard Tower in the Lesser Zone of Thalassia

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
    set_short("On a bridge");
    set_long("You are on a bridge of sorts between two "+
        "sections of the city seperated by a circular "+
        "wall. The road you are travelling on runs north "+
        "and south from here. Towering high above you is "+
        "a large tower, covering the bridge entirely. "+
        "There is a hole in the bottom of the tower that "+
        "you can swim up through if you wanted to venture "+
        "inside of the tower.\n");
    add_item("bridge","The bridge is actually carved out "+
        "a wall of marble surrounding and dividing this "+
        "entire section of the city from the other. Many "+
        "statues are placed on pedestals lining the entire "+
        "length of the bridge.\n");
    add_item(({"statue","statues","many statues"}),"These "+
        "statues are carved out of large blocks of pure "+
        "white marble. They depict several different figures "+
        "that are most likely, or most likely have been, "+
        "prominent persons in this city.\n");
    add_item(({"wall","circular wall"}),"This wall is made "+
        "from marble blocks placed with precision to form "+
        "a large circle around the entire section of the "+
        "city. Carved out of the wall here is a bridge, "+
        "connecting these two sections of the city.\n");
    add_item(({"block","blocks"}),"The marble blocks are placed "+
        "precisely together to form the wall.\n");
    add_item(({"section","sections"}),"There seems to be several "+
        "sections of this city, each divided by a circular wall.\n");
    add_item("road","The road travels north into the Lesser "+
        "Zone of the city and south into the Major Zone.\n");
    add_item(({"major zone","Major Zone"}),"South from "+
        "here is the Major Zone of the city. This section "+
        "of the city looks to be the largest of the three sections "+
        "of the city.\n");
    add_item(({"lesser zone","Lesser Zone"}),"North from "+
        "here is the Lesser Zone of the city. This section "+
        "of the city looks to be the second largest of the "+
        "three sections of the city.\n");
    add_item(({"tower","large tower","bridge tower"}),"The "+
        "tower is made from the same white marble blocks "+
        "that the city walls are made from. It looks to be "+
        "quite tall. At the bottom of the tower is a hole "+
        "that you could swim up through if you wanted to "+
        "venture inside of it. You suspect the tower is used "+
        "for guards to monitor who crosses the bridge.\n");
    add_item("hole","There is a hole that leads up to the "+
        "inside of the marble tower that tops the bridge.\n");
    add_swim_exit(THALL+"lesser3","north",0,1);
    add_swim_exit(THALM+"major4","south",0,1);
    add_swim_exit(THALL+"brguard_s_2_1","up",0,1);
}
