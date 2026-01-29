/* an olive, picked from the groves of Argos */
inherit "/std/food";
#include <stdproperties.h>
 
create_food()
{
    set_name(({"olive","argosian_olive"}));
    set_adj("green");
    set_long("It is a green olive from the groves of Argos.\n");
    set_amount(10);
    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 10);
}
