/*
 * The sign Zardago puts in Sparkle to show were he intend to land his ship.
 */

inherit "/std/scroll";
#include "local.h"
#include <stdproperties.h>

create_scroll()
{
    set_name("sign");
    set_adj("old");
    add_adj("wooden");
    set_long("A sign made of old weather beaten wood. There is something " +
	"written on it.\n");

    set_file(OBJ + "sign_text");
    add_prop(OBJ_M_NO_GET, "The sign is stuck in the ground.\n");
}


