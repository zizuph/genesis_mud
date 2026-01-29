#include <stdproperties.h>

inherit "/std/food";

void
create_food() 
{
    set_name(({ "steak", "dinner", "steak dinner" }));
    set_pname(({ "steaks", "dinners", "steak dinners" }));
    set_short("steak dinner");
    set_pshort("steak dinners");
    set_long("This is a delicious looking steak dinner " +
        "which comes with all the fixings.\n");
    set_amount(260);
    add_prop(OBJ_I_WEIGHT,500);
    add_prop(OBJ_I_VOLUME,500);
    add_prop(OBJ_I_VALUE, 260);
}