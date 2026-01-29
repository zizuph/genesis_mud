/* Sign for the Gelan-Terel shipline.

   Coded by Maniac, 27/11/95 
*/

#pragma save_binary

inherit "/std/scroll";
#include "ship.h"
#include <stdproperties.h>

create_scroll()
{
    set_name("sign");
    set_adj("crystalline");
    set_long("A crystalline sign, cut immaculately in the shape of a " +
             "dolphin. You can read it.\n");
    set_file(SIGN_TEXT);
    add_prop(OBJ_M_NO_GET, "The sign is stuck in the ground.\n");
}

