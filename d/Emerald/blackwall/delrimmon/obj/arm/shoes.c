/*
 *  /d/Emerald/blackwall/delrimmon/obj/arm/wh_shoes.c
 *
 *  Copyright (c) January 1998, by Cooper Sherry (Gorboth)
 *
 *  These are the hard-soled footgear of the Army of Darkness as supplied
 *  by the Darklings. They are uncomfortable, yet durable.
 */
#pragma strict_types

inherit "/std/armour.c";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Emerald/blackwall/delrimmon/defs.h"

public void
create_armour()
{
    set_name("shoe");
    add_name("armour");
    set_adj("iron-shod");

    set_short("pair of iron-shod shoes");
    set_long(BSN("These crudely crafted footwear look heavy and"
      + " uncomfortable, yet sturdy and well suited to rough terrain"
      + " and conditions. The iron material of their make bears"
      + " no discernable mark or emblem."));

    set_default_armour(12, A_FEET, (({ 0, 0, 0 })), 0);
    add_prop(OBJ_I_WEIGHT, 380);
    add_prop(OBJ_I_VOLUME, 180);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(12) + random(10));
}
