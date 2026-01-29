/* a bunch of grapes, picked from the vineyards of Argos */
inherit "/std/food";
#include <stdproperties.h>
 
create_food()
{
    set_name(({"bunch of red grapes","bunch of grapes","bunch","grapes"}));
    set_long("A bunch of red grapes.  They look delicious.\n");
    set_amount(200);
    add_prop(OBJ_I_WEIGHT, 200); /* what does an egg really weight??  */
    add_prop(OBJ_I_VOLUME, 200);
}
