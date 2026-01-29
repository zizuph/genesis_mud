/*
 *   /d/Gondor/ithilien/poros/obj/whip.c
 *
 *   This is one of the weapons the corsair's Haradan jailer uses.
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
#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_weapon()
{
    set_name(({"whip"}));
    set_short("old worn whip");
    set_pshort("old worn whips");
    set_long("This brown leather whip seems well used. You can see traces "
      + "of fresh blood have soaked into its frayed tip.\n");
    set_adj(({"old", "worn", "old worn", "brown", "leather", "well used"}));

    set_default_weapon(18,13, W_CLUB,W_SLASH,W_ANYH, 0);

    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(18,13) + random(200)-200);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 10);
}
