#include "defs.h"

inherit FISHBASE;

public void
create_food()
{
    set_name("scallop");
    add_name("shellfish");
    set_adj("raw");
    set_short("raw scallop");
    set_long("The scallop is a small, disc-shaped piece of meat " +
        "about a half inch across. It's not an actual shellfish, " +
        "rather it's the muscle that opens and closes the shell " +
        "of a whole scallop. The rest of the meat is inedible.\n");
    set_amount(15);
}