/*
 *  faerun/underdark/upper/menzo/sorcere/arm/masterrobe1.c
 *
 *  A masters robe in Underdark
 *
 *  Created by Midnight, 25-2-2004
 */

#include <formulas.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Faerun/defs.h"
#include "defs.h"

#define AC 20

inherit FAERUN_ARM_BASE;

void create_faerun_armour()
{
    set_name("robe");
    set_adj( "long" );
    set_adj( "layered" );
    set_adj( "dark" );
    set_long("This robe is made of several layers " +
             "of the finest of materials. The first " +
             "layer, closest to the body, is made of cool and soft " +
             "spidersilk, which shimmer with the glimmer of diamond " +
             "dust. On top of that layer there's a rich and thick " +
             "layer of luxurious midnight-blue velvet. The exterior " +
             "of the robe is made of a dark grey semi-translucent " +
             "web-like material, which flows elegantly on top of the " +
             "shimmering velvet.\n");
    set_short("dark long layered robe");

    set_ac(AC + random(5));
    set_at(A_ROBE);
    add_prop(OBJ_I_WEIGHT, 5000);

}

