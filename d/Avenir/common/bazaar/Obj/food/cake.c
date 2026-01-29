inherit "/std/food.c";
#include <stdproperties.h>
#include <macros.h>

void
create_food()
{
        set_name("cake");
        set_short("cake");
        set_long("A cake... it's hard to tell what kind, but it's edible.\n");

        set_amount(90);
        add_prop(OBJ_I_WEIGHT, 100);
        add_prop(OBJ_I_VOLUME, 100);
}
