
/*
 * Ceremonial Alb
 * No value
 * Only used for ceremonies
 *
 */
 
inherit "/std/armour";

#include <formulas.h>
#include <stdproperties.h>
 
void
create_armour()
{
    set_name(({"gray mantle","mantle"}));
    add_name("_ceremonial_mantle");
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
