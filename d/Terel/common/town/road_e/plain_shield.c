/*
    A plain shield. Mortricia 920729
 */
#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;

#include <wa_types.h>

create_terel_armour()
{
    set_name("shield");
    set_short("plain shield");
    set_long("It's a plain shield.\n");
    set_adj("plain");

    set_default_armour(15, A_SHIELD, 0, 0);
    set_am(({-1, 0, 1}));
}
