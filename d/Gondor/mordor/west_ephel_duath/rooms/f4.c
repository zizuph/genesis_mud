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


    add_exit(ED_W_ROOM + "f1", "northwest");
    add_exit(ED_W_ROOM + "f2", "northeast", 0,0,1);
    add_exit(ED_W_ROOM + "f5", "east");
    add_exit(ED_W_ROOM + "f6", "southwest");
    add_exit(ED_W_ROOM + "f7", "southeast", 0,0,1);
    
       
    here = this_object();

    plains_herbs_1();
    add_mountains();
    add_forest_floor();
    

}

string
my_long()
{
    string description1, description2;
    description1 = "Traveling northwest will take you to the edge of "
        + "the forest on then on to the road in Ithilien. You are in the "
        + "midst of a forest of bent and twisted trees. ";
    description2 = "Mountains cast a long shadow, covering the entire "
        + "forest most of the day, driving out light and plunging the "
        + "entire area into darkness.";
    return( description1 + time_description() + description2 + "\n");
}

void
reset_room()
{
    set_searched(0);

    
}

