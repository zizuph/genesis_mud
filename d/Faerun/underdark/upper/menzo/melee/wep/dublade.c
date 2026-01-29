/*
 *  faerun/underdark/upper/menzo/melee/wep/dublade.c
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
    set_name("du'blade");
    add_adj("five-bladed");
    add_adj("vicious");
    set_long("This is a vicious-looking claw, which is " +
             "constructed as a dagger, with five sharp " +
             "double-edged blades. Every blade is as black " +
             "as a starless night heaven. Every blade is " +
             "securely attached to the hilt, which is short " +
             "and thick and made of bright white polished bone.\n");
    set_short("vicious five-bladed du'blade");

    set_wt(W_KNIFE);
    set_hit(35);
    set_pen(30);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(32, 25));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(25, W_KNIFE));
}