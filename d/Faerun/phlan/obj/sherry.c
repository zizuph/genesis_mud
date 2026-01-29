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
    set_name("sherry");
    set_adj("amontillado");
    set_short("Amontillado sherry");
    set_pshort("Amontillado sherries");
    set_long("A light brown hued fortified wine with notes of"
        +" nuttiness, sauteed mushrooms an an umami richness.\n");
    add_prop(OBJ_I_WEIGHT, 80);
    add_prop(OBJ_I_VOLUME, 80);
}
