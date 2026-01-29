/*
 * These leggings are worn by the orcs at the tower at Cirith Ungol.
 * (They come in three sizes: high, medium and low; these are low)
 *
 * /Mercade, 3 august 1993
 */

inherit "/std/armour";

#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/d/Gondor/defs.h"

#define ARMOUR_CLASS 18

void
create_armour()
{
    set_name("greaves");
    add_name("leggings");

    set_adj("chained");
    set_adj("double");
    set_adj("iron");

    set_short("double chained iron greaves");
    set_pshort("double chained iron greaves");
    set_long(BSN("These greaves are made of iron rings, chained to " +
        "eachother. They give you a nice protection on your legs and are " +
        "very flexible due to the fact that they are made of very small, " +
        "yet strong, rings."));

    set_ac(ARMOUR_CLASS);
    set_at(A_LEGS);
    set_am( ({ -2, 3, -1 }) );

    add_prop(OBJ_I_WEIGHT, 6300);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS) + random(101) - 50);
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
