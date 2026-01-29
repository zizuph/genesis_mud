/*
 *  faerun/underdark/upper/menzo/sorcere/wep/qstaff.c
 *
 *  This is quarterstaff for wizard students
 *
 *  Created by Midnight, 21-2-2004
 */

#include <formulas.h>
#include <stdproperties.h>
#include "defs.h"

inherit P_MENZO_SORCERE + "std/base_weapon";

/*
 * Function name: create_sorcere_weapon
 * Description  : Construct a weapon for the Sorcere part of Menzoberranzan
 */
void create_sorcere_weapon()
{
    set_name("quarterstaff");
    add_adj("sleek");
    add_adj("blackened");
    set_long("This is a sleek quarterstaff , made of " +
             "duskwood. It feels as hard as iron and the " +
             "staff is slightly twirled along it's length " +
             "to secure a solid grip for the wielder. " +
             "The slender wooden staff seems to have been " +
             "blackened by fire, but amazingly not destroyed.\n");
    set_short("sleek blackened quarterstaff");

    set_wt(W_POLEARM);
    set_hit(37);
    set_pen(40);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(37, 40));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(40, W_POLEARM));
}
