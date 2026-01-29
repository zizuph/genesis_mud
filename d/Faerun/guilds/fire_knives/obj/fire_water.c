inherit "/std/drink";
#include "/sys/stdproperties.h"

/*
 * Function name: create_drink()
 * Description  : Constructor.  Creates the drink.
 */
create_drink()
{
    set_soft_amount(500);
    set_name("water");
    set_adj("well");
    set_short("well water");
    set_pshort("well waters");
    set_long("This small glass of well water looks moderately "
    +"refreshing. It has the faint "
    +"smell of salt though.\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
}
