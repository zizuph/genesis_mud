
/* 	Citadel in Thalassia

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
    set_short("Citadel of Thalassia");
    set_long("You are swimming around in the citadel of "+
        "Thalassia. Definately the richest area of the "+
        "entire city, it is almost entirely decorated with "+
        "white marble and gold, as well as a fiery material "+
        "known as orichalcum. There are roads leading off to "+
        "the west and southeast. Far south from here you see "+
        "the cold water spring house, while to the southwest you "+
        "see the Temple of Diabrecho. To the southwest and far "+
        "above you sits the beautiful golden dome on the top of the "+
        "Temple of Diabrecho. To the northwest you see the bridge "+
        "leading out of the citadel into the lesser zone. In the "+
        "centre of the bridge looms the guard tower. Northeast you "+
        "see the orichalcum wall that surrounds the entire citadel. It "+
        "sparkles like fire in the lights.\n");

    add_item(({"bridge","tower","guard tower"}),"The bridge leads off to "+
        "the north into the lesser zone of the city. In the very centre "+
        "of the bridge sits the three storey guard tower.\n");

    add_item(({"wall","orichalcum wall"}),"This fiery metal surrounds the "+
        "wall that encompasses the entire citadel, except where the "+
        "bridges pass through it. When the light hits it, the metal almost "+
        "seems as though it is on fire.\n"); 

    add_item(({"dome","golden dome","beautiful dome","beautiful golden dome"}),
        "This massive golden dome rises up into the water far above any "+
        "other object in this city. The dome itself must be over one "+
        "hundred feet high and two hundred feet wide at the base. It sits "+
        "atop the Temple of Diabrecho.\n");

    add_item(({"temple","Temple","Temple of Diabrecho","temple of diabrecho"}),
        "The Temple of Diabrecho is a large structure constructed of solid "+
        "silver, making it glitter brightly in the light. Along the pediment "+
        "you can see many statues made of gold. High above you, on top of "+
        "the temple sits the golden dome.\n");

    add_item(({"statue","statues"}),"The golden statues are sculptures of "+
        "past rulers of the city as well as prominent people of the city.\n");

       add_item(({"road","roads"}),"The roads are constructed of "+
        "polished white marble and have been carefully placed so "+
        "no vegitation grows between where the slabs have been "+
        "placed. The slabs themselves are a perfectly square, "+
        "measuring at least a bodies length on each side. The "+
        "road leads off to the west and southeast.\n");

    add_item(({"house","spring house","cold water spring house"}),
        "Far to the south you see the cold water spring house, which houses "+
        "the magical cold water spring that was granted to the citizens of "+
        "this city by Lord Diabrecho himself. From this place you cannot "+
        "see the entrance to this building.\n");

    add_swim_exit(THALC+"citadel10","west",0,1);
    add_swim_exit(THALC+"citadel13","southeast",0,1);
}
