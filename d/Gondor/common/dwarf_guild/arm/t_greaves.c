/*
 * /d/Gondor/common/dwarf_guild/arm/t_greaves.c
 *
 * These greaves are worn by the trainer in the dwarven race guild.
 *
 * /Mercade, 3 august 1993
 *
 * Revision history:
 */

#pragma save_binary

inherit "/std/armour";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "/d/Gondor/defs.h"
#include "../dwarf.h"

#define ARMOUR_CLASS 30

void
create_armour()
{
    set_name("greaves");
    add_name("leggings");

    set_adj("black");
    set_adj("steel");
    set_adj("plated");

    set_short("black steel plated greaves");
    set_pshort("black steel plated greaves");
    set_long(BSN("These greaves are made of black steel plates, linked to " +
        "eachother to protect your legs and at the same time give you " +
        "enough room to walk or run. The plates are forged in a special " +
        "way to make it black and very strong."));

    set_ac(ARMOUR_CLASS);
    set_at(A_LEGS);
    set_am( ({ 0, 0, 0 }) );

    add_prop(OBJ_I_WEIGHT, 7200);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS) + random(201) - 100);
}

string
query_recover()
{
    return MASTER + ":" + query_arm_recover();
}

void
init_recover(string arg)
{
    init_arm_recover(arg);
}