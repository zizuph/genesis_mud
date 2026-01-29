#include "../default.h"
inherit (STD + "armour");

#include <wa_types.h>

void
create_armour()
{
    ::create_armour();

    set_name("chainmail");
    set_adj("dwarven");
    add_adj("steel");
    set_pname("chainmails");
    set_short("dwarven steel chainmail");
    set_pshort("dwarven steel chainmails");
    set_long("A beautifully crafted suit of dwarven chainmail armour.\n");
    set_ac(27);
    set_at(A_BODY);
    add_prop(OBJ_I_VALUE,900);
    add_prop(OBJ_I_VOLUME,5000);
    add_prop(OBJ_I_WEIGHT,6000);
}
