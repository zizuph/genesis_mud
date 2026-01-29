/*
 * cloak.c
 * Heavy wool cloak to keep thanduin warm in the cool, damp breeze
 * of the mist-shrouded forest.
 * 
 * - Alaron Feb 1998
 */

#include "../dirheader.h"
#include "../coramar.h"
#include <wa_types.h>
#include <formulas.h>
#include "/d/Emerald/defs.h"

inherit "/std/armour";

void
create_armour()
{
    set_name("cloak");
    set_adj("heavy"); add_adj("wool");

    set_long("This long, gray wool cloak is very thick. It is made of "+
              "an extremely soft, heavy fur. The fur looks like it is "+
              "probably water-resistant, making this heavy cloak a very "+
              "useful item of clothing in cold, damp climates.\n");


    set_at(A_ROBE);
    set_ac(10);

    add_prop(OBJ_I_WEIGHT, 800);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(10));
}
