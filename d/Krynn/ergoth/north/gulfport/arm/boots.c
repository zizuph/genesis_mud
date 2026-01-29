
/*
 * boots.c
 * A pair of sturdy brown boots
 * Gulfport, Northern Ergoth
 * Tibbit, 1 May 1998
 *
 */

inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>

void
create_armour()
{
    set_name("boots");
    add_adj("sturdy");
    add_adj("brown");
    set_short("pair of sturdy brown boots");
    set_pshort("pairs of sturdy brown boots");

    set_long("A pair of sturdy brown boots, crafted from "+
        "stiffened leather.  It seems that they would be "+
        "quite comfortable for both work and play.\n");

    set_at(A_FEET);
    add_prop(OBJ_I_WEIGHT, 400);
    add_prop(OBJ_I_VOLUME, 400);
    add_prop(OBJ_I_VALUE, 200);

}

