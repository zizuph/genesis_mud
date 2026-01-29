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
    set_short("Toward the south side of the forest");
    set_long("@@my_long@@");


    add_exit(ED_W_ROOM + "f12", "east");
    add_exit(ED_W_ROOM + "f9", "northeast", 0, 0, 1);
    add_exit(ED_W_ROOM + "f14", "southeast");
    add_exit(ED_W_ROOM + "f8", "northwest");
   
    
    here = this_object();

    plains_herbs_1();
    add_mountains();
    add_forest_floor();



}

string
my_long()
{
    string description1, description2;
    description1 = "To the east, the Mountains of Shadow loom large, "
        + "covering the forest in shadow for most of the day. The "
        + "mountains look like a fence, and from here seem impassable. ";
    description2 = "The forest is made up of trees that are bent and "
        + "twisted, as if they've been subjected to a great weight. "
        + "The forest extends a little ways to the southeast and "
        + "quite a long ways to the north. ";
    return(time_description() + description1 + description2 +  "\n");
}

void
reset_room()
{
    set_searched(0);

    
}

