
/* 	Path To Thalassia 

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
    set_short("Path to Thalassia");
    set_long("You are swimming at the beginning (or the end, "+
        "depending on how you look at it) of a tunnel leading "+
        "to (or from) the vast city to the north. A road leads "+
        "to the north from here into the city between the high walls "+
        "made of stone. A tunnel is formed here to the southeast. "+
        "You see a large object between two buildings to the north.\n");

    add_item(({"object","large object"}),"It appears to be some "+
        "type of monument or statue from here but details are "+
        "hard to make out through the water. You will have to "+
        "swim north to survey it properly.\n");
    add_item(({"wall","walls","high wall","high walls"}),
        "The high walls stretch right from the seabed below to "+
        "high above you on both the east and west sides of you. "+
        "They appear to be made from some type of marble bricks "+
        "and are very precisely fashioned and assembled. A tunnel "+
        "forms a passageway to the southeast.\n");
    add_item("tunnel","The tunnel is formed when the walls curve "+
        "around to the southeast and meet each other at the top "+
        "and bottom, creating a circular tunnel leading off into "+
        "the distance.\n");
    add_item(({"building","buildings"}),"The buildings seem to be "+
        "constructed from the same stone bricks that the walls are "+
        "made from and have large towers atop them. Past the "+
        "buildings to the north you see a bridge.\n");
    add_item(({"city","vast city"}),"The city seems to stretch "+
        "out far to the north of here. It appears to be quite "+
        "large in size, even bigger than Gelan!\n");
    add_item("bridge","A bridge far to the north of "+
        "you seems to lead into a different section "+
        "of the city. Crowning the bridge is a large "+
        "lookout tower, presumably to keep an eye on "+
        "anyone attempting to cross it.\n");
    add_item(({"tower","tall tower","towers",
        "tall towers"}),"These towers stretch up into "+
        "the far reaches of the water above you. You "+
        "can't make it out from here but you swear that "+
        "someone is watching you from the top of the "+
        "towers.\n");

    add_swim_exit(THAL+"obelisk","north",0,1);
    add_swim_exit(THAL+"path2","southeast",0,1);
}
