/*
 *  /d/Emerald/blackwall/delrimmon/obj/arm/shield.c
 *
 *  This is one of the standard shields issued by the Army of Darkness
 *  to the captains of the orc troops.
 *
 *  Copyright (c) October 2001, by Cooper Sherry (Gorboth)
 */
#pragma strict_types;
inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#include "/d/Emerald/blackwall/delrimmon/defs.h"

void
create_armour()
{
    set_name("shield");
    set_short("round iron shield");
    set_pshort("iron shields");
    set_adj(({"heavy", "blackened", "iron", "round"}));
    set_long(BSN("The iron of this shield is thick, and has been stained"
        + " a dark black by some foul process. Though the thickness adds"
        + " to the protection the shield affords, it also adds considerably"
        + " to the weight, making it very heavy. A grey skull is painted"
        + " on the shield's front."));
    set_default_armour(30,A_SHIELD,({0,0,0}),0);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(30)+random(700)-250);
    add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(30,A_SHIELD)+random(1200)-200);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 7);
}
