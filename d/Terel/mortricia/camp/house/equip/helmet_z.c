#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include <wa_types.h>

create_terel_armour()
{
    set_name("helmet");
    set_short("hardened steel helmet");
    set_long("A hardened steel helmet.\n");
    set_adj("hardened");
    add_adj("steel");

    set_default_armour(20, A_HEAD, 0, 0);
    set_am(({ 1, 1, -2}));
}
