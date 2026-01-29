/*
 * Armour for goblin armour quest
 * - Boreaulam, April 2012
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

    set_name("armour");
    add_name("platemail");
    set_short("copper platemail");
    set_adj("copper");
    set_long("This suit of armour has been constructed from overlapping " +
             "plates of copper. It is perhaps not the ideal metal to craft " +
             "armour from, but it should provide some reasonable protection " +
             "to anyone who wears it.\n");
    set_ac(15 + random(10));
    set_at(A_TORSO);
    set_am(({0,0,0}));

    add_prop(OBJ_I_VALUE, 250);
    add_prop(OBJ_I_VOLUME, 1500);
    add_prop(OBJ_I_WEIGHT, 3000);
} /* create_armour */