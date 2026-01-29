#include "defs.h"

inherit FISHBASE;

public void
create_food()
{
    set_name("monkfish");
    add_name("fish");
    set_adj("raw");
    set_short("raw monkfish");
    set_pshort("raw monkfish");
    set_long("This fish has a hideous appearance. Its bulbous eyes " +
        "are out of scale with the rest of its body, and its fins " +
        "are accompanied with bony protuberances.\n");
    set_amount(220);
}