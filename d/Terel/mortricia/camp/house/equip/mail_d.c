/* A plain mail. Mortricia 920729 */

#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include <wa_types.h>

create_terel_armour()
{
    set_name("ringmail");
    set_short("steel ringmail");
    set_long("It's a ringmail made of steel.\n");
    set_adj("steel");

    set_default_armour(15, A_BODY, 0, 0);
    set_am(({ 0, 1, -1}));
}
