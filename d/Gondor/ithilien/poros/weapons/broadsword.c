/*
 *   /d/Gondor/ithilien/poros/weapons/broadsword.c
 *
 *   This is the weapon used by the Dunadan traveler atop the hill, along 
 *   the path near the poros river.
 *
 *   Talisan,  February 1996
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
    set_name(({"broadsword", "broad sword", "sword"}));
    set_short("steel-bladed broadsword");
    set_pshort("steel-bladed broadswords");
    set_long("This finely crafted broadsword is of Gondorian make. Its "
      + "thick steel blade is sharp and deadly. The sword's hilt is "
      + "wrapped with leather to afford a better grip.\n");
    set_adj(({"steel-bladed", "steel", "gondorian", "deadly", "sharp"}));

    set_default_weapon(27,30, W_SWORD,W_SLASH|W_IMPALE,W_ANYH, 0);

    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(27,30) + random(500)-250);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
}
