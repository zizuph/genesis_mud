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
#include "defs.h"

inherit P_MENZO_MELEE + "std/base_armour";

/*
 * Function name: create_melee_armour
 * Description  : Construct a armour for the Melee-magthere
 */
void create_melee_armour()
{
    set_name("piwafwi");
    set_adj( "stone-grey" );
    set_adj( "thin" );
    set_short("thin stone-grey piwafwi");
    set_long("This robe is made of the finest strongest " +
             "silk of a drider. Extremely thin strong metal " +
             "threads are woven into the fine spidersilk fabric, " +
             "which makes the robe provide remarkable protection " +
             "considering how thin the robe is.\n");
    

    set_ac(10);
    set_at(A_ROBE);

    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(10));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(10, A_ROBE));

}

