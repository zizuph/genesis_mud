inherit "/std/food";
#include <stdproperties.h>

create_food()
{
    set_name("roll");
    set_adj("gnomish");
    set_long("Not great, but nourishing. Eat up, it's getting cold.\n");
    set_short("gnomish roll");
    set_pshort("gnomish rolls");
    set_amount(30);
    add_prop(OBJ_I_WEIGHT, 180);
    add_prop(OBJ_I_VOLUME, 184);
}

