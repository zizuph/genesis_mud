#pragma strict_types

inherit "/std/weapon.c";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

void
create_weapon()
{
    set_name("dagger");
    set_short("sharp dagger");
    set_long("This is a very sharp dagger, beyond that there is nothing special about it.\n");
    set_default_weapon(14, 14, W_KNIFE, W_SLASH | W_IMPALE, W_ANYH, 0);
    add_prop(OBJ_I_WEIGHT, 1400);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(25,25) + random(200) - 50);
}
