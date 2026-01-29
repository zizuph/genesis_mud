
/*
 * Ceremonial Alb
 * No value, can't be taken outside of the temple
 * Only used for ceremonies in the temple
 *
 */
 
inherit "/std/armour";

#include <formulas.h>
#include <stdproperties.h>

#include "defs.h"
#include SPIRIT_HEADER
 
void
create_armour()
{
    set_name(({"gray mantle","mantle"}));
    add_name(CEREMONIAL_GARB);
    set_adj("grey");
    set_short("grey mantle");
    set_long("It is a long sleevless garment worn over a robe.\n");
    set_ac(1);
    set_at(A_BODY);
    set_am(({-1, 0, 1}));
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_M_NO_SELL,1);
}
