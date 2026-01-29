/* body_brl: Simple shirt for the poor who still need armour. */
inherit "/d/Kalad/std/armour";
#include <wa_types.h>
#include "defs.h"

void create_armour()
{
    ::create_armour();
    set_name("shirt");
    set_short("burlap shirt");
    set_long("Good for holding potatoes, some poor souls feel the itchy "+
             "material provides some small measure of defence.\n");
    set_adj("burlap");

    set_ac(10);
    set_am(({ -1, -1, 2}));
    set_at(A_BODY);

    add_prop(OBJ_I_WEIGHT, 1125);
    add_prop(OBJ_I_VOLUME, 575);
}
