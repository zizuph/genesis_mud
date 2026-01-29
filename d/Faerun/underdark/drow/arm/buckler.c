/*
 *  faerun/underdark/upper/menzo/melee/arm/buckler.c
 *
 *  Created by Midnight, 15-4-2004
 */

#include <formulas.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Faerun/defs.h"
#include "defs.h"

inherit FAERUN_ARM_BASE;

#define AC 15

void create_faerun_armour()
{

    set_name("buckler");
    add_name("shield");
    set_adj( "black" );
    set_adj( "adamantine" );
    set_short("black adamantine buckler");
    set_long("A common buckler made of solid adamantine by Drow. The dark " +
        "metal has been molded to a perfect circular shape. A large " +
        "crimson spider covers the front of the buckler in a decorative " +
        "manner.\n");

    set_ac(AC + random(5));
    set_at(A_SHIELD);

    add_prop(OBJ_I_WEIGHT, 900);
}