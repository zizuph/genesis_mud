/* A plain jacket. Mortricia 920722 */
#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include <wa_types.h>

create_terel_armour()
{
    set_name("jacket");
    set_short("plain jacket");
    set_long("It's a plain jacket, but it will provide some " +
	     "protection.\n");
    set_adj("plain");
    set_default_armour(3, A_BODY, 0, 0);
    set_am(({ 0, 0, 0}));
}
