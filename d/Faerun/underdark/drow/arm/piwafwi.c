/*
 *  faerun/underdark/upper/menzo/melee/arm/piwafwi.c
 *
 *  A piwafwi cloak in Underdark
 *
 *  Created by Midnight, 15-4-2004
 */

#include <formulas.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Faerun/defs.h"
#include "defs.h"

inherit FAERUN_ARM_BASE;

#define AC 10

void create_faerun_armour()
{
    set_name("piwafwi");
    add_name("robe");
    set_adj( "stone-grey" );
    set_adj( "thin" );
    set_short("thin stone-grey piwafwi");
    set_long("This robe is made of the finest strongest silk of a drider. " +
        "Extremely thin strong metal threads are woven into the fine " +
        "spider-silk fabric, which makes the robe provide remarkable " +
        "protection considering how thin the robe is.\n");

    set_ac(AC + random(5));
    set_at(A_ROBE);

    add_prop(OBJ_I_WEIGHT, 500);
}

