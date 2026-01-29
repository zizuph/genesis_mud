/* Bachlava is a sweet pastry found in Argos */
inherit "/std/food";
#include <stdproperties.h>
 
create_food()
{
    set_name(({"piece of bachlava","bachlava"}));
    set_short("piece of bachlava");
    set_pshort("pieces of bachlava");
    set_long(
       "It is a sweet, crusty pastry, a favorite of Argosians.\n");
    set_amount(55);
    add_prop(OBJ_I_WEIGHT, 40);
    add_prop(OBJ_I_VOLUME, 50);
}
