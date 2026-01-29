#include <stdproperties.h>
#include <wa_types.h>

inherit "/std/container";
inherit "/lib/holdable_item";

void create_container()
{
    string adj = one_of_list(({"simple", "plain"}));
    set_name("quiver");
    set_adj(({adj, "leather"}));
    set_short(adj + " leather quiver");
    set_long("This unadorned quiver is large and sewn from animal hide. Its "
        + "long strap is meant to be worn across the chest so arrows may be "
        + "drawn from over the shoulder.\n");
    add_prop(CONT_I_WEIGHT, 2500);
    add_prop(CONT_I_VOLUME, 4000);
    add_prop(CONT_I_MAX_WEIGHT, 9000);
    add_prop(CONT_I_MAX_VOLUME, 8000);
    add_prop(OBJ_I_VALUE, 100);
    add_prop(CONT_I_IS_QUIVER, 1);
}
