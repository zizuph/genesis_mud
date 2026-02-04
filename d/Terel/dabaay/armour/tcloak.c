/*
   A black cloak, suitable for a assassin. Shinto 980730
 */

#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include <wa_types.h>

create_terel_armour()
{
    set_name("cloak");
set_pname("cloaks");

    set_short("black cloak");
    set_long("It's a black cloak with grey linings.\n");
    set_adj(({"black"}));

    set_default_armour(20, A_ROBE, 0, 0);
    set_am(({ -2, 0, 2}));
}
