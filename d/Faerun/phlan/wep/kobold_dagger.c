/*
 *   Plain Dagger
 *   by Finwe, July 2005
 *
 *   Edited by Tharizdun 2021 for kobolds
 */
#pragma save_binary
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>

inherit FAERUN_WEP_BASE;

int hit = 11 + random(5),
    pen = 6 + random(5);
void
create_faerun_weapon()
{

    set_name("dagger");
    set_adj("steel");
    add_adj("plain");
    set_short("plain steel dagger");
    set_long("This is a " + short() + ". The blade is made of average quality"
        +" steel, sharpened on both edges. It is a common but functional"
        +" weapon, ubiquitous among smaller humanoid tribes.\n");

    set_hit(hit);
    set_pen(pen);
    set_wt(W_KNIFE);
    set_dt(W_SLASH | W_IMPALE);
    
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(pen,W_KNIFE)+random(50)-25);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(hit, pen)+random(20)-10);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);

    set_hands(W_ANYH);
}
