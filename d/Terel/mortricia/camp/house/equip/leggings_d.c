/* A pair of leggingss. Mortricia 920722 */
#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include <wa_types.h>

create_terel_armour()
{
    set_name(({"leggings", "pair of leggings"}));
    set_pname("pairs of leggings");
    set_short("pair of silverish leather leggings");
    set_pshort("pairs of silverish leather leggings");
    set_long("It's a pair of silverish leather leggings.\n");
    set_adj(({"silverish", "leather"}));

    set_default_armour(15, A_LEGS, 0, 0);
}
