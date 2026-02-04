/*
   A blue cloak, suitable for a prince. Mortricia 920722
 * Modified for Jenglea
 * Goldberry February, 2000
 */

#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include <wa_types.h>

create_terel_armour()
{
    set_name("tunic");
    set_short("dark tunic");
    set_long("A dark tunic with black linings.\n");
    set_adj(({"dark"}));

    set_default_armour(25, A_BODY, 0, 0);
    set_am(({ -2, 0, 2}));
}
