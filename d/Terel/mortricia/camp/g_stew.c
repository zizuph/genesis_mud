inherit "/std/food";
#include <stdproperties.h>

create_food()
{
    set_name("stew");
    set_short("bowl with stew");
    set_pshort("bowls with stew");
    set_adj("hot and spicy");
    set_long("A large portion of hot and spicy stew! Your favourite!\n");
    set_amount(63);
    add_prop(OBJ_I_WEIGHT, 80);
    add_prop(OBJ_I_VOLUME, 60);
}
