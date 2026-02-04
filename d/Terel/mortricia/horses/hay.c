inherit "/std/food";
#include <stdproperties.h>

void
create_food()
{
    set_name("bunch of hay");
    add_name("bunch");
    add_name("hay");
    set_pname("bunches of hay");
    add_pname("bunches");
    set_adj("dried");
    set_long("It's a bunch of dried hay. Suitable for a horse perhaps?\n");
    set_amount(27);
    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 3);
}

int
eat_access(object ob)
{
    if ((environment(ob) == environment(this_player())) &&
        (function_exists("create_heap", ob) == "/std/food") &&
        (ob->query_short()) &&
        (function_exists("create_horse", this_player())))
        return 1;
    else
        return 0;
}
