inherit "/std/food";
#include "/sys/stdproperties.h"

create_food()
{
    set_short("some food");
    set_pshort("some food");
    set_name("food");
    add_name("smajs");
    set_pname(food");
    set_adj("some");
    set_long("It looks like you could eat it, but you don't know "+
             "what it contains.\n");
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 220);
    set_amount(200);
}

