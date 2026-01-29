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
    set_name("death");
    set_adj("sudden");
    set_short("sudden death");
    set_pshort("sudden deaths");
    set_long("Aptly named, the Sudden Death is a drink that will "
    +"make you feel as if your heart just stopped. The potency "
    +"of this drink can be smelled from a distance.\n");
    add_prop(OBJ_I_WEIGHT, 80);
    add_prop(OBJ_I_VOLUME, 80);
}
