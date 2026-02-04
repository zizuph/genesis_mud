/* A plain cloak. Mortricia 920722 */
#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include "/d/Terel/common/terel_std_rec.h"
#include <wa_types.h>

create_terel_armour()
{
    set_name("cloak");
    set_short("leather cloak");
    set_long("It's a leather cloak.\n");
    set_adj("leather");
    set_default_armour(10, A_ROBE, 0, 0);
    set_am(({ 1, 1, -2}));
}
