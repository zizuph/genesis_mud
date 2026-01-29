/*
 * Bronze breastplate for goblins level 2
 * - Boreaulam, September 2012
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
    set_short("bronze breastplate");
    set_adj("bronze");
    set_long("This is a worn breastplate made out of bronze. Covered in " +
        "dents, the armour looks like it will only give the most basic " +
        "protection these days, but the polished finish is certainly " +
        "quite attractive to look at.\n");
    set_ac(13 + random(5));
    set_at(A_TORSO);

    add_prop(OBJ_I_VOLUME, 5500);
    add_prop(OBJ_I_WEIGHT, 7000);
} /* create_armour */