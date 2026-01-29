#include "defs.h"

inherit FISHBASE;

public void
create_food()
{
    set_name("wolffish");
    add_name("fish");
    add_adj("raw");
    set_short("raw wolffish");
    set_pshort("raw wolffish");
    set_long("This fish has marbled blue scales and large " +
        "canine-like teeth.\n");
    set_amount(220);
}