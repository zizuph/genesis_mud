#include "defs.h"

inherit FISHBASE;

public void
create_food()
{
    set_name("mussel");
    add_name("shellfish");
    set_adj("raw");
    set_short("raw mussel");
    set_long("The mussel is a small black shellfish with a plump " +
        "meat inside, best eaten steamed or boiled.\n");
    set_amount(15);
}