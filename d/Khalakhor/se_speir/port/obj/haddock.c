#include "defs.h"

inherit FISHBASE;

public void
create_food()
{
    set_name("haddock");
    add_name("fish");
    set_adj("raw");
    set_short("raw haddock");
    set_long("The haddock has been filleted into thick slabs " +
        "of fresh white meat.\n");
    set_amount(220);
}