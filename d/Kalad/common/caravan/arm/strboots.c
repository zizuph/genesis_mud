#include "../default.h"
inherit (STD + "armour");

#include <wa_types.h>

void
create_armour()
{
    ::create_armour();

    set_name("boots");
    set_adj("black");
    set_long("An extremely dark pair of fur-lined boots.\n");
    set_ac(8);
    set_at(A_FEET);
    add_prop(OBJ_I_VALUE, 240);
    add_prop(OBJ_I_VOLUME, 750);
    add_prop(OBJ_I_WEIGHT, 750);
}
