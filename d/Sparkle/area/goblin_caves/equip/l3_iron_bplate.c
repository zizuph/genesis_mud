/*
 * Iron breastplate for goblins level 3
 * - Boreaulam, Jan 2018
 */
inherit "/std/armour";

#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>

/*
 * Function name:        create_armour
 * Description  :        constructor for the object
 */
void
create_armour()
{

    set_name("breastplate");
    set_short("iron breastplate");
    set_adj("iron");
    set_long("This is a breastplate made out of iron.\n");
    set_ac(25 + random(5));
    set_at(A_TORSO);

    add_prop(OBJ_I_VOLUME, 5500);
    add_prop(OBJ_I_WEIGHT, 7000);
} /* create_armour */