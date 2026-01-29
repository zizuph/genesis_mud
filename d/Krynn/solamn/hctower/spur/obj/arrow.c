/*
 * Filename:      arrow.c
 * Description:   An arrow for the archers bow, originally coded by
 *                Grace aka. Lilith, converted into using the new
 *                arrow an bow module by Boron.
 *
 */
inherit "/std/arrow";
#include "../local.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>

public void
create_weapon()
{
    set_adj("steel-tipped");

    set_hit(35);
    set_pen(32);

    AI("arrowhead", "It is made of steel.\n");
    AI("shaft", "It is made of wood.\n");
    AI("feathers", "The fletcher put short rows of feathers along the end "+
        "of the shaft opposite the arrowhead.\n");

    set_projectile_id("solamnian_steel_tipped_arrow");

    add_prop(OBJ_I_VOLUME, 180);
    add_prop(OBJ_I_WEIGHT, 250);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(35, 32));
}

string
get_projectile_long(string str, object for_obj, int num)
{

    return "The fletcher that made " + ((num == 1) ? "this arrow" :
           "these arrows") + " knew what he was doing.\n" +
           "The steel " + ((num == 1) ? "arrowhead" : "arrowheads") +
           "is balanced by the length of the shaft and the feathers " +
           "at the opposite end.\n";
}