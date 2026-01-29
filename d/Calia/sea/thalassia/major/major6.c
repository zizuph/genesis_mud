
/* 	Major Zone of Thalassia

    coder(s):   Jaacar

    history:    15. 7.03    room coded                      Jaacar

*/

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/std/water_room";


void
create_water_room()
{
    set_short("Major Zone of Water");
    set_long("You are swimming around in the Major Zone of "+
        "Thalassia. This is the largest area of the "+
        "entire city and is almost entirely decorated with "+
        "white marble and bronze. There are roads leading off to "+
        "the west, east, south and southwest. A few statues "+
        "surround a fountain in the centre of this area. "+
        "Surrounding the statues is a small garden.\n");

    add_item(({"garden","small garden"}),"The small garden "+
        "has many different varieties of plants and flowers "+
        "that you do not recognize. It is very beautiful and "+
        "colourful. The garden surrounds a few statues that in "+
        "turn surround a fountain.\n");

    add_item(({"flower","flowers","plant","plants"}),"There are "+
        "many beautiful and colourful plants and flowers here, "+
        "but you do not recognize any of them.\n");

    add_item(({"statue","statues","few statues"}),"The statues are "+
        "expertly carved from white marble and decorated with gold, "+
        "silver, orichalcum, and gemstones. They depict sea-creatures "+
        "like a sea-elephant and a sea-lion swimming after each other "+
        "around the top of the fountain.\n");

    add_item("fountain","This fountain is as all others you have seen "+
        "in this city, upside-down and spouting air instead of water. "+
        "There are statues around the top of this fountain.\n");

    add_item(({"road","roads"}),"The roads are constructed of "+
        "polished white marble and have been carefully placed so "+
        "no vegitation grows between where the slabs have been "+
        "placed. The slabs themselves are a perfectly square, "+
        "measuring at least a bodies length on each side. The "+
        "road leads off to the west, east, south "+
        "and southwest.\n");

    add_swim_exit(THALM+"major4","west",0,1);
    add_swim_exit(THALM+"major7","east",0,1);
    add_swim_exit(THALM+"major3","southwest",0,1);
    add_swim_exit(THALM+"major5","south",0,1);
}
