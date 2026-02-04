/*
    A plain shield. Mortricia 920729
 */

inherit "/std/armour";
#include <wa_types.h>

create_armour()
{
    set_name("shield");
    set_short("plain shield");
    set_long("It's a plain shield, but it looks robust.\n");
    set_adj("plain");

    set_default_armour(15, A_SHIELD, 0, 0);
    set_am(({ 3, 3, -6}));
}
