inherit "/std/armour";
inherit "/lib/keep";

#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"

#define ARMOUR_CLASS 33+random(5)

void
create_armour()
{
    set_name("helmet");
    add_name("helm");

    set_adj("black");
    set_adj("steel");

    set_short("black steel helmet");
    set_pshort("black steel helmets");
    set_long(BS("This helmet, used by a goblin, is of a very good quality. "+
                "It is indeed doubtfull that it was made by goblins. "+
                "Probably they have it from some unfortunate adventurer.\n"));

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
