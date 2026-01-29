inherit "/std/food";
#include <stdproperties.h>

create_food()
{
    set_name("ration");
    set_adj("gnomish");
    set_long("Not great, but nourishing. Eat up, it's getting cold.\n");
    set_short("gnomish energy ration");
    set_pshort("gnomish energy rations");
    set_amount(250);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 150);
}

