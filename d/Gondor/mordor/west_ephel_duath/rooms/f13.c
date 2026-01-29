/*
 * Western slopes of Ephel Duath outdoor room
 *
 * --Raymundo, May 2020
 */

#pragma strict_types

inherit "/d/Gondor/mordor/west_ephel_duath/lib/base_room";

#include <macros.h>
#include "/d/Gondor/defs.h"
//#include "defs.h"

string my_long();

void
create_plains()
{
    set_short("Next to the Mountains of Shadow");
    set_long("@@my_long@@");


    add_exit(ED_W_ROOM + "f10", "northwest");
    add_exit(ED_W_ROOM + "f12", "west");

       
    here = this_object();

    plains_herbs_2();
    add_mountains_close("southeast", "m9");
    add_forest_floor();
    

}

string
my_long()
{
    string description1, description2;
    description1 = "The forest stops abruptly here. Great mountains "
        + "stand here, like a row of jagged teeth pushed from the "
        + "ground. ";
    description2 = "To the west the forest continues toward Ithilen. "
        + "And to the east lies Mordor. ";
    return(description1 + description2 + time_description() + "\n");
}

void
reset_room()
{
    set_searched(0);

    
}

