#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include <wa_types.h>

create_terel_armour()
{
    set_name("cloak");
    set_short("silverish cloak");
    set_long("It's a silverish cloak.\n");
    set_adj("silverish");
    set_default_armour(15, A_ROBE, 0, 0);
    set_am(({ 1, 1, -2}));
}
