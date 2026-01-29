/*
 * Bronze helmet for goblins level 2
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

    set_name("helmet");
    add_name("helm");
    set_short("bronze helmet");
    set_adj("bronze");
    set_long("This helmet is made entirely out of bronze. Dented enough " +
        "that it does not rest easily on top of your head, you suspect that " +
        "the helm will provide only the most basic protection. However, the " +
        "polished finish is certainly quite attractive to look at.\n");
    set_ac(9 + random(5));
    set_at(A_HEAD);

    add_prop(OBJ_I_VOLUME, 2500);
    add_prop(OBJ_I_WEIGHT, 4000);
} /* create_armour */