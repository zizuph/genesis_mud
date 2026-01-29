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
#include "/d/Faerun/defs.h"

inherit FAERUN_WEP_BASE;

#define HIT 30
#define PEN 30

void
create_faerun_weapon()
{
    set_name("scimitar");
    add_name("sword");
    add_adj("jagged");
    add_adj("polished");
    set_long("This is a polished scimitar. It has a slender curved blade which is as black as a starless night. The sharp edge runs along the inside of the curved blade. The hilt is short, thick and made of bright white polished bone.\n");
    set_short("polished jagged scimitar");

    set_wt(W_SWORD);
    
    set_hit(HIT + random(5));
    set_pen(PEN + random(5));
}
