#include <stdproperties.h>
#include <formulas.h>

inherit "/std/drink";

void
create_drink() 
{
    set_name(({"gin","mirkwood gin"}));
    set_pname(({"gin","mirkwood gins"}));
    set_short("Mirkwood gin");
    set_pshort("Mirkwood gins");
    set_long("Originally brewed by the woodsmen as a herbal remedy, " +
        "this gin is made from the finest selection of juniper berries found " +
        "in Mirkwood forest. This gin is so strong, you can only drink " +
        "one very small shot at a time.\n");
    set_soft_amount(110);
    set_alco_amount(55);

    add_prop(OBJ_I_WEIGHT, 20);
    add_prop(OBJ_I_VOLUME, 20);
    add_prop(OBJ_I_VALUE, F_VALUE_ALCO(55));
}