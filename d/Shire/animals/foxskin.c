/*
 *    A fox skin
 */
inherit "/std/armour";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/d/Shire/sys/defs.h"
#include "animals.h"

create_armour()
{
    set_name("fox pelt");
    add_name("pelt");
    add_name("fur");
    add_name("fox fur");
    set_short("red fox pelt");
    set_pshort("fox pelts");
    set_long("This is the pelt of a red fox from the Shire. It " +
        "has been expertly skinned from the animal and ready to " +
        "be tanned.\n");
    set_adj(({"red","fox's","fox"}));
    set_ac(9);
    set_at(A_BODY);
    set_am(({-2,2,1}));
    add_prop(OBJ_I_WEIGHT,(800+(random(200))));
    add_prop(OBJ_I_VOLUME,(200+(random(400))));
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(9)+random(40)-50);
    add_prop(SKIN_PROP,10);
}

