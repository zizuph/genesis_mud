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
    set_short("A forest of twisted trees");
    set_long("@@my_long@@");


    add_exit(ED_W_ROOM + "f7", "east");
    add_exit(ED_W_ROOM + "f9", "southeast", 0, 0, 1);
    add_exit(ED_W_ROOM + "f4", "northeast");
    add_exit(ED_W_ROOM + "f8", "south");
    
    here = this_object();

    plains_herbs_2();
    add_mountains();
    add_forest_floor();

        add_item( ({"ground", "forest floor", "floor", "soil"}),
            "The ground is mostly dirt, but here and there you see some grass "
            + "struggling to take root in this harsh climate. Deep "
            + "bootprints sink into the ground here, with some drag "
            + "marks following them.\n");
        add_item( ({"print", "prints", "bootprint", "bootprints", "boot print", "boot prints", "tracks", "track"}),
            "These bootprints are quite large, perhaps as large as an "
            + "uruk-hai's or a troll's foot. They sink deeply into the "
            + "ground, as if whoever made these bootprints was carrying "
            + "something heavy. The bootprints seem to be leading toward "
            + "the mountains.\n");
        add_item( ({"line", "lines", "mark", "marks", "drag marks", "drag", "drag mark"}),
            "It appears that these marks were made by someone dragging their "
            + "feet on the ground while they were being dragged away.\n");

}

string
my_long()
{
    string description1, description2;
    description1 = "Bent and twisted trees form a forest here in the "
        + "shadow of Ephel Duath, their leaves turning brown on the "
        + "edges. ";
    description2 = "Heavy bootprints press into the ground, thin lines "
        + "just behind them as if something heavy were dragged here. ";
    return(description1 + description2 + time_description() + "\n");
}

void
reset_room()
{
    set_searched(0);

    
}

