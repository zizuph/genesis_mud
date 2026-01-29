/*
 * These leggings are worn by the orcs at the tower at Cirith Ungol.
 * (They come in three sizes: high, medium and low; these are medium)
 *
 * /Mercade, 3 august 1993
 */

inherit "/std/armour";

#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/d/Gondor/defs.h"

#define ARMOUR_CLASS 25

void
create_armour()
{
    set_name("greaves");
    add_name("leggings");

    set_adj("brass");
    set_adj("augmented");

    set_short("brass augmented greaves");
    set_pshort("brass augmented greaves");
    set_long(BSN("These greaves are made of brass strips, partially " +
        "overlapping eachother. Even though they give you good protection " +
        "on your legs, they don't hinder you too much when you walk."));

    set_ac(ARMOUR_CLASS);
    set_at(A_LEGS);
    set_am( ({ 1, -2, 1 }) );

    add_prop(OBJ_I_WEIGHT, 6300);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS) + random(151) - 75);
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
