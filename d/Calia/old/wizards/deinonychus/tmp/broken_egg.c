inherit "/std/food";

#include <stdproperties.h>
#include <macros.h>

create_food()
{
    set_amount(0);
    set_name("egg");
    set_short("broken egg");
    set_adj("broken");
    set_long("This is a broken Easter-egg.\n" +
        "Maybe you better eat it, for there's no other use for it.\n");
}
