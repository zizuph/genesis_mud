inherit "/std/food.c";
#include <stdproperties.h>
#include <macros.h>

void
create_food()
{
        set_name("muffin");
        set_short("muffin");
        set_long("A hard muffin that has been lying out for a few days.\n");

        set_amount(30);
        add_prop(OBJ_I_WEIGHT, 65);
        add_prop(OBJ_I_VOLUME, 65);
}
