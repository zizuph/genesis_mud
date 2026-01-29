#include "defs.h"

inherit FISHBASE;

public void
create_food()
{
    set_name("salmon");
    add_name("fish");
    set_adj("raw");
    set_short("raw salmon");
    set_long("The salmon is nice and lean, and completely " +
        "intact awaiting deboning and cleaning for baking, " +
        "frying, or whatever recipe you care to throw it into.\n");
    set_amount(220);
    mod_value(10);
}