inherit "/std/armour";

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include "defs.h"

void
create_armour()
{
    set_name(({"pants", "pair"}));
    set_adj(({"diaphanous", "silky", "white"}));
    set_short("pair of diaphanous white harem pants");
    set_long("A pair of diaphanous silky white harem pants.\n");
    set_at(A_LEGS);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 5);
}
