/*
 * This helmet is worn by the orcs at the tower at Cirith Ungol.
 * (It comes in three sizes: high, medium and low; this is medium)
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
    set_name("helmet");
    add_name("helm");

    set_adj("brass");
    set_adj("plated");

    set_short("brass plated helmet");
    set_pshort("brass plated helmets");
    set_long(BSN("This helmet is made of brass plate to give you good " +
        "protection for your head. It isn't visored, but has a nose guard. " +
        "On the helmet you see a crest: a red eye, meaning that the " +
        "previous bearer of this armour was a member of the armies of the " +
        "dark Lord."));

    set_ac(ARMOUR_CLASS);
    set_at(A_HEAD);
    set_am( ({ -1, -1, 2 }) );

    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 380);
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
