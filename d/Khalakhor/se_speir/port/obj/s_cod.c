#include "defs.h"

inherit FISHBASE;

public void
create_food()
{
    set_name("cod");
    add_name("fish");
    set_adj("salted");
    set_short("salted cod");
    set_long("The salted cod consists of cod fillets which have " +
        "been heavily salted and dried into tough slices.\n");
    set_amount(220);
    set_cooked();
    mod_value(20);
}