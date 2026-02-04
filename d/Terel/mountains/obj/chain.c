#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include <wa_types.h>
#include <stdproperties.h>

create_terel_armour()
{
    set_name(({"chainmail","shirt","chain","armor","armour"}));
    set_adj("rusty");
    set_short("shirt of rusty chainmail");
    set_long("An old and rusty chainmail shirt.\n");
    set_ac(10);
    set_at(A_BODY);
    set_am(({0, 0, 0}));
    add_prop(OBJ_I_WEIGHT, 9500);
    add_prop(OBJ_I_VOLUME, 7500);
}
