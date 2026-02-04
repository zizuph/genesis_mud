/* A pair of leggings. Mortricia 920722 */
#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include <wa_types.h>

create_terel_armour()
{
    set_name(({"leggings", "pair of leggings"}));
    set_pname("pairs of leggings");
    set_short("pair of fancy leather leggings");
    set_pshort("pairs of fancy leather leggings");
    set_long("It's a pair of fancy leather leggings.\n");
    set_adj(({"fancy", "leather"}));

    set_default_armour(20, A_LEGS, 0, 0);
}
