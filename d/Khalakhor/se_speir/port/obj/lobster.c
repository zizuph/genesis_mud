#include "defs.h"

inherit FISHBASE;

public void
create_food()
{
    set_name("lobster");
    add_name("shellfish");
    set_adj("raw");
    set_short("raw lobster");
    set_long("The lobster is a beauty, though it looks something " +
        "like a huge bug. A healthy green, it's fresh out of the " +
        "water, and once boiled makes a great meal.\n");
    set_amount(400);
}