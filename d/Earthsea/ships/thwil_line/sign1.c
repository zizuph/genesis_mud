#pragma strict_types

inherit "/std/scroll";

#include <stdproperties.h>

public void
create_scroll()
{
    set_name("sign");
    set_short("wooden sign");
    set_long("You are looking at a wooden sign attached to the " +
        "pier. It has some words engraved into the wood.\n");
    set_file("/d/Earthsea/ships/thwil_line/sign1.txt");
    add_prop(OBJ_I_NO_GET, 1);
}
