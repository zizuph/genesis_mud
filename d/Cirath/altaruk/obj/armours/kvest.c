inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>

create_armour()
{
    set_name("vest");
    set_adj("strapped");
    add_adj("leather");
    set_short("strapped leather vest");
    set_long("This is a leather vest with straps to ensure a tight fit. " +
        " Erdlu scales is fitted across the back for better protection.\n");
    set_ac(25);
    set_at(A_BODY);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(25, A_BODY));
    add_prop(OBJ_I_VOLUME, F_WEIGHT_DEFAULT_ARMOUR(25, A_BODY) / 5);
}


