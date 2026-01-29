
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
    set_short("Royal Palace Entranceway");
    set_long("You are at the entranceway of the Royal Palace of "+
        "Thalassia. There are hallways that lead off to the "+
        "north and to the south. To the west and the east you "+
        "see guard rooms of some type. The ceiling itself glows "+
        "brightly, giving off a bright light, illuminating the entire "+
        "area. The walls seem like they are made of pure "+
        "gold and they shine brightly in the light.\n");
    add_item(({"guard room","guard rooms"}),"There are guard "+
        "rooms to the west and east of you, guarding the way "+
        "into the Royal Palace itself.\n");
    add_item(({"wall","walls"}),"The walls appear to be "+
        "completely covered in gold.\n");
    add_item("ceiling","The ceiling glows brightly, almost "+
        "magically.\n");
    add_item("hallway","The hallway continues off to the "+
        "north, further into the Royal Palace.\n");
    
    IN;

    add_swim_exit(THALC+"palace_1_15","north",0,1);
    add_swim_exit(THALC+"palace_1_3","west",0,1);
    add_swim_exit(THALC+"palace_1_9","east",0,1);
    add_swim_exit(THALC+"palace_1_1","south",0,1);
}
