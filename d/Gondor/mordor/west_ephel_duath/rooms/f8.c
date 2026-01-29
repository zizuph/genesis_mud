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
    set_short("A forest near the Mountains of Shadow");
    set_long("@@my_long@@");


    add_exit(ED_W_ROOM + "f7", "northeast", 0, 0, 1);
    add_exit(ED_W_ROOM + "f9", "east");
    add_exit(ED_W_ROOM + "f6", "north");
    add_exit(ED_W_ROOM + "f11", "southeast");
    
    here = this_object();

    plains_herbs_1();
    add_mountains();
    add_forest_floor();

    add_item( ({"bramble", "bush", "bushes", "briar", "briars", "brambles"}),
        "The brambles and briars are thick and thorny. They grow amongst and "
        + "in some cases up the trees, turning the forest into a thorn-covered "
        + "wall.\n");

}

string
my_long()
{
    string description1, description2;
    description1 = "To the west, the forest becomes too overgrown to "
        + "travel through, with thick brambles and briars blocking the way. ";
    description2 = "The trees growing here bend westward, seeming to reach "
        + "out for what little sunlight is available here. Dark shadows "
        + "cover the land for most of the day. ";
    return(description1 + description2 + time_description() + "\n");
}

void
reset_room()
{
    set_searched(0);

    
}

