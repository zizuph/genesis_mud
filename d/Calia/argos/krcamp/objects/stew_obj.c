/* The stew found in the stewpot
**
** Date     Coder       Action
** -------- ----------- ---------------------------------------
** 5/25/96  Zima        Created
*/
inherit "/std/food";
#include <stdproperties.h>
 
create_food() {
    set_name("spoonful of stew from the pot");
    add_name("_stew_obj");
    set_short("spoonful of stew from the pot");
    set_long("It is some stew from a stewpot.\n");
    set_amount(55);
    add_prop(OBJ_I_WEIGHT, 40);
    add_prop(OBJ_I_VOLUME, 50);
}
