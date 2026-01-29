#include <stdproperties.h>
#include <formulas.h>

inherit "/std/drink";

void
create_drink() 
{
    set_name(({ "special", "house special" }));
    set_pname(({ "specials", "house specials" }));
    set_short("house special");
    set_pshort("house specials");
    set_adj("house");
    set_long("As you examine the bottle carefully, about " 
        + "all you can tell is that it has the fruity aroma of a " 
        + "very strong, alcoholic bevereg.\n");
    set_soft_amount(150);
    set_alco_amount(35);

    add_prop(OBJ_I_WEIGHT, 300);
    add_prop(OBJ_I_VOLUME, 300);
    add_prop(OBJ_I_VALUE, F_VALUE_ALCO(35));
}