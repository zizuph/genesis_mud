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
    set_short("At the foot of the Ephel Duath Mountains");
    set_long("@@my_long@@");


    add_exit(ED_W_ROOM + "f3", "northeast");
    add_exit(ED_W_ROOM + "f2", "northwest");
    add_exit(ED_W_ROOM + "f4", "west");
    add_exit(ED_W_ROOM + "f7", "southwest");
       
    here = this_object();

    plains_herbs_2();
    add_mountains_close("southeast", "m5");
    add_forest_floor();
    

}

string
my_long()
{
    string description1, description2;
    description1 = "At the foot of the Mountains of Shadow, the "
        + "rugged enormity of the mountains becomes apparent. "
        + "The mountains reach seemingly to the sky, their peaks "
        + "lost from sigh. ";
    description2 = "All around you, trees lean to the west, "
        + "twisted and bent, weighed down by the shadow from the "
        + "east. ";
    return(description1 + description2 + time_description() + "\n");
}

void
reset_room()
{
    set_searched(0);

    
}

