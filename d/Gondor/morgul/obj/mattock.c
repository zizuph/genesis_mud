/*  
 *      /d/Gondor/morgul/obj/mattock.c
 *      A mattock for use of Ithil uruks
 *      Olorin, July 1993
 *      Last Modification: Olorin, July 1994
 */
#pragma strict_types

inherit "/std/weapon";
inherit "/lib/keep";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

void
create_weapon() 
{
    set_name(({"mattock","axe","weapon"}));
    set_short("heavy steel mattock");

    set_long(BSN("This is a heavy steel axe, a mattock, with a handle " +
        "made out of hard black wood. The mattock has two blades, one " +
        "horizontal, and a large vertical one. Etched into the " +
        "larger of the blades is the picture of a Moon disfigured with " +
        "a ghastly face of death."));
    set_adj(({"large", "heavy", "steel"}));
    set_default_weapon(28,38,W_AXE,W_SLASH|W_BLUDGEON,W_BOTH,0);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(28,38)+random(600)-150);
    add_prop(OBJ_I_WEIGHT,
	(F_WEIGHT_DEFAULT_WEAPON(28,W_AXE) + random(1000) + 500));
}

