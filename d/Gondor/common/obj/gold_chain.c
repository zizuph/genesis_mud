/*  Armour coded by Arren, July 94 */

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Gondor/defs.h"

void
create_armour()
{
    set_name("chain");
    add_name(({"belt"}));
    set_adj("gold");
    add_adj(({"precious"}));
    set_short("gold chain");
    set_long(BSN("A long gold chain to be worn around the waist, it's "+
    "thin with fine links. "));

    set_default_armour(5, A_WAIST, ({0,0,0}), 0);

    add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(5, A_BODY));
    add_prop(OBJ_I_VOLUME, 333);
    add_prop(OBJ_I_VALUE, 500 + random(100));
}
