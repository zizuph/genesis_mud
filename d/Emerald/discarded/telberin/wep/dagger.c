inherit "/std/weapon";

#include <stdproperties.h>
#include <wa_types.h>

void
create_weapon()
{
    set_name("dagger");
    set_short("shiny dagger");
    set_adj("shiny");
    set_long("This shiny and curved dagger is of the type used by City " +
             "guards. It is quite light and useful in close quarter " +
             "fighting.\n");

    set_default_weapon(14, 15, W_KNIFE, W_SLASH | W_IMPALE, W_ANYH,  0);
    add_prop(OBJ_I_WEIGHT, 1410); 
    add_prop(OBJ_I_VOLUME,  1499);
    add_prop(OBJ_I_VALUE, 121);
}
