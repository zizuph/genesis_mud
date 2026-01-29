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
#include "/d/Faerun/defs.h"

inherit FAERUN_WEP_BASE;

#define HIT 37
#define PEN 40

void 
create_faerun_weapon()
{
    set_name("quarterstaff");
    add_name("staff");
    add_name("polearm");
    add_adj("sleek");
    add_adj("blackened");
    set_long("This is a sleek quarterstaff and made of " +
             "duskwood. It feels as hard as iron and the " +
             "staff is slightly twirled along its length " +
             "to secure a solid grip for the wielder. " +
             "The slender wooden staff seems to have been " +
             "blackened by fire, but amazingly not destroyed.\n");
    set_short("sleek blackened quarterstaff");

    set_wt(W_POLEARM);
    set_hit(HIT);
    set_pen(PEN);

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN, W_POLEARM));
}
