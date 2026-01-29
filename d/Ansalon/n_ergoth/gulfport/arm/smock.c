
/*
 * smock.c
 * A smock, worn by Gullydwarves
 * City of Gulfport, Northern Ergoth
 * Created by Tibbit, 22 May 1998
 *
 */

inherit "/std/armour";

#include "../local.h"
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("smock");
    set_adj("dirty");
    add_adj("simple");

    set_short("simple dirty smock");

    set_long("A simple, small-sized smock. It is particularly dirty."+
        "\n");

    set_at(A_ROBE);
    set_ac(2);

    add_prop(OBJ_I_VOLUME, 400);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(2,A_ROBE));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(2));

}

