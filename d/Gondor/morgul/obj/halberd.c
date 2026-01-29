/* 
 *      /d/Gondor/morgul/obj/halberd.c
 *
 *      A halberd for use of Ithil uruks
 *
 *      Olorin, July 1993
 *
 *      Last Modification: Olorin, July 1994
 */
#pragma strict_types

inherit "/std/weapon.c";
inherit "/lib/keep.c";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

void
create_weapon() 
{
    set_name(({"halberd","polearm","weapon"}));
    set_short("large steel halberd");

    set_long(BSN("This is a large steel halberd with a pole made out " +
    "of hard black wood. The halberd has two blades, the larger one " +
    "formed like the blade of an axe, the smaller one ending in a sharp " +
    "point. The top of the wooden pole ends in a sharp pointed spear " +
    "head, so the polearm can be used as a lance, too. Etched into the " +
    "larger of the blades is the picture of a Moon disfigured with " +
    "a ghastly face of death."));
    set_adj(({"orc", "large", "heavy", "steel"}));
    set_default_weapon(28, 40,W_POLEARM,W_IMPALE|W_SLASH,W_BOTH,0);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(28, 40)+random(400)-200);
    add_prop(OBJ_I_WEIGHT,
	(F_WEIGHT_DEFAULT_WEAPON(28, W_POLEARM) + random(500) + 1000));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
    add_prop(GONDOR_M_MORGUL_NO_SELL, 1);
}
