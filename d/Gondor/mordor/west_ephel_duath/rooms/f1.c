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
    set_short("In an open forest west of Ephel Duath");
    set_long("@@my_long@@");




    add_exit(ITH_DIR + "road/nr11", "northwest");
    add_exit(ED_W_ROOM + "f2", "east");
    add_exit(ED_W_ROOM + "f4", "southeast");
    
    here = this_object();

    plains_herbs_1();
    add_mountains();
    add_forest_floor();
    

}

string
my_long()
{
    string description1, description2;
    description1 = "To the northwest is the road leading from the crossroads "
        + "in Ithilien north to Morannon. But here is a large forest full of "
        + "bent and twisted trees. ";
    description2 = "East of here are the Ephel Duath mountains. Most of the "
        + "day they cast dark shadows across the forest, plunging it into "
        + "darkness.\n";
    return(description1 + time_description() + description2);
}

void
reset_room()
{
    set_searched(0);

    
}

