#pragma save_binary

inherit "/std/armour";
inherit "/lib/keep";

#include <wa_types.h>
#include <formulas.h>
#include "/d/Shire/sys/defs.h"


#define ARMOUR_CLASS 35+random(5)

void
create_armour()
{
    set_name("mail");
    add_name("platemail");

    set_adj("steel");
    set_adj("black");

    set_short("black steel platemail");
    set_pshort("black steel platemails");

        set_long("This mail, used by a goblin and is of very good quality. " +
        "It is doubtful that it was made by goblins. It was probably " +
        "taken from some unfortunate adventurer or looted from a fallen " +
        "enemy after a battle.\n");

    set_ac(ARMOUR_CLASS);
    set_at(A_BODY);
    set_am( ({ 2, 2, -4 }) );

    add_prop(OBJ_I_WEIGHT, 10000);
    add_prop(OBJ_I_VOLUME, 4000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS) + random(201) - 100);
    set_keep(1);
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
