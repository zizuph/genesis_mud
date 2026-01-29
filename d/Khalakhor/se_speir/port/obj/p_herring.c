#include "defs.h"

inherit FISHBASE;

public void
create_food()
{
    set_name("herring");
    add_name("fish");
    set_adj("pickled");
    set_short("pickled herring");
    set_long("The small herring has been cleaned, deboned, and " +
        "pickled in a brine solution. Salty, but ready to eat!\n");
    set_cooked();
    set_amount(110);
    mod_value(10);     /* 10% more expensive than raw herring. */
}
