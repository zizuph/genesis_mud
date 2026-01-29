#include "defs.h"

inherit "/std/container";

public void
create_container()
{
    set_name("bones");
    add_name("pile");
    add_name("pile of bones");
    set_pname("piles");
    add_pname("piles of bones");
    set_adj("cracked");
    add_adj("yellow");
    set_short("pile of cracked yellow bones");
    set_pshort("piles of cracked yellow bones");
    set_long("It's a large pile of cracked yellow bones. They " +
        "appear to be human, very old, and look like they've " +
        "gone through a meat grinder.\n");

    add_prop(OBJ_I_VALUE, 0);
}
