/* A plain cloak. Mortricia 920722 */
#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include <wa_types.h>

create_terel_armour()
{
    set_name("cloak");
    set_short("plain cloak");
    set_long("It's a plain cloak, but it will provide some " +
	     "protection.\n");
    set_adj("plain");
    set_default_armour(5, A_ROBE, 0, 0);
    set_am(({ 1, 1, -2}));
}
