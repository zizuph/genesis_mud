#pragma save_binary

inherit "/std/scroll";
#include "ship.h"
#include <stdproperties.h>

create_scroll()
{
	set_name("sign");
	set_adj("large");
	add_adj("beige");
	set_long("A large beige sign in the shape of a walnut. You can " +
                 "read it.\n");

	set_file(SIGN_TEXT);
    add_prop(OBJ_M_NO_GET, "The sign is stuck in the ground.\n");
}
