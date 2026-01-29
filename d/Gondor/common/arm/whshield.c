/* 
 *      /d/Gondor/common/arm/whshield.c
 *
 *      Shield of the Isengard Uruk-hai
 */
#pragma strict_types

inherit "/std/armour";

#include <formulas.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

public void
create_armour()
{
    set_name("shield");
    add_name("Isengard_Shield");
    set_pname("shields");
    set_short("iron shield");
    set_pshort("iron shields");
    set_adj("normal");
    set_adj("iron");
    set_long(BSN("This is a normal iron shield. On the front is a " +
        "crest; a small white hand in the centre of a black field."));
    set_default_armour(8, A_SHIELD,({ -2, 1, 0}), 0);
    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 880);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(8) + random(10) - 20);
}
