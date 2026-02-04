#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include "/sys/stdproperties.h"
#include <wa_types.h>

create_terel_armour()
{
    set_name(({"chainmail","mail","chain","armor","armour"}));
    set_adj("silver");
    set_short("suit of silver chainmail");
    set_long("This suit of silver chainmail is very old.\n");
    set_ac(40);
    set_at(A_BODY);
    set_am(({0, 0, 0}));
    add_prop(OBJ_I_WEIGHT, 5500);
    add_prop(OBJ_I_VOLUME, 7500);
    add_prop(OBJ_I_VALUE, 17280);
}
