/*
 * Bronze greaves for goblins level 2
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

    set_name("greaves");
    set_short("bronze greaves");
    set_adj("bronze");
    set_long("These greaves are made out of bronze. Dented and mishappen, " +
        "these leg guards look like they will only give the most basic " +
        "protection these days. However, the polished finish is certainly " +
        "quite attractive to look at.\n");
    set_ac(14 + random(5));
    set_at(A_LEGS);

    add_prop(OBJ_I_VOLUME, 2500);
    add_prop(OBJ_I_WEIGHT, 4000);
} /* create_armour */