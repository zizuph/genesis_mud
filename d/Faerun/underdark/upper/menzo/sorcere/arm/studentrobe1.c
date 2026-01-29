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
#include "defs.h"

inherit P_MENZO_SORCERE + "std/base_armour";

/*
 * Function name: create_sorcere_armour
 * Description  : Construct a armour for the Sorcere part of Menzoberranzan
 */
void create_sorcere_armour()
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

    set_ac(15);
    set_at(A_ROBE);

    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(15));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(15, A_ROBE));

}

