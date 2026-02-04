/*
   A plain mail. Mortricia 920729
 */

inherit "/std/armour";
#include <wa_types.h>

create_armour()
{
    set_name("ringmail");
    set_short("plain ringmail");
    set_long("It's a plain ringmail, but it looks robust\n");
    set_adj("plain");

    set_default_armour(20, A_BODY, 0, 0);
    set_am(({ 3, 3, -6}));
}
