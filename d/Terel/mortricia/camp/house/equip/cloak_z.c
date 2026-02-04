#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include "/d/Terel/common/terel_std_rec.h"
#include <wa_types.h>

create_terel_armour()
{
    set_name("robe");
    set_short("black robe");
    set_long("It's a black robe.\n");
    set_adj("black");
    set_default_armour(20, A_ROBE, 0, 0);
    set_am(({ 1, 1, -2}));
}
