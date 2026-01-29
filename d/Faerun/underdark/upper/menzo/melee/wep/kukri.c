/*
 *  faerun/underdark/upper/menzo/melee/wep/kukri.c
 *
 *  This is dagger for warfare students
 *
 *  Created by Midnight, 21-2-2004
 */

#include <formulas.h>
#include <stdproperties.h>
#include "defs.h"

inherit P_MENZO_MELEE + "std/base_weapon";

/*
 * Function name: create_melee_weapon
 * Description  : Construct a weapon for the Melee-magthere
 */
void create_melee_weapon()
{
    set_name("kukri");
    add_adj("ebony-bladed");
    add_adj("curved");
    set_long("This is a heavy large dagger, which " +
             "has a curved blade, which is as black as " +
             "a starless night heaven. The sharp edge " +
             "runs along the inside of the curved blade. " +
             "The hilt is short and thick and made of " +
             "bright white polished bone.\n");
    set_short("curved ebony-bladed kukri");

    set_wt(W_KNIFE);
    set_hit(32);
    set_pen(25);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(32, 25));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(25, W_KNIFE));
}