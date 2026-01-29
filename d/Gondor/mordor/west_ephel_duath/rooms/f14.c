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
    set_short("At the southern edge of the forest");
    set_long("@@my_long@@");


    add_exit(ED_W_ROOM + "f12", "northeast");
    add_exit(ED_W_ROOM + "f11", "northwest");
   
    
    here = this_object();

    plains_herbs_1();
    add_mountains();
    add_forest_floor();



}

string
my_long()
{
    string description1, description2;
    description1 = "The forest ends abruptly here--not ends so much as "
        + "becomes so thick and overgrown that you cannot proceed any "
        + "direction except back to the north. ";
    description2 = "The peaks of the Ephel Duath mountains become almost "
        + "lost in the clouds, and cold wind races down the mountain from "
        + "time to time rustling the leaves on the trees. ";
    return( description1 +time_description() + description2 +  "\n");
}

void
reset_room()
{
    set_searched(0);

    
}

