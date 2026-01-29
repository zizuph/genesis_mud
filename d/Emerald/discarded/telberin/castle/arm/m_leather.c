inherit "/std/armour";

#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"


void
create_armour()
{

    if(!IS_CLONE)
        return;

    set_name("armour"); set_adj("leather");

    set_long("It is a tough and rigid leather hide molded to fit the "+
             "general size of an elven torso. It looks like a fairly sturdy piece of "+
             "protection.\n");

    add_adj("stiff");
    set_ac(12);

    set_am(({0,0,0}));  /* armour modifiers - slash,impale,bludgeon */
    set_at(A_BODY);

    add_prop(OBJ_I_VOLUME,3000);
    add_prop(OBJ_I_WEIGHT,9200);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(12)-24+random(69));
}

string
query_recover()
{
    return "/d/Emerald/obj/general/m_leather" + ":" + query_arm_recover();
}

void
init_recover(string arg)
{
    init_arm_recover(arg);
}
