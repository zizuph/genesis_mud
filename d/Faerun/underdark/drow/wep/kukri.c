/*
 *  faerun/underdark/upper/menzo/sorcere/wep/kukri.c
 *
 *  This is dagger for wizard students
 *
 *  Created by Midnight, 21-2-2004
 */

#include <formulas.h>
#include <stdproperties.h>
#include "defs.h"
#include "/d/Faerun/defs.h"

inherit FAERUN_WEP_BASE;

#define HIT 32
#define PEN 25

void 
create_faerun_weapon()
{
    set_name("kukri");
    add_name("dagger");
    add_name("knife");
    add_adj("ebony-bladed");
    add_adj("curved");
    set_short("curved ebony-bladed kukri");
    set_long("This is a " + query_short() + ". It has a curved blade which " +
        "is as black as a starless night heaven. The sharp edge runs " +
        "along the inside of the curved blade. The hilt is short and " +
        "thick and made of bright white polished bone.\n");

    set_wt(W_KNIFE);
    set_hit(HIT);
    set_pen(PEN);

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN, W_KNIFE));
}
