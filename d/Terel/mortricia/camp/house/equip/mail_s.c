/* A plain mail. Mortricia 920729 */

#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include <wa_types.h>

create_terel_armour()
{
    set_name("ringmail");
    set_short("small ringmail");
    set_long("It's a small ringmail.\n");
    set_adj("small");

    set_default_armour(5, A_BODY, 0, 0);
    set_am(({ 0, 1, -1}));
}
