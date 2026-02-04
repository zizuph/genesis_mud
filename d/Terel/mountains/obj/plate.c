#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include <wa_types.h>
#include <stdproperties.h>

create_terel_armour()
{
    set_name(({"plate","breastplate","platemail","armor","armour"}));
    set_adj("iron");
    set_short("a large iron breastplate");
    set_long("A very crude iron breastplate.\n");
    set_ac(20);
    set_at(A_BODY);
    set_am(({0, 0, 0}));
    add_prop(OBJ_I_WEIGHT, 9500);
    add_prop(OBJ_I_VOLUME, 9500);
}
