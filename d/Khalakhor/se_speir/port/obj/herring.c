#include "defs.h"

inherit FISHBASE;

public void
create_food()
{
    set_name("herring");
    add_name("fish");
    set_adj("raw");
    set_short("raw herring");
    set_long("The small herring is just as it came from the sea, " +
        "complete with head, tail and scales.\n");
    set_amount(110);
}