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
    set_adj("apricot");
    set_short("apricot brandy");
    set_pshort("plum brandies");
    set_long("Well-made brandy flavoured with dried apricots and honey."
    +" It has a delicate fruity sweetness with a slight kick at the finish.\n");
    add_prop(OBJ_I_WEIGHT, 80);
    add_prop(OBJ_I_VOLUME, 80);
}
