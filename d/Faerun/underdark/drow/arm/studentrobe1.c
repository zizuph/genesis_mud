/*
 *  faerun/underdark/upper/menzo/sorcere/arm/studentrobe1.c
 *
 *  A nightscale armour in Underdark
 *
 *  Created by Midnight, 21-2-2004
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
    set_name("robe");
    set_adj( "silver-lined" );
    set_adj( "spidersilk" );
    set_long("This robe is made of the finest strongest " +
             "silk of a drider. Thin strong silver threads " +
             "are woved into the fine spidersilk fabric,  " +
             "which makes the robe shimmer with the " +
             "glimmer of diamond dust.\n");
    set_short("silver-lined spidersilk robe");

    set_ac(AC + random(5));
    set_at(A_ROBE);

    add_prop(OBJ_I_WEIGHT, 5000);
}

