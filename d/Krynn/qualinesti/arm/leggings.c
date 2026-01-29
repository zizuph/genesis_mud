/*  
 * File: leggings.c
 * Kragh's leggings.
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
    set_name("leggings");
    set_short("pair of scalemail dwarven leggings");
    set_pshort("pairs of scalemail dwarven leggings");
    add_adj(({ "scalemail", "heavy", "dwarven" }));
    set_ac(31);
    set_am( ({2,0,-2}) );
    set_at(A_LEGS | A_ANKLES);
    set_long("This is a pair of leather pants with iron discs sewn onto " +
        "them as protection. They are a little heavy, but give better " +
        "protection than chainmail does.\n");
    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(31) + random(600));
}

