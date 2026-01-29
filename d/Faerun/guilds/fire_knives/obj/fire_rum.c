inherit "/std/drink";
#include "/sys/stdproperties.h"

/*
 * Function name: create_drink()
 * Description  : Constructor.  Creates the drink.
 */
create_drink()
{
    set_soft_amount(10);
    set_alco_amount(70);
    set_name("rum");
    set_adj("black");
    set_short("black rum");
    set_pshort("black rums");
    set_long("Aged in oak casks and sent out to sea with some of the "
    +"sailors, this rum is at least 5 years old and has been spiced.\n");
    add_prop(OBJ_I_WEIGHT, 80);
    add_prop(OBJ_I_VOLUME, 80);
}
