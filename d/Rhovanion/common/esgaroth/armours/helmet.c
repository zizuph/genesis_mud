inherit "/d/Rhovanion/common/esgaroth/armours/genericarmour";

#include <wa_types.h>

create_armour()
{
    set_name("cap");
    set_adj("leather");
    set_long("This is a hard leather cap, which the townsfolk of Esgaroth " +
        "would consider a helmet.\n");
    set_at(A_HEAD);
    set_ac(9 + random(2));
}
