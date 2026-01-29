
/*  Grand Palace in Thalassia

    coder(s):   Jaacar

    history:    15. 7.03    room coded                      Jaacar

*/

#pragma save_binary
#pragma strict_types

inherit "/d/Calia/std/water_room";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

void
create_water_room()
{  
    set_short("Meeting chamber");
    set_long("You have entered the west half of the Royal "+
        "Meeting chamber. There is an enormous table here "+
        "that extends into the area to the east. To the "+
        "south is the Throne Room and the Meeting chamber "+
        "continues off to the east.\n");

    add_item(({"table", "enormous table"}), "This enormous "+
        "table is made from some type of black marble and "+
        "extends right into the other half of this room to "+
        "the east.\n");

    IN;

    add_swim_exit(THALC+"palace_1_4","east",0,1);
    add_swim_exit(THALC+"palace_1_6","south",0,1);
}
