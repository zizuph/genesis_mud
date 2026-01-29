/*
 * Dagger from Mere of Dead Men
 * by Finwe, July 2005
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

int hit = 15,
    pen = 10;
void
create_faerun_weapon()
{

    set_name("dagger");
    set_adj("polished");
    set_adj("steel");
    set_short("polished dagger");
    set_long("This is a " + short() + ". It fits nicely in your hand and " +
        "is perfectly balanced. The blade has some ridges on the edge " +
        "which seem to make the blade deadlier when used.\n");

    set_hit(hit);
    set_pen(pen);
    set_wt(W_KNIFE);
    set_dt(W_SLASH | W_IMPALE);

    add_prop(OBJ_I_WEIGHT,1500);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(hit,pen) + random(50) - 20);

    set_hands(W_ANYH);
}
