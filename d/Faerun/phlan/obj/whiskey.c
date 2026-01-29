inherit "/std/drink";
#include "/sys/stdproperties.h"


/*
 * Function name: create_drink()
 * Description  : Constructor.  Creates the drink.
 */
create_drink()
{
    set_soft_amount(10);
    set_alco_amount(100);
    set_name("whiskey");
    set_adj("bourbon");
    set_short("bourbon whiskey");
    set_pshort("bourbon whiskeys");
    set_long("This whiskey is aged 10 years in charred oak barrels."
    +" It is smooth going down and a fireball when it gets there.\n");
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 200);
}
