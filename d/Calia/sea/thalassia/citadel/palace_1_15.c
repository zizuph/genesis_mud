
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
    set_short("Thalassian Royal Palace");
    set_long("You are just inside of the Royal Palace of "+
        "Thalassia. This hallway leads off deeper into the "+
        "palace to the south and back out to the Citadel to "+
        "the north. The ceiling itself glows brightly, "+
        "giving off a bright light, illuminating the entire "+
        "area. The walls seem like they are made of pure "+
        "gold and they shine brightly in the light.\n");
    add_item(({"wall","walls"}),"The walls appear to be "+
        "completely covered in gold.\n");
    add_item("ceiling","The ceiling glows brightly, almost "+
        "magically.\n");
    add_item("hallway","The hallway continues off to the "+
        "south, further into the Royal Palace.\n");

    add_prop(ROOM_I_INSIDE,1);

    add_swim_exit(THALC+"fountain","north",0,1);
    add_swim_exit(THALC+"palace_1_2","south",0,1);
}
