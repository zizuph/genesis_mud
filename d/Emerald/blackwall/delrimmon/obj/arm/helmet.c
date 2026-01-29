/*
 *  /d/Emerald/blackwall/delrimmon/obj/arm/helmet.c
 *
 *  This is a standard issue helmet for the troops within the Army
 *  of Darkness.
 *
 *  Copyright (c) October 2001, by Cooper Sherry (gorboth)
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
    set_name("helmet");
    set_short("dark black helmet");
    set_pshort("dark black helmets");
    set_adj( ({ "stained", "blackened", "iron", "dark", "black" }) );
    set_long(BSN("While somewhat crude and offensive to look upon, this"
        + " helmet is obviously a well crafted piece of armour. The iron"
        + " of its composition has been stained a dark black by some"
        + " foul process, and an emblem of a grey skull in a black"
        + " circle is fixed above the noseplate."));
    set_default_armour(25,A_HEAD,({0,0,0}),0);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(25)+random(250)-50);
    add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(25,A_HEAD)+random(250));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 6);
}
