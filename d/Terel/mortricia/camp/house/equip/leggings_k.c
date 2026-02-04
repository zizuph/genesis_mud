/* A pair of leggings. Mortricia 920722 */
#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include <wa_types.h>

create_terel_armour()
{
    set_name(({"leggings", "pair of leggings"}));
    set_pname("pairs of leggings");
    set_short("pair of golden leggings");
    set_pshort("pairs of golden leggings");
    set_long("It's a pair of golden leggings.\n");
    set_adj(({"golden"}));

    set_default_armour(25, A_LEGS, 0, 0);
}
