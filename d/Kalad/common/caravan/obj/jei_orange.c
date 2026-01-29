inherit "/std/food";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_food()
{
    set_name("orange");
    set_pname("oranges");
    set_adj("fresh");
    set_short("fresh orange");
    set_pshort("fresh oranges");
    set_long("A freshly picked orange from the farmlands west of Kabal.\n");
    add_prop(OBJ_I_WEIGHT,30);
    add_prop(OBJ_I_VOLUME,30);
    set_amount(30);
}
