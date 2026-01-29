/* created by Aridor  09/07/93 */

inherit "/std/food";
#include "/sys/stdproperties.h"

create_food()
{
    set_name("fish");
    set_pname("fishes");
    add_name("weedfish");
    add_pname("weedfishes");
    set_adj("strange");
    set_short("strange weedfish");
    set_pshort("strange weedfishes");
    set_long("This fish is about 30 centimeters long and has a golden color.\n");
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 1000);
    set_amount(100);
}
