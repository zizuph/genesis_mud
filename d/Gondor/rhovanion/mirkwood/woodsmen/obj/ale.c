#include <stdproperties.h>
#include <formulas.h>

inherit "/std/drink";

void
create_drink() 
{
    set_name(({"ale","cup","cup of ale"}));
    set_pname(({"ales","cups","cups of ale"}));
    set_short("cup of ale");
    set_pshort("cups of ale");
    set_long("The cup is filled with a light, pale ale. This looks like a " +
        "refreshing drink to enjoy after a hard days work. \n");
    set_soft_amount(90);
    set_alco_amount(7);

    add_prop(OBJ_I_WEIGHT, 20);
    add_prop(OBJ_I_VOLUME, 20);
    add_prop(OBJ_I_VALUE, F_VALUE_ALCO(7));
}