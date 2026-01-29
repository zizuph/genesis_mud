#pragma save_binary
#pragma strict_types

inherit "/std/scroll";

#include <stdproperties.h>

#include "../defs.h"

void
create_scroll()
{
    set_name("sign");
    set_adj("gleaming");
    add_adj("metallic");
    set_long("It's an official looking sign, well polished.\n");

    set_file(OBJ_DIR + "sign_text");
    add_prop(OBJ_M_NO_GET, "The sign is stuck in the ground.\n");
}
