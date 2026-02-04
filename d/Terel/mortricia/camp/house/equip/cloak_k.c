#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include "/d/Terel/common/terel_std_rec.h"
#include <wa_types.h>

create_terel_armour()
{
    set_name("robe");
    set_short("black ceremonial robe");
    set_long("It's a black ceremonial robe.\n");
    set_adj("black");
    add_adj("ceremonial");
    set_default_armour(25, A_ROBE, 0, 0);
    set_am(({ -2, -2, 4}));
}
