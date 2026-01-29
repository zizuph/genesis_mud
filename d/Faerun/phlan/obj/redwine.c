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
    set_adj("red");
    set_short("red wine");
    set_pshort("red wines");
    set_long("A rich red wine from grapes of Elven Court, vinified by"
    +" the master vintners of Elventree.\n");
    add_prop(OBJ_I_WEIGHT, 80);
    add_prop(OBJ_I_VOLUME, 80);
}
