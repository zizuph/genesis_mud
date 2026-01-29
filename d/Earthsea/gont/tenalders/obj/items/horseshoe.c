/*
 * horseshoe
 * coded for Tenalders, Amelia, 9/14/97
 * used for herb witch's 'lucky items' quest
*/

#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>

public void
create_object()
{
    set_name("horseshoe");
    add_name("shoe");
    add_name("piece");
    add_name("iron");
    add_adj("old");
    add_adj("horse");
    add_adj(({"rusty", "junk"}));
    set_short("rusty old horseshoe");
    set_pshort("rusty pieces of junk iron");
    set_long("A rusty piece of junk iron. After examining " +
        "it more closely, however, you see that it is an old horseshoe! " +
        "However, the horse must have abandoned this one a long time " +
        "ago, as it is very bent and rusty. But it still has its " +
        "characteristic curved shape.\n");
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE, 25);
}

public int
query_lucky_horseshoe()
{
    return 1;
}
