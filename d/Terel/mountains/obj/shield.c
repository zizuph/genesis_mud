#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include <wa_types.h>
#include <stdproperties.h>

create_terel_armour()
{
    set_name("shield");
    set_adj("silver");
    set_short("silver shield");
    set_long("A strange runed silver shield.\n");
    set_ac(35);
    set_at(A_SHIELD);
    set_am(({0, 0, 0}));
    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME, 6000);
    add_prop(OBJ_I_VALUE, 15000);
}
