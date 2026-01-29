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
#include "/d/Faerun/defs.h"

inherit FAERUN_WEP_BASE;

#define HIT 30
#define PEN 30

void 
create_faerun_weapon()
{
    set_name("du'blade");
    add_name("claw");
    add_name("knife");
    add_name("dagger");
    add_adj("five-bladed");
    add_adj("vicious");
    set_long("This is a vicious-looking claw, which is " +
             "constructed as a dagger and has five sharp " +
             "double-edged blades. Every blade is as black " +
             "as a starless night. They are " +
             "securely attached to the hilt, which is short " +
             "and thick and made of bright white polished bone.\n");
    set_short("vicious five-bladed du'blade");

    set_wt(W_KNIFE);
    set_hit(HIT + random(5));
    set_pen(PEN + random(5));

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(HIT, W_KNIFE));
}