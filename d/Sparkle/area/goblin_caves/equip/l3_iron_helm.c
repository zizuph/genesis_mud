/*
 * Iron helm for goblins level 3
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

    set_name("helmet");
    add_name("helm");
    set_short("iron helmet");
    set_adj("iron");
    set_long("This helmet is made entirely out of iron.\n");
    set_ac(20 + random(5));
    set_at(A_HEAD);

    add_prop(OBJ_I_VOLUME, 2500);
    add_prop(OBJ_I_WEIGHT, 4000);
} /* create_armour */