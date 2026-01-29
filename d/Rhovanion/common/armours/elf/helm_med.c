inherit "/std/armour";
inherit "/lib/keep";

#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"

#define ARMOUR_CLASS 11+random(3)

void
create_armour()
{
    set_name("helmet");
    add_name("helm");

    set_adj("nice");

    set_short("nice helmet");
    set_pshort("nice helmets");
    set_long(BS("This helmet was made by elves. It is not the best " +
		"armour that you ever seen but still it is not that " +
		"good if you realize that it is elven made.\n"));

    set_ac(ARMOUR_CLASS);
    set_at(A_HEAD);
    set_am( ({ -1, 2, -1 }) );

    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 380);
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


