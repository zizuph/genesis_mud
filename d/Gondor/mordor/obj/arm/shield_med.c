/*
 * This shield is worn by the orcs at the tower at Cirith Ungol.
 * (It comes in three sizes: high, medium and low; this is high)
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
    set_name("shield");

    set_adj("brass");
    set_adj("augmented");

    set_short("brass augmented shield");
    set_pshort("brass augmented shields");
    set_long(BSN("This shield is made off brass plates, partially " +
        "overlapping eachother to give you good protection on several " +
        "parts of your body. On the shield you see a crest painted: a red " +
        "eye, meaning that the previous bearer of this armour was a member " +
        "of the armies of the dark Lord."));

    set_ac(ARMOUR_CLASS);
    set_at(A_SHIELD);
    set_am( ({ 0, 0, 0 }) );

    add_prop(OBJ_I_WEIGHT, 6400);
    add_prop(OBJ_I_VOLUME, 1000);
    /* This value is due to the fact that it also protects your body */
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS) + random(151) );
}

int *
query_shield_slots()
{
    return (::query_shield_slots() + ({ A_BODY }) );
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
