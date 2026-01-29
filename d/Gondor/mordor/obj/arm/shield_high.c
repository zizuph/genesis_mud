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

#define ARMOUR_CLASS 35

void
create_armour()
{
    set_name("shield");

    set_adj("black");
    set_adj("steel");
    set_adj("plated");

    set_short("black steel plated shield");
    set_pshort("black steel plated shields");
    set_long(BSN("This shield is made off black steel plate. It is a great " +
        "shield that can protect various parts of your body. The plate is " +
        "forged in a special way to make it black and very strong. On the " +
        "shield you see a crest painted: a red eye, meaning that the " +
        "previous bearer of this armour was a member of the armies of the " +
        "dark Lord."));

    set_ac(ARMOUR_CLASS);
    set_at(A_SHIELD);
    set_am( ({ 0, 0, 0 }) );

    add_prop(OBJ_I_WEIGHT, 7000);
    add_prop(OBJ_I_VOLUME, 1000);
    /* This value is made for the fact that it protects more that just
       your arm */
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS) + random(201) );
}

/*
 * This shield will not only protect the arm it is worn on, but also the other
 * major hitlocations.
 */
int *
query_shield_slots()
{
    return (::query_shield_slots() + ({ A_BODY, A_LEGS , A_HEAD }) );
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

