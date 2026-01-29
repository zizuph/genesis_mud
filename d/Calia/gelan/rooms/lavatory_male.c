/* 	this is the neuter persons lavatory in the town Gelan

    coder(s):  Maniac & Merlin

    history:  
            31.5.95    changed graffiti object path.            Maniac 
            26.5.95    Adapted from Merlin's old lav code       Maniac

*/

#pragma save_binary

inherit "/d/Calia/std/lav";
#include "room.h"
#include <stdproperties.h>
#include <macros.h>
#include <const.h>

void
create_room()
{
    make_the_room(GELAN_ROOMS + "lavatory", 
        GELAN_DOORS + "lavatory_male",
        GELAN_TEXTS+"lm", G_MALE);
} 
