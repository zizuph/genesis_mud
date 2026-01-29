inherit "/std/drink";
#include "/sys/stdproperties.h"

/*
 * Function name: create_drink()
 * Description  : Constructor.  Creates the drink.
 */
create_drink()
{
    set_soft_amount(100);
    set_alco_amount(4);
    set_name("ale");
    set_adj("pale");
    set_short("pale ale");
    set_pshort("pale ales");
    set_long("This is a light colored, top-fermented ale from"
        +" the city of Mulmaster. It is lightly hopped and"
        +" slightly malty. A very refreshing drink.\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
}
