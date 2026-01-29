/*
 * This mail is worn by the orcs in the tower at Cirith Ungol.
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
    set_name("mail");

    set_adj("augmented");
    set_adj("brass");

    set_short("brass augmented mail");
    set_pshort("brass augmented mails");

    set_long(BSN("This mail is made of severel strips of brass linked to " +
        "eachother and partially overlapping eachother. Behind the plates " +
        "is layer of leather for comfort. On the mail you see a crest " +
        "painted: a red eyes, meaning that the previous bearer is a member " +
        "of the armies of the dark Lord."));

    set_ac(ARMOUR_CLASS);
    set_at(A_BODY);
    set_am( ({ -2, -2, 4 }) );

    add_prop(OBJ_I_WEIGHT, 8400);
    add_prop(OBJ_I_VOLUME, 2500);
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
