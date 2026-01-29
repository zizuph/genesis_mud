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
    set_short("Near the Ephel Duath Mountains");
    set_long("@@my_long@@");


    add_exit(ED_W_ROOM + "f5", "northeast");
    add_exit(ED_W_ROOM + "f4", "northwest", 0, 0, 1);
    add_exit(ED_W_ROOM + "f6", "west");
    add_exit(ED_W_ROOM + "f8", "southwest", 0, 0, 1);
    add_exit(ED_W_ROOM + "f9", "south");
    add_exit(ED_W_ROOM + "f10", "southeast");
       
    here = this_object();

    plains_herbs_1();
    add_mountains_close("east", "m5");
    add_forest_floor();
    
    add_item( ({"fence", "rock fence"}), "Steep and tall, the mountains "
        + "make it nearly impossible to go any further east.\n");
}

string
my_long()
{
    string description1, description2;
    description1 = "The Mountains of Shadow, Ephel Duath, form a tall "
        + "jagged fence here, making passage to the east difficult at "
        + "best. ";
    description2 = "Cold winds race down the mountains and rattle the "
        + "leaves on the trees, casting a chill about the land. From time "
        + "to time, huge fell beasts can be seen circling the mountains "
        + "and keeping watch below.";
    return(description1 + time_description() + description2 +  "\n");
}

void
reset_room()
{
    set_searched(0);

    
}

