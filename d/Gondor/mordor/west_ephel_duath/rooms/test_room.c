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




//    add_exit(CAMP_ROOM_DIR + "f2", "southwest");
 
    
    here = this_object();

    plains_herbs_1();
    add_mountains();

}

string
my_long()
{
    string description1, description2;
    description1 = "You're standing in an open forest west of the Mountains of "
        + "Shadow. ";
    description2 = "To the west is Ithilien, "
        + "while to the east the Ephel Duath mountains rise like a "
        + "jagged fence.\n";
    return(description1 + time_description() + description2);
}

void
reset_room()
{
    set_searched(0);

    
}

