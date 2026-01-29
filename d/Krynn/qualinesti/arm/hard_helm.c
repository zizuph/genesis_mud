/*  
 * File: hard_helm.c
 * Kragh's helm.
 *
 * Blizzard, 05/2003
 */
 
inherit "std/armour.c";
inherit "/lib/keep";

#include <wa_types.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Krynn/common/defs.h"

void
create_armour()
{
    set_name("helm");
    add_name(({"helmet", "armour" }));
    set_short("hard leather helm");
    add_adj(({ "leather", "hard" }));
    set_ac(18);
    set_am( ({1,0,-1}) );
    set_at(A_HEAD);
    set_long("This is rigid leather helm studded with iron rivets. It is " +
        "much heavier than a regular leather helm, but the iron studs " +
        "deflect blows.\n");
    add_prop(OBJ_I_WEIGHT, 1500);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(18) + random(300));
}
