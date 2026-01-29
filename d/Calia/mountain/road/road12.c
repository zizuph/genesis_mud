/* Digit 02 FEB 95 
   Modified, descriptions added  Maniac 7/3/95
   Modified, 2/5/95, Maniac
*/

#pragma save_binary

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/mountain/defs.h"

void
create_room()
{
    set_short("Beginning of the foothills");
    set_long("You are on a cobbled road through bleak moorland " +
       "in the mid-western regions of Calia. " +
       "To the southeast you can see the beginning of the northwestern " +
       "foothills of Mount Kyrus, which sweep toward the giant grey " +
       "mountain. The cobbled road you are on runs from " +
       "northwest to southeast.\n");

    add_item(({"road", "cobbled road"}),
        "A simple road through the surrounding lands, its surface " +
        "made of smallish grey stones that are " +
        "closely cobbled together. It might create a slightly " +
        "bumpy ride for carriages.\n");

    add_item(({"moor", "moorland"}),
       "A wide area of open " +
       "uncultivated moorland stretches out to the north and " +
       "northwest, with the cobbled road winding through it " +
       "on its lonely path.\n");

    add_item(({"hills", "foothills", "hill", "terrain"}), 
       "The foothills may be seen to the southeast.\n");

    add_item(({"mount kyrus", "mountain", "mount"}),
       "The great grey mountain can be seen rising " +
       "a fair way way to the southeast. Its mighty grey " +
       "mass reaches high into the sky, so that its peak is " +
       "shrouded in mist. The mountain completely dominates the " +
       "landscape for miles around it.\n");

    add_exit(ROAD+"road13","northwest");
    add_exit(ROAD+"road11","southeast", 0, 2);
    add_exit(ROAD+"m31","west");
    add_exit(ROAD+"m32","east");
    add_exit(ROAD+"m26","north");
    add_exit(ROAD+"m27","northeast");
    add_exit(ROAD+"m34","southwest");
    add_exit(ROAD+"m35","south");
}

