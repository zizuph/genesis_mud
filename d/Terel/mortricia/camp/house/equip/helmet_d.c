#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include <wa_types.h>

create_terel_armour()
{
    set_name("helmet");
    set_short("pointed steel helmet");
    set_long("A pointed steel helmet.\n");
    set_adj("pointed");
    add_adj("steel");

    set_default_armour(15, A_HEAD, 0, 0);
    set_am(({ 1, 1, -2}));
}
