/*
 * This mail is worn by the orcs in the tower at Cirith Ungol.
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
    set_name("chainmail");
    add_name("mail");

    set_adj("chained");
    set_adj("strong");
    set_adj("iron");

    set_short("strong iron chainmail");
    set_pshort("strong iron chainmail");

    set_long(BSN("This mail is made of iron rings linked to eachother, " +
        "forming strong chains. Behind the chain of rings is layer of " +
        "leather for comfort. On the mail you see a crest painted: a red " +
        "eye, meaning that the previous bearer is a member of the armies " +
        "of the dark Lord."));

    set_ac(ARMOUR_CLASS);
    set_at(A_BODY);
    set_am( ({ -3, 0, 3 }) );

    add_prop(OBJ_I_WEIGHT, 8000);
    add_prop(OBJ_I_VOLUME, 4000);
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
