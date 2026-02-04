/* A plain mail. Mortricia 920729 */

#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include <wa_types.h>

create_terel_armour()
{
    set_name("ringmail");
    set_short("simple ringmail");
    set_long("It's a very simple ringmail.\n");
    set_adj("simple");
    set_default_armour(6, A_BODY, 0, 0);
    set_am(({ -2, 1, 1}));
}
