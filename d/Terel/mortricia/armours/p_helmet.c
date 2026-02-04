/*
    A helmet. Mortricia 920722
 */

inherit "/std/armour";
#include <wa_types.h>

create_armour()
{
    set_name("helmet");
    set_short("plain helmet");
    set_long("It's a plain helmet, but it looks robust.\n");
    set_adj("plain");

    set_default_armour(20, A_HEAD, 0, 0);
    set_am(({ 3, 3, -6}));
}
