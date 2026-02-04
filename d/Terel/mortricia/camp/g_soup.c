inherit "/std/food";
#include <stdproperties.h>

create_food()
{
    set_name("soup");
    set_short("bowl of mushroom soup");
    set_pshort("bowls of mushroom soup");
    set_adj("mushroom");
    set_long("It's a bowl with mushroom soup.\n");
    set_amount(30);
    add_prop(OBJ_I_WEIGHT, 40);
    add_prop(OBJ_I_VOLUME, 30);
}
