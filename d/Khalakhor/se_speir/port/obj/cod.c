#include "defs.h"

inherit FISHBASE;

public void
create_food()
{
    set_name("cod");
    add_name("fish");
    set_adj("raw");
    set_short("raw cod");
    set_long("The cod has been filleted into long tender strips.\n");
    set_amount(220);
}