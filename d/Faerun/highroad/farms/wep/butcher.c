/*
 * Butcher Knife
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

int hit = 17,
    pen =  5;
void
create_faerun_weapon()
{

    set_name("knife");
    set_adj("large");
    set_adj("butcher");
    set_short("large butcher knife");
    set_long("This is a " + short() + ". It has a wide, triangular blade " +
        "with a wooden handle.The blade is sharp and used to cut or " +
        "trim meat. It is heavy-duty and dangerous looking.\n");

    set_hit(hit);
    set_pen(pen);
    set_wt(W_KNIFE);
    set_dt(W_SLASH | W_IMPALE);

    add_prop(OBJ_I_WEIGHT,1500);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(hit,pen) + random(50) - 20);

    set_hands(W_ANYH);
}
