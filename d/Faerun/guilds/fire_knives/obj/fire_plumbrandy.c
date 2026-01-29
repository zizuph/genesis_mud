inherit "/std/drink";
#include "/sys/stdproperties.h"

/*
 * Function name: create_drink()
 * Description  : Constructor.  Creates the drink.
 */
create_drink()
{
    set_soft_amount(10);
    set_alco_amount(80);
    set_name("brandy");
    set_adj("plum");
    set_short("plum brandy");
    set_pshort("plum brandies");
    set_long("Well-made brandy flavoured with a homemade plum syrup to give "
    +"it a beautiful sweetness and just the right amount of kick.\n");
    add_prop(OBJ_I_WEIGHT, 80);
    add_prop(OBJ_I_VOLUME, 80);
}
