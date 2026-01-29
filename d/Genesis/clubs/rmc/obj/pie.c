inherit "/std/food";
#include "/sys/stdproperties.h"

create_food()
{
    set_short("meat pie");
    set_name("pie");
    set_adj("meat");
    set_long("This is a meat pie, perfect for outdoor meals.\n");
    add_prop(OBJ_I_WEIGHT, 300);
    add_prop(OBJ_I_VOLUME, 400);
    set_amount(300);
}

