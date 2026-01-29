
/*
 * heavy_cloth_shirt.c
 * cloth shirt, worn by sailors
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
    set_name("shirt");
    set_adj("heavy");
    add_adj("cloth");

    set_short("heavy cloth shirt");

    set_long("This moderately-heavy shirt is of the loose-fitting type "+
        "typically prefered by sailors.\n");

    set_at(A_BODY);
    set_ac(2);

    add_prop(OBJ_I_VOLUME, 400);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(2,A_BODY));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(2));

}

