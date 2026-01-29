/*

   Diamond

    lavatory_female.c
    -----------------

    Coded ........: May 1997
    By ...........: Kentari

    Latest update : May 1997
    By ...........: Kentari

        Taken virtually directly from the lavatory in gelan:
    coder(s):  Maniac & Merlin

    history:  
            31.5.95    changed graffiti object path.            Maniac 
            26.5.95    Adapted from Merlin's old lav code       Maniac
*/

#pragma save_binary

inherit "/d/Calia/std/lav";
#include "../local.h"
#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <const.h>

void
create_room()
{
    make_the_room(DIROOM + "bathrm",
        DIDOORS + "lavatory_female",
        GELAN_TEXTS+"lf", G_FEMALE);
} 
