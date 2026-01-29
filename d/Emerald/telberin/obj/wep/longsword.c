/*
 *  /d/Emerald/telberin/obj/wep/longsword
 *
 *  This is one of the standard issue weapons crafted for the 
 *  Protectorate of Telberin.
 *
 *  Copyright (c) July 2003, by Cooper Sherry (Gorboth)
 */

#pragma strict_types
inherit "/std/weapon.c";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Emerald/blackwall/delrimmon/defs.h"

public void
create_weapon()
{
    set_name("longsword");
    add_name( ({ "sword" }) );
    add_adj( ({ "gleaming", "metal" }) );
    set_short("gleaming metal longsword");
    set_long("This weapon is long and sharp, with a gleam along its"
      + " blade indicating that it has been excellently cared for."
      + " A fine coat of oil has been recently applied to its edge,"
      + " and its hilt is well polished.\n");
    set_default_weapon(30,30, W_SWORD, W_SLASH | W_IMPALE, W_BOTH, 0);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(30, W_SWORD)
      +random(100));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(30, 30) + random(45));
}
