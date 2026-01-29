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
#include "/d/Faerun/defs.h"

inherit FAERUN_WEP_BASE;

#define HIT 30
#define PEN 30

void
create_faerun_weapon()
{
    set_name("battleaxe");
    add_name("axe");
    add_adj("blackened");
    add_adj("steel");
    set_long("This is a long-handled battleaxe. It has a sharp steel blade which is as black as a starless night. The double-edged blade crowns the long handle which is made out of grey ironwood. The hardwood has the silvery finish of metal, and by the feeling of it, it could very well have been metal.\n");
    set_short("blackened steel battleaxe");

    set_wt(W_AXE);
    set_hit(HIT + random(5));
    set_pen(PEN + random(5));

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(HIT, W_AXE));
}