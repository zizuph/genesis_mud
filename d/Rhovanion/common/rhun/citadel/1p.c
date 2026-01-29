
inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include "/d/Rhovanion/farlong.h"

create_room()
{
    set_short("Dim, narrow stair");
    set_long("This is a small stairway that, rather than winding in circular "+
        "fashion, is straight, heading downward into darkness.  You wonder "+
        "what could lie down there.  A narrow hallway leads off to the "+
        "northeast, widening as it goes.\n");

    AE(RHUN+"citadel/1o","northeast");
    AE(RHUN+"citadel/0a","down");

    add_item(({"stairs","stair","stairwell","stairway"}),"The stairs lead "+
        "downward from here, into darkness.\n");
    add_item(({"hall","hallway","northeast"}),"The hallway leads back "+
        "to the northeast, widening as it goes.\n");

    IN;

}

