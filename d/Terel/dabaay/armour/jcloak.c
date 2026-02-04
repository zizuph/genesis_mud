/*
   A black cloak, suitable for a assassin. Shinto 980730
 * Modified for Jenglea
 * Goldberry February, 2000
 */

#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include <wa_types.h>

create_terel_armour()
{
    set_name("cloak");
    set_pname("cloaks");

    set_short("dark cloak");
    set_pshort("dark cloaks");
    set_long("A dark cloak with black linings.\n");
    set_adj(({"dark"}));

    set_default_armour(24, A_ROBE, 0, 0);
    set_am(({ -2, 0, 2}));
}
