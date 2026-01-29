/*
 *  faerun/underdark/upper/menzo/melee/wep/axe.c
 *
 *  This is an axe for warfare students
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
    set_name("battleaxe");
    add_adj("blackened");
    add_adj("steel");
    set_long("This is a long-handled battleaxe, which " +
             "has a sharp steel blade, which is as black as " +
             "a starless night heaven. The double-edged " +
             "blade crowns the long handle which is made " +
             "out of grey ironwood. The hard wood has the " +
             "silvery finish og metal and by the feeling " +
             "of it, it could very well have been metal.\n");
    set_short("blackened steel battleaxe");

    set_wt(W_AXE);
    set_hit(28);
    set_pen(28);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(28, 28));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(28, W_AXE));
}