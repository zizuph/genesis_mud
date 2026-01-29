
inherit "/d/Rhovanion/lib/room";

#include "/d/Rhovanion/farlong.h"
#include <stdproperties.h>
#include <macros.h>

init()
{
    ::init();
    add_action("pray_function","pray");
    add_action("pray_function","worship");
}

create_room()
{   
    set_short("At the shrine");
    set_long("This is the center of this area of stone ruins."
    +"  Though around you stand the crumbled piles of stone and rubble, "+
    "before you stands a sight untouched by time.  A statue of gleaming "+
    "white stone stands tall atop a pedestal of the same material.  It "+
    "depicts a heavenly being-- not a man, for this figure is too "+
    "beautiful, to majestic to be mortal-- but a humanoid figure "+
    "of obvious heavenly origins.  In its hands, the figure holds "+
    "a winged helmet.  You can tell this was some sort of shrine, "+
    "a place of abject worship, at some long-forgotten time in the "+
    "past, when the ruins around you were the buildings, the homes, of "+
    "some thriving, successful population.  Exits from this "+
    "shrine, the center and focal point of the area, lead in all "+
    "directions.\n");
    
    AE(RHUN+"ruins/n_side","north");
    AE(RHUN+"ruins/ne_side","northeast");
    AE(RHUN+"ruins/e_side","east");
    AE(RHUN+"ruins/se_side","southeast");
    AE(RHUN+"ruins/s_side","south");
    AE(RHUN+"ruins/sw_side","southwest");
    AE(RHUN+"ruins/w_side","west");
    AE(RHUN+"ruins/nw_side","northwest");
    
    add_item(({"statue","figure","humanoid","being","man"}),
        "The figure depicted in the statue seems to somehow "+
        "be of heavenly origins, and wears an expression of divine "+
        "peace and harmony.  In its hands is a winged helmet.\n");
    add_item(({"winged helmet","helmet"}),"The winged helmet which the "+
        "statue figure holds in its hands is carved in intricate "+
        "detail.  You wonder if such a piece of armour ever truly "+
        "existed.\n");
}

int
pray_function()
{
    write("You kneel down and pray before the statue figure.\n");
    say(QCTNAME(TP)+" kneels down and worships the statue figure.\n");
/* Temporary-- later on, clone the Rhosgobel quest winged helmet
	here and move it to TP */
    write("Your prayers are unanswerable at this time; perhaps you should"
        +" return at a later date.\n");

    return 1;

}

