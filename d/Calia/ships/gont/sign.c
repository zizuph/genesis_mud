/* Sign for the Gelan-Gont shipline.

   Coded by Maniac, 27/11/95 
    Changed for Gont by Jaacar, 6/09/97
*/

#pragma save_binary

inherit "/std/scroll";
#include "ship.h"
#include <stdproperties.h>

create_scroll()
{
    set_name("sign");
    set_adj("wooden");
    set_long("A small wooden sign, carved out of the trees from the "+
        "forests of Argos. You can read it.\n");
    set_file(SIGN_TEXT);
    add_prop(OBJ_M_NO_GET, "The sign is stuck in the ground.\n");
}

