
/* 	Thalassian Guard Barracks

    coder(s):   Jaacar

    history:    15. 7.03    room coded                      Jaacar

*/

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/std/water_room";


void
create_water_room()
{
    set_short("Guard tower sleeping chamber");
    set_long("This area acts as a sleeping chamber for "+
        "fortunate guards that have the duty of watching "+
        "the gates of this city. There are two rows of "+
        "five beds each in this area, and there appears "+
        "to be more beds to the north. The lookout area "+
        "is back to the west.\n");
    add_item(({"bed","beds","five beds","row","rows","two rows",
        "two rows of five beds"}),"These beds are constructed "+
        "from finely carved wood with some type of mattress "+
        "lying on top of the frame. There are ten beds in this "+
        "room and there appear to be more in the room to the"+
        "north.\n");

    add_swim_exit(THAL+"guard_nw_2_4","north",0,1);
    add_swim_exit(THAL+"guard_nw_2_1","east",0,1);
}




