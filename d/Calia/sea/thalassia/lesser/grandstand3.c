
/* 	Grandstand in the Lesser Zone of Thalassia

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
    add_swim_exit(THALL+"grandstand2","west",0,1);
    add_swim_exit(THALL+"grandstand4","east",0,1);
    add_swim_exit(THALL+"grandstand1","down",0,1);
}
