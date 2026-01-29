inherit "/d/Rhovanion/common/esgaroth/armours/genericarmour";

#include <wa_types.h>
        
create_armour()
{
    set_name("cloak");
    set_adj("short");
    set_long("This is a short cloak, designed to avoid being stepped on, " +
        "or tripped over by clumsy fisherman or tangled in fishhooks.\n");
    set_at(A_ROBE);
    set_ac(10);
}
