
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
        "the northeast and southwest, as well as a large golden "+
        "pathway leading northwest towards the immense fountain "+
        "in the very centre of the city. Directly north from "+
        "here you see the cold water spring house, while to "+
        "the west you see the massive Royal Palace. Far to the "+
        "northwest, above the cold water spring house, you see the "+
        "beautiful golden dome of the Temple of Diabrecho.\n");

    add_item(({"dome","golden dome","beautiful dome","beautiful golden dome"}),
        "This massive golden dome rises up into the water far above any "+
        "other object in this city. The dome itself must be over one "+
        "hundred feet high and two hundred feet wide at the base. It sits "+
        "atop the Temple of Diabrecho.\n");

    add_item(({"temple","Temple","Temple of Diabrecho","temple of diabrecho"}),
        "The Temple of Diabrecho is far to the northwest of here. You can "+
        "only see the dome sitting high atop of it from this location.\n");

    add_item(({"garden","well kept garden"}),"The garden surrounds "+
        "the Royal Palace west of you. It appears to be well taken "+
        "care of by the citizens of this fair city.\n");

    add_item(({"palace","Palace","royal palace","Royal Palace",
        "massive royal palace","massive Royal Palace"}),
        "West of you is the Royal Palace of Thalassia, finely "+
        "constructed with colourful marble. The palace itself "+
        "is two stories tall. Surrounding the palace is a well kept "+
        "garden.\n");

    add_item(({"road","roads"}),"The roads are constructed of "+
        "polished white marble and have been carefully placed so "+
        "no vegitation grows between where the slabs have been "+
        "placed. The slabs themselves are a perfectly square, "+
        "measuring at least a bodies length on each side. The "+
        "road leads off to the northeast and southwest.\n");

    add_item(({"pathway","golden pathway","large golden pathway"}),
        "This pathway is constructed entirely of a solid sheet of "+
        "pure gold. If you could only sell this road, you would "+
        "have enough gold and platinum coins to bury yourself in "+
        "many times over. The pathway leads towards the fountain "+
        "in the centre of the citadel.\n");

    add_item(({"fountain","immense fountain"}),"To the northwest you "+
        "see a large fountain. In the middle of the fountain you see "+
        "statues made of silver and gold. Perhaps you should swim "+
        "that way if you want to take a closer look at it.\n");

    add_item(({"house","spring house","cold water spring house"}),
        "To the north you see the cold water spring house, which houses "+
        "the magical cold water spring that was granted to the citizens of "+
        "this city by Lord Diabrecho himself. From this place you cannot "+
        "see the entrance to this building.\n");

    add_swim_exit(THALC+"fountain","northwest",0,1);
    add_swim_exit(THALC+"citadel14","northeast",0,1);
    add_swim_exit(THALC+"citadel2","southwest",0,1);
}
