#pragma save_binary

inherit "/std/scroll";
#include "ship.h"
#include <stdproperties.h>

create_scroll()
{
	set_name("sign");
    set_adj("black");
    set_long("It is a black sign with gold lettering painted on it. "+
        "You could probably read it.\n");

	set_file(SIGN_TEXT);
    add_prop(OBJ_M_NO_GET, "The sign is stuck in the ground.\n");
}

