/*
 * This helmet is worn by the orcs at the tower at Cirith Ungol.
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

#define ARMOUR_CLASS 35

void
create_armour()
{
    set_name("helmet");
    add_name("helm");

    set_adj("black");
    set_adj("steel");
    set_adj("visored");

    set_short("black steel visored helmet");
    set_pshort("black steel visored helmets");
    set_long(BSN("This is a big and protective helmet. It is made of steel " +
        "plates and has a visor to protect your face. The steel is forged " +
        "in a special way to make it black and very strong. On the helmet " +
        "you see a crest: a red eye, meaning that the previous bearer of " +
        "helmet was a member of the armies of the dark Lord."));

    set_ac(ARMOUR_CLASS);
    set_at(A_HEAD);
    set_am( ({ -2, 0, 2 }) );

    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 380);
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
