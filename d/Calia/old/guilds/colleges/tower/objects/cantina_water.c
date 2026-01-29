
inherit "/std/drink";

#include <stdproperties.h>

void
create_drink()
{
    set_soft_amount(500);
    set_alco_amount(0);
    set_name("water");
    set_short("glass of water");
    set_long("This icy glass of water looks very refreshing.\n");
    add_prop(OBJ_I_VALUE, 0);
}

public string
query_recover()
{
    return 0;
}