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
    set_short("In the shadow of the Ephel Duath mountains");
    set_long("@@my_long@@");


    add_exit(ED_W_ROOM + "f3", "east");
    add_exit(ED_W_ROOM + "f5", "southeast");
    add_exit(ED_W_ROOM + "f1", "west");
    add_exit(ED_W_ROOM + "f4", "southwest", 0, 0, 1);
    
    here = this_object();

    plains_herbs_2();
    add_mountains();
    add_forest_floor();
    

}

string
my_long()
{
    string description1, description2;
    description1 = "The Ephel Duath mountains tower over the forest, "
        + "like a dark storm brewing. They push from the ground "
        + "almost straight up, forming a jagged rock wall. ";
    description2 = "Twisted trees grow here, bending westward as if "
        + "they're trying to flee what's coming. ";
    return(description1 + description2 + time_description() + "\n");
}

void
reset_room()
{
    set_searched(0);

    
}

