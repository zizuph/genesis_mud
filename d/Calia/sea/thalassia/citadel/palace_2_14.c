
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
    object administrator;

    set_short("Palace Administration Office");
    set_long("You have entered one of the Administration Offices "+
        "in the Royal Palace. There is a counter here, behind which "+
        "is one of the administration officers of the city of "+
        "Thalassia. Here is where all of the official paperwork "+
        "that runs a city of this size goes through. To the west "+
        "you see a stairway leading down to the first floor of the "+
        "palace, while to the east you see a hallway leading further "+
        "into the depths of the palace.\n");

    add_item("counter", "There is a large white marble counter here, "+
        "behind which is an administration officer of Thalassia.\n");
    add_item(({"stairs", "stairway"}), "In the room to the west you "+
        "see a stairway leading down to the first floor of the palace.\n");
    add_item(({"hallway","hall"}),"The hallway leads off to the east, "+
        "deeper into the palace itself.\n");

    IN;

    administrator=clone_object(SEA_CREATURES+"thal_admin_east");
    administrator->move(TO);
    tell_room(TO,QCTNAME(administrator) + " rises from behind the desk.\n");

    add_swim_exit(THALC+"palace_2_1","west",0,1);
    add_swim_exit(THALC+"palace_2_13","east",0,1);
}
