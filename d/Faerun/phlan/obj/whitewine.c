inherit "/std/drink";
#include "/sys/stdproperties.h"

/*
 * Function name: create_drink()
 * Description  : Constructor.  Creates the drink.
 */
create_drink()
{
    set_soft_amount(10);
    set_alco_amount(50);
    set_name("wine");
    set_adj("white");
    set_short("white wine");
    set_pshort("white wines");
    set_long("A light and flowery wine produced locally by the priests"
    +" of Tyr.\n");
    add_prop(OBJ_I_WEIGHT, 80);
    add_prop(OBJ_I_VOLUME, 80);
}
