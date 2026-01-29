#include "defs.h"

inherit FISHBASE;

public void
create_food()
{
    set_name("crab");
    add_name("shellfish");
    set_adj("raw");
    set_short("raw crab");
    set_long("The crab, despite looking like a huge aquatic tick, " +
        "actually has quite tasty meat when cooked, particularly " +
        "in the legs.\n");
    set_amount(220);
}