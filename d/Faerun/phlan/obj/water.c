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
    set_short("water");
    set_pshort("waters");
    set_long("This small glass of well water comes from Kuto's"
    +" well. It looks refreshing.\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
}
