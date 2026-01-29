/*
 * This mail is worn by the orcs in the tower at Cirith Ungol.
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
    set_name("mail");

    set_adj("plated");
    set_adj("steel");
    set_adj("black");

    set_short("black steel plated mail");
    set_pshort("black steel plated mails");

    set_long(BSN("This mail is made of two steel plates, covering your " +
        "front and back, linked to two steel plates covering your sides. " +
        "Behind the plates is layer of leather for comfort. The steel " +
        "plates are forges in a special way to make it black and very " +
        "strong. On the mail you see a crest painted: a red eye, meaning " +
        "that the previous bearer is a member of the armies of the dark " +
        "Lord."));

    set_ac(ARMOUR_CLASS);
    set_at(A_BODY);
    set_am( ({ 2, 2, -4 }) );

    add_prop(OBJ_I_WEIGHT, 10000);
    add_prop(OBJ_I_VOLUME, 4000);
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
