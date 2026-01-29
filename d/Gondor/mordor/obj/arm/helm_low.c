/*
 * This helmet is worn by the orcs at the tower at Cirith Ungol.
 * (It comes in three sizes: high, medium and low; this is low)
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
    set_name("helmet");
    add_name("helm");

    set_adj("iron");
    set_adj("double");
    set_adj("chained");

    set_short("iron double chained helmet");
    set_pshort("iron double chained helmets");
    set_long(BSN("This helmet is made of very small iron rings, chained to " +
        "eachother and secured on a leather cap. The fine rings give better " +
        "protection than larger rings, for they are more flexible and they " +
        "leave less space for even an arrow to enter. On the helmet you see " +
        "a crest: a red eye, meaning that the previous bearer was a member " +
        "of the armies of the dark Lord."));

    set_ac(ARMOUR_CLASS);
    set_at(A_HEAD);
    set_am( ({ 2, 1, -3 }) );

    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME, 330);
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
