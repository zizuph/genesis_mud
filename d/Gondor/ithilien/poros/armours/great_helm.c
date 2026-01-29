/*
 *   /d/Gondor/ithilien/poros/armours/great_helm.c
 *
 *   This is the helm worn by the corsair captain while at the base.
 *
 *   Talisan,  February 1996
 * Modification log:
 * Gwyneth - Added more verbose set_pshort 4/1/01
 */

#pragma strict_types

inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_armour()
{
    set_name(({"helm", "helmet"}));
    set_short("black great helm");
    set_pshort("black great helms");
    set_long("This pure black great helm has been expertly crafted in Umbar, "
      + "from the finest of steels found in all of Harad. The high steel helm "
      + "offers full protection for the head, neck, and face.\n");
    add_adj(({"black", "great", "umbarim", "steel", "high-steel",
        "high steel"}));

    set_default_armour(30,A_HEAD|A_NECK, ({-2,4,-2}), 0);

    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(30)+random(250)-150);
    add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(30,A_HEAD));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
}
