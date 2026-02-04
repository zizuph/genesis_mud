/*
   A plain mail. Mortricia 920729
 */

inherit "/std/armour";
#include <wa_types.h>

create_armour()
{
    set_name("ringmail");
    set_short("plain ringmail");
    set_long("It's a plain ringmail.\n");
    set_adj("plain");

    set_default_armour(15, A_BODY, 0, 0);
    set_am(({ 0, 1, -1}));
}
