/*
 *   /d/Gondor/ithilien/poros/obj/cutlass.c
 *
 *   This is the standard weapon used by the corsair raiders who are 
 *   encamped at their hidden base along the Poros river.
 *
 *   Talisan,  January 1996
 * Modification log:
 * Gwyneth - Added more verbose set_pshort 4/1/01
 */

#pragma strict_types

inherit "/std/weapon";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
# include <macros.h>

#include "/d/Gondor/defs.h"

void
create_weapon()
{
    set_name(({"cutlass", "cutlas", "sword"}));
    set_short("steel cutlass");
    set_pshort("steel cutlasses");
    set_long("This is a short, heavy, slightly curved steel sword. A favorite "
      + "of the Corsairs, it is designed for sheer butchery instead "
      + "of finesse.\n");
    set_adj(({"short", "heavy", "curved", "steel", "corsair"}));

    set_default_weapon(22,28,W_SWORD,W_SLASH,W_ANYH, 0);

    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(22,28) + random(100) - 100);
    add_prop(OBJ_I_WEIGHT,
	(F_WEIGHT_DEFAULT_WEAPON(22, W_SWORD) + 1000));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 8);
}
