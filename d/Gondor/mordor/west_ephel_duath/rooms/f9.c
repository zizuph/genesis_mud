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
    set_short("The middle of the forest");
    set_long("@@my_long@@");


    add_exit(ED_W_ROOM + "f7", "north");
    add_exit(ED_W_ROOM + "f10", "east");
    add_exit(ED_W_ROOM + "f11", "southwest", 0, 0, 1);
    add_exit(ED_W_ROOM + "f12", "southeast");
    add_exit(ED_W_ROOM + "f8", "west");
    add_exit(ED_W_ROOM + "f6", "northwest", 0, 0, 1);
    
    here = this_object();

    plains_herbs_2();
    add_mountains();
    add_forest_floor();



}

string
my_long()
{
    string description1, description2;
    description1 = "In every direction, the forest stretches onward. Fell "
        + "creatures patrol the skies, and the sounds of boots and "
        + "trumpets echo in the distance often. ";
    description2 = "The ground is mostly covered in rocks and dirt, but a "
        + "few herbs grow, as well as a little bit of grass. Mountains "
        + "rise up, steep and tall, to the east. ";
    return(time_description() + description1 + description2 +  "\n");
}

void
reset_room()
{
    set_searched(0);

    
}

