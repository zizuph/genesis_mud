/*
 *  faerun/underdark/upper/menzo/melee/wep/sword.c
 *
 *  This is a sword for warfare students
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
    set_name("sword");
    add_adj("blackened");
    add_adj("slender");
    set_long("This is a blackened sword, which " +
             "has a slender blade, which is as black as " +
             "a starless night heaven. The double-edged " +
             "blade is long and ends with a beautifully " +
             "carved guard of bright white polished bone.\n");
    set_short("blackened slender sword");

    set_wt(W_SWORD);
    set_hit(28);
    set_pen(28);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(28, 28));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(28, W_SWORD));
}