
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
    set_long("You are inside of the Royal Palace of "+
        "Thalassia. This hallway leads off deeper into the "+
        "palace to the north and east. To the north you see "+
        "the Throne Room. The ceiling itself glows brightly, "+
        "giving off a bright light, illuminating the entire "+
        "area. The walls seem like they are made of pure "+
        "gold and they shine brightly in the light. There is "+
        "a stairway here leading up to the second floor of "+
        "the palace.\n");

    add_item(({"stairway", "stairs"}), "There is a stairway "+
        "leading up to the second floor of the palace here. "+
        "The stairs are made of the same glowing material that "+
        "the ceiling is made of.\n");
    add_item(({"wall","walls"}),"The walls appear to be "+
        "completely covered in gold.\n");
    add_item("ceiling","The ceiling glows brightly, almost "+
        "magically.\n");
    add_item("hallway","The hallway continues off to the "+
        "north and east, further into the Royal Palace.\n");

    IN;

    add_swim_exit(THALC+"palace_1_6","north",0,1);
    add_swim_exit(THALC+"palace_1_8","east",0,1);
    add_swim_exit(THALC+"palace_2_3","up",0,1);
}
