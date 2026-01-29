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
#include "defs.h"

inherit P_MENZO_SORCERE + "std/base_armour";

/*
 * Function name: create_sorcere_armour
 * Description  : Construct a armour for the Sorcere part of Menzoberranzan
 */
void create_sorcere_armour()
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
             "layer of luxorius midnight-blue velvet. The exterior " +
             "of the robe is made of a dark grey semi-translucent " +
             "web-like material, which flows elegantly on top of the " +
             "shimmering velvet.\n");
    set_short("dark long layered robe");

    set_ac(20);
    set_at(A_ROBE);

    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(20));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(20, A_ROBE));

}

