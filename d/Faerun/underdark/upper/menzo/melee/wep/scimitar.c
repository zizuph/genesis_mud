/*
 *  faerun/underdark/upper/menzo/melee/wep/scimitar.c
 *
 *  This is scimitar for warfare students
 *
 *  Created by Midnight, 15-4-2004
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
    set_name("scimitar");
    add_adj("jagged");
    add_adj("polished");
    set_long("This is a polished scimitar, which " +
             "has a slender curved blade, which is as black as " +
             "a starless night heaven. The sharp edge " +
             "runs along the inside of the curved blade. " +
             "The hilt is short and thick and made of " +
             "bright white polished bone.\n");
    set_short("polished jagged scimitar");

    set_wt(W_SWORD);
    set_hit(28);
    set_pen(28);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(28, 28));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(28, W_SWORD));
}