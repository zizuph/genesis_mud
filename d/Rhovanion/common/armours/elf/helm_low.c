inherit "/std/armour";
inherit "/lib/keep";

#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"

#define ARMOUR_CLASS 4+random(3)

void
create_armour()
{
    set_name("helmet");
    add_name("helm");

    set_adj("leather");

    set_short("leather helmet");
    set_pshort("leather helmets");
    set_long(BS("This helmet is made by elves. It is made of leather " +
        "and looks strong. It is typical elven armour.\n"));

    set_ac(ARMOUR_CLASS);
    set_at(A_HEAD);
    set_am( ({ -1, 0, 1 }) );

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
