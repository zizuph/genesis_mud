/*
    A blue helmet, suitable for a prince. Mortricia 920722
 */

inherit "/std/armour";
#include <wa_types.h>

create_armour()
{
    set_name("helmet");
    set_short("plain helmet");
    set_long("A plain helmet, but it will provide some protection.\n");
    set_adj("plain");

    set_default_armour(20, A_HEAD, 0, 0);
    set_am(({ 3, 3, -6}));
}
