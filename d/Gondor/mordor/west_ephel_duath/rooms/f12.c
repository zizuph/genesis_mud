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
    set_short("In the shadow of Ephel Duath");
    set_long("@@my_long@@");


    add_exit(ED_W_ROOM + "f10", "northeast", 0, 0, 1);
    add_exit(ED_W_ROOM + "f11", "west");
    add_exit(ED_W_ROOM + "f14", "southwest");
    add_exit(ED_W_ROOM + "f13", "east");
    add_exit(ED_W_ROOM + "f9", "northwest");
   
    
    here = this_object();

    plains_herbs_2();
    add_mountains();
    add_forest_floor();



}

string
my_long()
{
    string description1, description2;
    description1 = "The trees here lean westward, bent and twisted, in "
        + "what could be described as a slow run away from Ephel Duath. "
        + "Deep shadows cover the forest for most of the day, plunging "
        + "the land into darkness. ";
    description2 = "Fell beasts patrol the sky, while ravens fly about "
        + "in abundance, watching everything.";
    return( description1 +time_description() + description2 +  "\n");
}

void
reset_room()
{
    set_searched(0);

    
}

