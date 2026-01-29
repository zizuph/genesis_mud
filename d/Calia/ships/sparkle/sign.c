#pragma save_binary

inherit "/std/scroll";
#include "ship.h"
#include <stdproperties.h>

create_scroll()
{
	set_name("sign");
	set_adj("freshly painted");
	add_adj("new");
	set_long("A new sign, that has been freshly "+
		"painted. You see blue letters and the figure of a dolphin "+
		"painted on a background of white.\n");

	set_file(SIGN_TEXT);
    add_prop(OBJ_M_NO_GET, "The sign is stuck in the ground.\n");
}

