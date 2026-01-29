
/* 	Thalassian Surveyors Obelisk

    coder(s):   Jaacar

    history:    15. 7.03    room coded                      Jaacar
                16. 7.03    obelisk side descriptions       Quintas

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
    set_short("At the obelisk");
    set_long("Before you, rising up out of the ground below "+
        "lies a tall obelisk. It appears at one time to have "+
        "been surrounded by five objects in a star-like pattern "+
        "however they have all but decayed, leaving only small "+
        "broken pillars. The road you have been following "+
        "continues to the north from here and then onto a "+
        "bridge, while south it runs between two walls and "+
        "appears to curve to the southeast in the distance.  "+
        "To the west and east of you lie tall towers. You "+
        "get the feeling that you are being watched from "+
        "high atop of these towers.\n");

    add_item(({"obelisk","tall obelisk"}),"This obelisk rises "+
        "up out of the ground below and is perfectly smooth "+
        "to the touch. It is shaped like a tall rectangle "+
        "topped by a pyramid. The obelisk stands about "+
        "eight feet in height. Each side of the obelisk "+
        "is decorated a different way. Perhaps you could "+
        "look at each of the four sides or the top.\n");
    add_item(({"side","sides"}),"Perhaps you could look "+
        "at one of the four sides? (first side, second "+
        "side, etc...)\n");
    add_item(({"first side","1st side","north side",
        "northern side","1 side","earth side"}),"The "+
        "northern side of the obelisk is formed from "+
        "a sheet of sandstone that has been sculpted by "+
        "time and the surrounding currents.  The way the "+
        "light and shadows shimmer over it, give you a "+
        "picture of a solid landmass of hills, mountains "+
        "and valleys undergoing constant change.\n");
    add_item(({"second side","2nd side","west side",
        "western side","2 side","water side"}),"The "+
        "western side of the obelisk is formed of blue "+
        "and green marbled malachite, with a golden vein "+
        "that looks like waves inscribed on it. This side "+
        "of the obelisk very closely resembles the same view "+
        "you'd get if you look back out into the open sea.\n");
    add_item(({"third side","3rd side","south side",
        "southern side","3 side","fire side"}),
        "This side of the obelisk is formed of garnet "+
        "with iron pyrite veins. The way the light "+
        "from above reflects from the iron pyrite gives "+
        "the illusion that this side of the pillar is "+
        "actually burning. At the bottom of this "+
        "side there is a small plaque.\n");
    add_item(({"fourth side","4th side","east side",
        "eastern side","4 side","air side"}),"The "+
        "eastern side is formed from white agate with "+
        "a bluish tint that is picked up from the waters "+
        "surrounding it. Shadows through the water splash "+
        "across it loosely resembling clouds coasting through "+
        "a clear sky.\n");
        
    add_item(({"top","obelisk top","top side","pyramid",
        "spirit side"}),"The top is a pyramid constructed "+
        "of a higly reflective obsidian. The rays of light "+
        "filtering down through the water from above chase "+
        "across the slopes of the pyramid, resembling "+
        "fleeting ghosts, or spirits of days gone by.\n");
    add_item(({"object","objects","five objects","pattern",
        "star-like pattern","pillar","pillars",
        "broken pillar","broken pillars","small pillar",
        "small pillars","small broken pillar",
        "small broken pillars","statue","statues",
        "broken statue","broken statues"}),"These small broken "+
        "objects were made of carved marble and "+
        "were most likely statues of some type. All "+
        "that remains are the crumbling pieces of "+
        "stone.\n");
    add_item(({"road","path"}),"The road you have "+
        "been following continues to the north from "+
        "here and then onto a bridge, while south it "+
        "runs between two walls and appears to curve "+
        "to the southeast in the distance.\n");
    add_item("bridge","A bridge far to the north of "+
        "you seems to lead into a different section "+
        "of the city. Crowning the bridge is a large "+
        "lookout tower, presumably to keep an eye on "+
        "anyone attempting to cross it.\n");
    add_item(({"wall","walls","two walls"}),"You are "+
        "too far from the walls to make out any great "+
        "details, but the walls appear to form a sort "+
        "of tunnel so to speak, leading back towards the "+
        "gates of this city.\n");
    add_item(({"tower","tall tower","towers",
        "tall towers"}),"These towers stretch up into "+
        "the far reaches of the water above you. You "+
        "can't make it out from here but you swear that "+
        "someone is watching you from the top of the "+
        "towers.\n");
    add_item(({"plaque","small plaque"}),"There is "+
        "some type of strange letters and writing on "+
        "the plaque. The only word you can make out "+
        "is 'THALASSIA'.\n");

    add_swim_exit(THAL+"path4","north",0,1);
    add_swim_exit(THAL+"guard_sw_1_1","west",0,1);
    add_swim_exit(THAL+"guard_se_1_2","east",0,1);
    add_swim_exit(THAL+"path3","south",0,1);
}
