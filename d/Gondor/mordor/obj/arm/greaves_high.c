/*
 * These leggings are worn by the orcs at the tower at Cirith Ungol.
 * (They come in three sizes: high, medium and low; these are high)
 *
 * /Mercade, 3 august 1993
 */

inherit "/std/armour";

#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/d/Gondor/defs.h"

#define ARMOUR_CLASS 35

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
