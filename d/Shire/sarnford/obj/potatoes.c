#include <stdproperties.h>

inherit "/std/food";

void
create_food() 
{
    set_name(({ "potatoes", "roasted potatoes", "plate of roasted potatoes" }));
    set_pname("plates of roasted potatoes");
    set_short("plate of roasted potatoes");
    set_pshort("plates of roasted potatoes");
    set_long("This is a plate of delicious looking roasted "
      + "potatoes which are crisp and lightly salted. They look "
      + "mildly addictive.\n");
    set_amount(100);

    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_VALUE, 10);
}