#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include <wa_types.h>
#include <stdproperties.h>

create_terel_armour()
{
    set_name("coat");
    set_adj("fur");
    set_short("fur coat");
    set_long("This is a silvery fur coat, it is heavy.\n");
    set_ac(12);
    set_at(A_ROBE);
    set_am(({0, 0, 0}));
    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME, 6000);
}
