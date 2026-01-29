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
    set_short("A twisted forest at the base of the Mountains of Shadow");
    set_long("@@my_long@@");


    add_exit(ED_W_ROOM + "f5", "southwest");
    add_exit(ED_W_ROOM + "f2", "west");
       
    here = this_object();

    plains_herbs_2();
    add_mountains_close("up", "m1");
    add_forest_floor();
    

}

string
my_long()
{
    string description1, description2;
    description1 = "Within the forest, the air feels opressive. Either "
        + "it is ominously still or a bitter, cold wind blows from the "
        + "east. ";
    description2 = "The mountains look so high from this close that you "
        + "can't see the tops of them. The parts of the mountains you "
        + "can see look inhospitable, covered with boulders and shrubs. "
        + "without looking closer, you cannot see a way through them. ";
    return(time_description() + description1 + description2 + "\n");
}

void
reset_room()
{
    set_searched(0);

    
}

