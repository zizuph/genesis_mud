/* A raven egg, found in nest outside window in rooms/stair2. nothing */
/* special, but the player doesn't know that ;)                       */
inherit "/std/food";
#include <stdproperties.h>
 
create_food()
{
    set_name(({"raven egg","egg"}));
    add_adj("red");
    add_adj("black_speckled");
    set_short("raven egg");
    set_long(
       "It is a red black-speckled raven egg.\n");
    set_amount(10);
    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 5);
}
