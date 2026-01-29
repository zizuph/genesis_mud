/* File         : /d/Khalakhor/se_speir/rannoch/arm/boots.c
 * Creator      : Darragh@Genesis
 * Date         : 00-12-22 
 * Purpose      : Npc in the Loch Rannoch area.
 * Related Files: 
 * Comments     :
 * Modifications: 
 */

#pragma strict_types

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include "/d/Khalakhor/sys/defs.h"

#define AC 1

inherit "/std/armour";
inherit "/lib/keep";

public void
create_armour()
{
    set_name("boots");
    set_short("pair of low leather boots");
    set_pshort("pairs of low leather boots");
    set_adj("low");
    add_adj("leather");
    set_long("These boots were made from some animal " +
        "skin, well-made and yet comfortable.\n");

    set_ac(AC);
    set_at(A_FEET);
    set_keep(1);
    set_af(TO);

    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(AC));
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 2000);
}
